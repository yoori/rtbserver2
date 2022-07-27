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
#ifndef USERINFOSVCS_USERINFOCOMMONS_ALLOCATOR_HPP
#define USERINFOSVCS_USERINFOCOMMONS_ALLOCATOR_HPP

#include <Generics/Allocator.hpp>
#include <Generics/MemBuf.hpp>

namespace AdServer
{
  namespace UserInfoSvcs
  {
    struct MembufAllocator
    {
      static Generics::Allocator::FixedBase_var ALLOCATOR;
    };

    typedef Generics::MemBufTmpl<MembufAllocator> MemBuf;
    typedef Generics::SmartMemBufTmpl<Generics::MemBuf, MembufAllocator>
      SmartMemBuf;
    typedef Generics::SmartMemBufTmpl<const Generics::MemBuf,
      MembufAllocator> ConstSmartMemBuf;

    typedef Generics::SmartMemBuf* SmartMemBufPtr;
    typedef const Generics::ConstSmartMemBuf* ConstSmartMemBufPtr;

    using Generics::SmartMemBuf_var;
    using Generics::ConstSmartMemBuf_var;
    /*
    typedef ReferenceCounting::ConstPtr<ConstSmartMemBuf>
      ConstSmartMemBuf_var;
    */
  }
}

#endif
