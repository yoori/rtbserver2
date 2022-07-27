/*
 * This file is part of the RTBServer distribution (https://github.com/yoori/rtbserver2).
 * RTBServer is DSP server that allow to bid (see RTB auction) targeted ad
 * via RTB protocols (OpenRTB, Google AdExchange, Yandex RTB)
 *
 * Copyright (c) 2017 Yuri Kuznecov <yuri.kuznecov@gmail.com>.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 3 of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the
 * GNU Lesser General Public License (version 3)
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */
/// @file AdFrontend/AcFrontendStat.cpp
#include <Frontends/FrontendCommons/FrontendStatistic.hpp>
#include "ActionFrontendStat.hpp"

namespace
{
  const char AC_OPT_IN_COUNT[] = "actionRequest-OptInUser-Count";
  const char AC_OPT_OUT_COUNT[] = "actionRequest-nonOptInUser-Count";
}

namespace Aspect
{
  extern const char ACTION_FRONTEND[];
}

namespace AdServer
{

  AcFrontendStat::StatData&
  AcFrontendStat::StatData::operator +=(const AcFrontendStat::StatData& rhs) noexcept
  {
    opt_in_user += rhs.opt_in_user;
    non_opt_on_user += rhs.non_opt_on_user;

    return *this;
  }

  AcFrontendStat::AcFrontendStat(
    Logging::Logger* logger,
    const CORBACommons::CorbaObjectRef& stats_collector_ref,
    Generics::Planner* scheduler_ptr,
    const Generics::Time& dump_period,
    Generics::ActiveObjectCallback* callback,
    const char* host_name)
    /*throw(Exception)*/
    : FrontendStat(logger, stats_collector_ref, scheduler_ptr,
                   dump_period, callback, host_name),
      stat_data_()
  {
  }

  void
  AcFrontendStat::consider_request(
    const AdServer::CampaignSvcs::CampaignManager::ActionInfo& request_info)
    noexcept
  {
    if (request_info.test_request)
    {
      return;
    }

    StatData d{
      request_info.user_status == AdServer::CampaignSvcs::US_OPTIN ? 1UL : 0UL,
      request_info.user_status == AdServer::CampaignSvcs::US_OPTOUT ? 1UL : 0UL};

    if (!d.opt_in_user && !d.non_opt_on_user)
    {
      return;
    }

    Sync::PosixGuard lock(mutex_);

    stat_data_ += d;
  }

  Generics::Values_var
  AcFrontendStat::extract_stats_values()
  {
    StatData d = {0, 0}; //to prevent warning

    {
      Sync::PosixGuard lock(mutex_);
      std::swap(d, stat_data_);
    }

    Generics::Values_var v(new Generics::Values);

    v->set(AC_OPT_IN_COUNT, d.opt_in_user);
    v->set(AC_OPT_OUT_COUNT, d.non_opt_on_user);

    return v;
  }
}
