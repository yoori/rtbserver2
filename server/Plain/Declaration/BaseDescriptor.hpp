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
#ifndef PLAIN_DECLARATION_BASEDESCRIPTOR_HPP
#define PLAIN_DECLARATION_BASEDESCRIPTOR_HPP

#include <list>
#include "BaseType.hpp"

namespace Declaration
{
  class SimpleDescriptor;
  typedef ReferenceCounting::SmartPtr<SimpleDescriptor>
    SimpleDescriptor_var;

  class StructDescriptor;
  typedef ReferenceCounting::SmartPtr<StructDescriptor>
    StructDescriptor_var;

  class TemplateDescriptor;
  typedef ReferenceCounting::SmartPtr<TemplateDescriptor>
    TemplateDescriptor_var;

  class CompleteTemplateDescriptor;
  typedef ReferenceCounting::SmartPtr<CompleteTemplateDescriptor>
    CompleteTemplateDescriptor_var;

  typedef unsigned long SizeType;

  class BaseDescriptor: public virtual BaseType
  {
  public:
    BaseDescriptor(const char* name_val);
    
    virtual SimpleDescriptor_var as_simple() noexcept;

    virtual StructDescriptor_var as_struct() noexcept;

    virtual CompleteTemplateDescriptor_var as_complete_template() noexcept;

    virtual bool is_fixed() const noexcept = 0;

    virtual SizeType fixed_size() const noexcept = 0;

    virtual BaseDescriptor_var as_descriptor() noexcept;

  protected:
    virtual ~BaseDescriptor() noexcept {}
  };

  typedef ReferenceCounting::SmartPtr<BaseDescriptor>
    BaseDescriptor_var;

  typedef std::list<BaseDescriptor_var> BaseDescriptorList;
}

#endif /*PLAIN_DECLARATION_BASEDESCRIPTOR_HPP*/
