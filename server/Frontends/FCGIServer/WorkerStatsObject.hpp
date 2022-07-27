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
#ifndef WORKERSTATSOBJECT_HPP_
#define WORKERSTATSOBJECT_HPP_

#include <eh/Exception.hpp>
#include <ReferenceCounting/SmartPtr.hpp>
#include <Generics/Time.hpp>
#include <Sync/PosixLock.hpp>
#include <Sync/SyncPolicy.hpp>
#include <Logger/Logger.hpp>

#include <Commons/DelegateActiveObject.hpp>

namespace AdServer
{
namespace Frontends
{
  class WorkerStatsObject: public Commons::DelegateActiveObject
  { 
    static const Generics::Time STATS_TIMEOUT;

  public:
    WorkerStatsObject(
      Logging::Logger* logger,
      Generics::ActiveObjectCallback* callback)
      /*throw (eh::Exception)*/;

    void
    work_() noexcept;

    virtual void
    terminate_() noexcept;

    void
    incr_use_workers();

    void
    dec_use_workers();

    void
    incr_free_workers();

    void
    dec_free_workers();

  protected:
    virtual
    ~WorkerStatsObject() noexcept;

    void
    eval_max_workers_i_();

  private:
    typedef Sync::Policy::PosixThread WorkerStatsSyncPolicy;

    WorkerStatsSyncPolicy::Mutex worker_stats_lock_;
    WorkerStatsSyncPolicy::Mutex worker_cond_lock_;
    Sync::Conditional workers_condition_;

    Logging::Logger_var logger_;

    unsigned long free_workers_count_;
    unsigned long use_workers_count_;

    unsigned long workers_interval_max_;
    unsigned long workers_max_;
  };

  typedef ReferenceCounting::SmartPtr<WorkerStatsObject>
    WorkerStatsObject_var;
}
}

#endif /*WORKERSTATSOBJECT_HPP_*/
