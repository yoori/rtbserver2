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
#ifndef GENERICS_FDSETSIZE
#define GENERICS_FDSETSIZE

#include <sys/select.h>


namespace Generics
{
  union FDSet
  {
  public:
    FDSet() throw ();

    fd_set*
    operator &() throw ();

    const fd_set*
    operator &() const throw ();

  private:
    unsigned data_[16384 / (8 * sizeof(unsigned))];
    fd_set set_;
  };
};

namespace Generics
{
  FDSet::FDSet() throw ()
  {
    for (unsigned i = 0; i < sizeof(data_) / sizeof(*data_); i++)
    {
      data_[i] = 0;
    }
  }

  fd_set*
  FDSet::operator &() throw ()
  {
    return &set_;
  }

  const fd_set*
  FDSet::operator &() const throw ()
  {
    return &set_;
  }
}

#endif
