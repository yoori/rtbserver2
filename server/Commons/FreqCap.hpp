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
#ifndef _COMMONS_FREQCAP_HPP_
#define _COMMONS_FREQCAP_HPP_

#include <Generics/Time.hpp>

namespace AdServer
{
  namespace Commons
  {
    struct FreqCap
    {
      FreqCap() noexcept;
      
      FreqCap(
        unsigned long fc_id_val,
        unsigned long lifelimit_val,
        const Generics::Time& period_val,
        unsigned long window_limit_val,
        const Generics::Time& window_time_val) noexcept;

      bool operator==(const FreqCap& right) const noexcept;
      
      std::ostream& print(std::ostream& out) const noexcept;
      
      unsigned long fc_id;
      unsigned long lifelimit;
      Generics::Time period;
      unsigned long window_limit;
      Generics::Time window_time;
    };
  }
}

namespace AdServer
{
  namespace Commons
  {
    inline
    FreqCap::FreqCap() noexcept
      : fc_id(0), lifelimit(0), window_limit(0)
    {}

    inline
    FreqCap::FreqCap(
      unsigned long fc_id_val,
      unsigned long lifelimit_val,
      const Generics::Time& period_val,
      unsigned long window_limit_val,
      const Generics::Time& window_time_val) noexcept
      : fc_id(fc_id_val),
        lifelimit(lifelimit_val),
        period(period_val),
        window_limit(window_limit_val),
        window_time(window_time_val)
    {}

    inline
    bool FreqCap::operator==(const FreqCap& right) const noexcept
    {
      return fc_id == right.fc_id &&
        lifelimit == right.lifelimit &&
        period == right.period &&
        window_limit == right.window_limit &&
        window_time == right.window_time;
    }

    inline
    std::ostream&
    FreqCap::print(std::ostream& out) const noexcept
    {
      out << "fc_id = " << fc_id <<
        ", lifelimit = " << lifelimit <<
        ", period = " << period.get_gm_time() <<
        ", window_limit = " << window_limit <<
        ", window_time = " << window_time.get_gm_time();
      return out;
    }
  }
}

#endif /*_COMMONS_FREQCAP_HPP_*/
