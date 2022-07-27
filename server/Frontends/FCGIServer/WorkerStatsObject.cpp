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
#include "WorkerStatsObject.hpp"

namespace AdServer
{
namespace Frontends
{
  namespace Aspect
  {
    const char WORKER[] = "FCGI::Worker";
  }
  
  const Generics::Time WorkerStatsObject::STATS_TIMEOUT(5l);  // 5 seconds

  // WorkerStatsObject impl
  WorkerStatsObject::WorkerStatsObject(
    Logging::Logger* logger,
    Generics::ActiveObjectCallback* callback)
    /*throw (eh::Exception)*/
    : Commons::DelegateActiveObject(callback, 1),
      logger_(ReferenceCounting::add_ref(logger)),
      free_workers_count_(0),
      use_workers_count_(0),
      workers_interval_max_(0),
      workers_max_(0)
  {}

  void
  WorkerStatsObject::work_() noexcept
  {
    while(active())
    {
      Stream::Error ostr;

      {
        unsigned long free_workers_count;
        unsigned long use_workers_count;
        unsigned long workers_max;
        unsigned long workers_interval_max;

        {
          WorkerStatsSyncPolicy::ReadGuard lock(worker_stats_lock_);
          free_workers_count = free_workers_count_;
          use_workers_count = use_workers_count_;
          workers_max = workers_max_;
          workers_interval_max = workers_interval_max_;
          workers_interval_max_ = 0;
        }

        ostr << "Worker stats: "
          "current use: " << use_workers_count <<
          ", free: " << free_workers_count <<
          ", max: : " << workers_max <<
          ", last " << STATS_TIMEOUT.tv_sec <<
          " seconds max: " << workers_interval_max;
      }

      logger_->info(ostr.str(), Aspect::WORKER);
      
      {
        WorkerStatsSyncPolicy::WriteGuard lock(worker_cond_lock_);
        workers_condition_.timed_wait(worker_cond_lock_, &STATS_TIMEOUT, true);
      }
    }
  }

  void
  WorkerStatsObject::terminate_() noexcept
  {
    WorkerStatsSyncPolicy::WriteGuard lock(worker_cond_lock_);
    workers_condition_.broadcast();
  }

  void
  WorkerStatsObject::incr_free_workers()
  {
    WorkerStatsSyncPolicy::WriteGuard lock(worker_stats_lock_);
    free_workers_count_++;
    eval_max_workers_i_();
  }

  void
  WorkerStatsObject::dec_free_workers()
  {
    WorkerStatsSyncPolicy::WriteGuard lock(worker_stats_lock_);
    --free_workers_count_;
  }

  void
  WorkerStatsObject::incr_use_workers()
  {
    WorkerStatsSyncPolicy::WriteGuard lock(worker_stats_lock_);
    use_workers_count_++;
    eval_max_workers_i_();
  }

  void
  WorkerStatsObject::dec_use_workers()
  {
    WorkerStatsSyncPolicy::WriteGuard lock(worker_stats_lock_);
    --use_workers_count_;
  }
 
  void
  WorkerStatsObject::eval_max_workers_i_()
  {
    if(free_workers_count_ + use_workers_count_ > workers_interval_max_)
    {
      workers_interval_max_ = free_workers_count_ + use_workers_count_;
    }

    if(free_workers_count_ + use_workers_count_ > workers_max_)
    {
      workers_max_ = free_workers_count_ + use_workers_count_;
    }
  }

  WorkerStatsObject::~WorkerStatsObject() noexcept
  {}
}
}
