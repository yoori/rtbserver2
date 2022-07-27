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
#ifndef _SIMPLEDESCRIPTOR_HPP_
#define _SIMPLEDESCRIPTOR_HPP_

#include <ReferenceCounting/DefaultImpl.hpp>
#include "BaseDescriptor.hpp"

namespace Declaration
{
  class SimpleDescriptor: public virtual BaseDescriptor
  {
  public:
    SimpleDescriptor(
      const char* name,
      bool is_fixed_val,
      SizeType fixed_size_val)
      noexcept;

    virtual bool is_fixed() const noexcept;

    virtual SizeType fixed_size() const noexcept;

    virtual SimpleDescriptor_var as_simple() noexcept;

  protected:
    virtual ~SimpleDescriptor() noexcept {}
    
  private:
    bool is_fixed_;
    SizeType fixed_size_;
  };

  typedef ReferenceCounting::SmartPtr<SimpleDescriptor>
    SimpleDescriptor_var;
}

namespace Declaration
{
  inline
  SimpleDescriptor::SimpleDescriptor(
    const char* name_val,
    bool is_fixed_val,
    SizeType fixed_size_val)
    noexcept
    : BaseType(name_val),
      BaseDescriptor(name_val),
      is_fixed_(is_fixed_val),
      fixed_size_(fixed_size_val)
  {}
  
  inline
  bool
  SimpleDescriptor::is_fixed() const noexcept
  {
    return is_fixed_;
  }

  inline
  SizeType
  SimpleDescriptor::fixed_size() const noexcept
  {
    return fixed_size_;
  }

  inline
  SimpleDescriptor_var
  SimpleDescriptor::as_simple() noexcept
  {
    return ReferenceCounting::add_ref(this);
  }
}

#endif /*_SIMPLEDESCRIPTOR_HPP_*/
