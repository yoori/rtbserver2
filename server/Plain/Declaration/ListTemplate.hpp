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
#ifndef PLAIN_DECLARATION_LISTTEMPLATE_HPP
#define PLAIN_DECLARATION_LISTTEMPLATE_HPP

#include <ReferenceCounting/DefaultImpl.hpp>
#include "BaseTemplate.hpp"
#include "CompleteTemplateDescriptor.hpp"

namespace Declaration
{
  /* BaseArrayTemplate */
  class BaseArrayTemplate:
    public virtual ReferenceCounting::DefaultImpl<>,
    public BaseTemplate
  {
  public:
    BaseArrayTemplate(
      const char* name,
      unsigned long header_size) noexcept;

  protected:
    virtual ~BaseArrayTemplate() noexcept {}
    
    virtual CompleteTemplateDescriptor_var
    create_template_descriptor_(
      const char* name,
      const BaseDescriptorList& args) const
      /*throw(InvalidParam)*/;

  private:
    CompleteTemplateDescriptor_var create_array_simple_type_(
      BaseDescriptor* descriptor) const
      noexcept;

    CompleteTemplateDescriptor_var create_array_struct_type_(
      BaseDescriptor* descriptor) const
      noexcept;

  private:
    unsigned long header_size_;
  };

  /* ArrayTemplate */
  class ArrayTemplate: public BaseArrayTemplate
  {
  public:
    ArrayTemplate() noexcept;

  protected:
    virtual ~ArrayTemplate() noexcept {}
  };

  /* CompatibilityListTemplate */
  class CompatibilityListTemplate: public BaseArrayTemplate
  {
  public:
    CompatibilityListTemplate() noexcept;

  protected:
    virtual ~CompatibilityListTemplate() noexcept {}
  };
}

#endif /*PLAIN_DECLARATION_LISTTEMPLATE_HPP*/
