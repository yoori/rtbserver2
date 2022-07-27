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
#ifndef GENERICS_PROC_HPP
#define GENERICS_PROC_HPP

#include <cstddef>


namespace Generics
{
  namespace Proc
  {
    /**
     * Reads process' memory information from proc(5)
     * @param vsize virtual memory size
     * @param rss resident memory size
     * @return whether or not reading has been successful
     */
    bool
    memory_status(unsigned long& vsize, unsigned long& rss)
      throw ();

    /**
     * Fills buffer with backtrace information
     * @param buf buffer to fill
     * @param size its size
     * @param from the deepest function to add
     * @param to the most shallow function to add
     */
    void
    backtrace(char* buf, size_t size, size_t from, size_t to)
      throw ();
  }
}

#endif