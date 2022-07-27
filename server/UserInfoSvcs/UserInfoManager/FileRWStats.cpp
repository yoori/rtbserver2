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
#include "FileRWStats.hpp"

namespace AdServer
{
namespace UserInfoSvcs
{
  FileRWStats::FileRWStats(
    const Generics::Time interval,
    const std::size_t times)
    noexcept
    : interval_(interval), times_(times)
  {
    IntervalStat stat;
    stat.timestamp = Generics::Time::get_time_of_day();
    stats_.push_back(stat);
  }

  FileRWStats::IntervalStats
  FileRWStats::get_stats() const noexcept
  {
    SyncPolicy::ReadGuard lock(stats_lock_);
    return stats_;
  }

  void
  FileRWStats::add_read_time_(
    const Generics::Time& start,
    const Generics::Time& stop,
    unsigned long size)
    noexcept
  {
    SyncPolicy::WriteGuard lock(stats_lock_);
    check_for_new_interval_i_(stop);
    add_time_i_(start, stop, size, stats_.back().read);
  }

  void
  FileRWStats::add_write_time_(
    const Generics::Time& start,
    const Generics::Time& stop,
    unsigned long size)
    noexcept
  {
    SyncPolicy::WriteGuard lock(stats_lock_);
    check_for_new_interval_i_(stop);
    add_time_i_(start, stop, size, stats_.back().write);
  }

  void
  FileRWStats::check_for_new_interval_i_(const Generics::Time& stop) noexcept
  {
    if (stop > stats_.back().timestamp &&
        (stop - stats_.back().timestamp) > interval_)
    {
      IntervalStat stat;
      stat.timestamp = stop;
      stats_.push_back(stat);

      if (stats_.size() > times_)
      {
        stats_.pop_front();
      }
    }
  }

  void
  FileRWStats::add_time_i_(
    const Generics::Time& start,
    const Generics::Time& stop,
    unsigned long size,
    Counters& counters)
    noexcept
  {
    const Generics::Time time = stop - start;
    counters.max_time = std::max(counters.max_time, time);
    counters.sum_time += time;
    counters.sum_size += size;
    ++counters.count;
  }
}
}
