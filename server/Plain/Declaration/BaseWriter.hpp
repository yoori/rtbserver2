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
#ifndef _BASEWRITER_HPP_
#define _BASEWRITER_HPP_

#include <list>
#include <set>
#include <eh/Exception.hpp>
#include "BaseType.hpp"

namespace Declaration
{
  typedef std::set<std::string> MappingSpecifierSet;

  class SimpleWriter;
  typedef ReferenceCounting::SmartPtr<SimpleWriter>
    SimpleWriter_var;

  class StructWriter;
  typedef ReferenceCounting::SmartPtr<StructWriter>
    StructWriter_var;

  class BaseWriter: public virtual BaseType
  {
  public:
    DECLARE_EXCEPTION(Exception, eh::DescriptiveException);
    DECLARE_EXCEPTION(InvalidMappingSpecifier, Exception);

    BaseWriter(const char* name_val) noexcept;

    virtual BaseDescriptor_var descriptor() noexcept = 0;

    virtual void
    check_mapping_specifiers(
      const MappingSpecifierSet& mapping_specifiers)
      /*throw(InvalidMappingSpecifier)*/ = 0;

    /* non fixed field */
    virtual SimpleWriter_var as_simple_writer() noexcept;

    virtual StructWriter_var as_struct_writer() noexcept;

    virtual BaseWriter_var as_writer() noexcept;

  protected:
    virtual ~BaseWriter() noexcept {}
  };

  typedef ReferenceCounting::SmartPtr<BaseWriter>
    BaseWriter_var;

  typedef std::list<BaseWriter_var> BaseWriterList;
}

#endif /*_BASEWRITER_HPP_*/
