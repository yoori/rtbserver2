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
#ifndef USERINFOSVCS_USERINFOMANAGERSTAT_HPP
#define USERINFOSVCS_USERINFOMANAGERSTAT_HPP

#include <CORBACommons/StatsImpl.hpp>
#include <CORBACommons/ServantImpl.hpp>

#include <Controlling/StatsDumper/StatsDumper.hpp>
#include "UserInfoManagerImpl.hpp"

namespace AdServer
{
  namespace UserInfoSvcs
  {
    /* UserInfoClusterStatsImpl */
    class UserInfoManagerStatsImpl:
      public virtual CORBACommons::ReferenceCounting::ServantImpl<
        POA_CORBACommons::ProcessStatsControl>,
      public virtual Generics::CompositeActiveObject
    {
    public:
      UserInfoManagerStatsImpl(
        Generics::ActiveObjectCallback* callback,
        Logging::Logger* logger,
        UserInfoManagerImpl* uim_val,
        const CORBACommons::CorbaObjectRef& dumper_ref,
        const Generics::Time& update_period)
        noexcept;

      virtual 
      ~UserInfoManagerStatsImpl() noexcept;

      virtual CORBACommons::StatsValueSeq*
      get_stats() throw(
        CORBA::Exception,
        CORBACommons::ProcessStatsControl::ImplementationException);

    protected:
      void
      dump_stats_() noexcept;

    private:
      class DumpStatsTask: public Generics::TaskGoal
      {
      public:
        DumpStatsTask(
          UserInfoManagerStatsImpl* user_info_manager_stats)
          noexcept
          : Generics::TaskGoal(user_info_manager_stats->task_runner_),
            user_info_manager_stats_(user_info_manager_stats)
        {}

        virtual void execute() noexcept
        {
          user_info_manager_stats_->dump_stats_();
        }

      protected:
        virtual ~DumpStatsTask() noexcept
        {}

      private:
        UserInfoManagerStatsImpl* user_info_manager_stats_;
      };

      typedef std::unique_ptr<AdServer::Controlling::StatsDumper>
        StatsDumperPtr;

    private:
      Generics::ActiveObjectCallback_var callback_;
      Logging::Logger_var logger_;

      UserInfoManagerImpl_var uim_;

      Generics::Planner_var scheduler_;
      Generics::TaskRunner_var task_runner_;
      Generics::Time update_period_;
      StatsDumperPtr stats_dumper_;
    };

    typedef ReferenceCounting::SmartPtr<UserInfoManagerStatsImpl>
      UserInfoManagerStatsImpl_var;
  } /* UserInfoSvcs */
} /* AdServer */

#endif
