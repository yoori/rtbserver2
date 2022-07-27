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
// file      : Utility/Synch/Policy/Null.hpp
// author    : Boris Kolpackov <boris@kolpackov.net>
// copyright : Copyright (c) 2002-2003 Boris Kolpackov
// license   : http://kolpackov.net/license.html

#ifndef SYNC_NULL_SYNCH_POLICY_HPP
#define SYNC_NULL_SYNCH_POLICY_HPP

#include <Generics/Uncopyable.hpp>


namespace Sync
{
  namespace Policy
  {
    class NullMutex : private Generics::Uncopyable
    {
    };

    class NullGuard : private Generics::Uncopyable
    {
    public:
      explicit
      NullGuard(NullMutex&) throw ();
    };

    struct Null
    {
      typedef NullMutex Mutex;
      typedef NullGuard ReadGuard;
      typedef NullGuard WriteGuard;
    };
  }
}


namespace Sync
{
  namespace Policy
  {
    inline
    NullGuard::NullGuard (NullMutex&) throw ()
    {
    }
  }
}

#endif
