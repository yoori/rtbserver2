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
#include <TestCommons/Memory.hpp>


namespace TestCommons
{
  void
  print_mallinfo(std::ostream& ostr, struct mallinfo* info)
    /*throw (eh::Exception)*/
  {
    struct mallinfo real_info;
    if (!info)
    {
      real_info = mallinfo();
      info = &real_info;
    }

    ostr <<
      " non-mmapped space allocated from system " << info->arena << "\n" <<
      " number of free chunks " << info->ordblks << "\n" <<
      " number of fastbin blocks " << info->smblks << "\n" <<
      " number of mmapped regions " << info->hblks << "\n" <<
      " space in mmapped regions " << info->hblkhd << "\n" <<
      " maximum total allocated space " << info->usmblks << "\n" <<
      " space available in freed fastbin blocks " << info->fsmblks << "\n" <<
      " total allocated space " << info->uordblks << "\n" <<
      " total free space " << info->fordblks << "\n" <<
      " top-most, releasable (via malloc_trim) space " << info->keepcost <<
      "\n" << std::endl;
  }
}
