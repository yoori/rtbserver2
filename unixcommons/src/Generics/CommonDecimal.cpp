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
#include <Generics/CommonDecimal.hpp>


namespace Generics
{
  namespace DecimalHelper
  {
    template <>
    void
    mul<false>(uint64_t factor1, uint64_t factor2, uint64_t base,
      uint64_t& major, uint64_t& minor) throw ()
    {
      uint64_t h, l;
      __asm__ __volatile__(
        "mulq %%rdx\n"
        "divq %%rcx\n"
        : "=a" (h), "=d" (l)
        : "a" (factor1), "d" (factor2), "c" (base)
      );
      major = h;
      minor = l;
    }

    template <>
    void
    div<false>(uint64_t major, uint64_t minor, uint64_t base,
      uint64_t divisor, uint64_t& quotient, uint64_t& remainder) throw ()
    {
      uint64_t q, r;
      __asm__ __volatile__(
        "mulq %%rcx\n"
        "addq %%rsi, %%rax\n"
        "adcq $0, %%rdx\n"
        "divq %%rdi\n"
        : "=d" (r), "=a" (q)
        : "a" (major), "S" (minor), "c" (base), "D" (divisor)
      );
      quotient = q;
      remainder = r;
    }
  }
}
