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
#ifndef USERINFOSVCS_USERINFOMANAGER_FILERWSTATS_HPP_
#define USERINFOSVCS_USERINFOMANAGER_FILERWSTATS_HPP_

#include <list>

#include <ProfilingCommons/PlainStorage3/FileController.hpp>

namespace AdServer
{
namespace UserInfoSvcs
{
  class FileRWStats : public ProfilingCommons::PosixFileController::Stat
  {
  public:
    typedef Sync::Policy::PosixThread SyncPolicy;

    struct Counters : public ProfilingCommons::StatImpl::Counters
    {
      unsigned long sum_size;

      Counters()
        : ProfilingCommons::StatImpl::Counters(), sum_size(0)
      {}
    };

    struct IntervalStat
    {
      Counters read;
      Counters write;
      Generics::Time timestamp;
    };

    typedef std::list<IntervalStat> IntervalStats;

  public:
    FileRWStats(
      const Generics::Time interval,
      const std::size_t times)
      noexcept;

    IntervalStats
    get_stats() const noexcept;

  protected:
    virtual
    ~FileRWStats() noexcept
    {}

    void
    add_read_time_(
      const Generics::Time& start,
      const Generics::Time& stop,
      unsigned long size)
      noexcept;

    void
    add_write_time_(
      const Generics::Time& start,
      const Generics::Time& stop,
      unsigned long size)
      noexcept;

    void
    check_for_new_interval_i_(const Generics::Time& stop) noexcept;

    void
    add_time_i_(
      const Generics::Time& start,
      const Generics::Time& stop,
      unsigned long size,
      Counters& counters)
      noexcept;

  private:
    const Generics::Time interval_;
    const std::size_t times_;
    mutable SyncPolicy::Mutex stats_lock_;
    IntervalStats stats_;
  };
}
}

#endif /* USERINFOSVCS_USERINFOMANAGER_FILERWSTATS_HPP_ */
