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
#ifndef GENERICS_RANDOM_SELECT_HPP
#define GENERICS_RANDOM_SELECT_HPP

#include <iterator>
#include <functional>
#include <algorithm>

#include <Generics/Rand.hpp>


namespace Generics
{
  template <typename SumType, typename WeightFun, typename Iterator>
  Iterator
  random_select(const Iterator& begin, const Iterator& end,
    const WeightFun& weight_fun = WeightFun())
  {
    SumType cumulative_weight = 0;
    for (Iterator it = begin; it != end; ++it)
    {
      cumulative_weight += weight_fun(*it);
    }

    SumType rnd_weight = safe_rand(1, cumulative_weight);

    SumType cum_weight = 0;

    for (Iterator it = begin; it != end; ++it)
    {
      if (rnd_weight <= cum_weight + weight_fun(*it))
      {
        return it;
      }
      cum_weight += weight_fun(*it);
    }

    return end;
  }
}

#endif
