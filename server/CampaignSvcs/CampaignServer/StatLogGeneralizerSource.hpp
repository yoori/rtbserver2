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
#ifndef CAMPAIGNSERVER_STATLOGGENERALIZERSOURCE_HPP
#define CAMPAIGNSERVER_STATLOGGENERALIZERSOURCE_HPP

#include <eh/Exception.hpp>
#include <ReferenceCounting/AtomicImpl.hpp>
#include <Logger/Logger.hpp>
#include <CORBACommons/CorbaAdapters.hpp>

#include <Commons/CorbaObject.hpp>
#include <LogProcessing/LogGeneralizer/LogGeneralizer.hpp>

#include "StatSource.hpp"

namespace AdServer
{
namespace CampaignSvcs
{
  class StatLogGeneralizerSource:
    public StatSource,
    public virtual ReferenceCounting::AtomicImpl
  {
  public:
    DECLARE_EXCEPTION(Exception, StatSource::Exception);

    StatLogGeneralizerSource(
      Logging::Logger* logger,
      unsigned long server_id,
      const CORBACommons::CorbaObjectRefList& stat_providers)
      noexcept;

    virtual Stat_var
    update(
      Stat* stat,
      bool& full_synch_required,
      const Generics::Time& now)
      /*throw(Exception)*/;

  protected:
    virtual ~StatLogGeneralizerSource() noexcept {}

  private:
    typedef AdServer::Commons::CorbaObject<
      AdServer::LogProcessing::LogGeneralizer> LogGeneralizerRef;
    typedef std::list<LogGeneralizerRef> LogGeneralizerRefList;

  private:
    StatSource::Stat_var
    convert_stats_update_(
      const AdServer::LogProcessing::StatInfo& update,
      const Generics::Time& now)
      /*throw(Exception)*/;

  private:
    Logging::Logger_var logger_;
    unsigned long server_id_;
    LogGeneralizerRefList stat_providers_;
  };
}
}

#endif /*CAMPAIGNSERVER_STATLOGGENERALIZERSOURCE_HPP*/
