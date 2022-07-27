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
#ifndef PLAIN_DECLARATION_SIMPLETYPE_HPP
#define PLAIN_DECLARATION_SIMPLETYPE_HPP

#include <ReferenceCounting/DefaultImpl.hpp>
#include "SimpleDescriptor.hpp"
#include "SimpleReader.hpp"
#include "SimpleWriter.hpp"

namespace Declaration
{
  /* SimpleType is descriptor, reader and writer with one name
   *   requirement : descriptor must return writer at as_writer
   */
  class SimpleType:
    public virtual ReferenceCounting::DefaultImpl<>,
    public virtual BaseType,
    public SimpleDescriptor,
    public SimpleReader,
    public SimpleWriter
  {
  public:
    SimpleType(
      const char* name,
      bool is_fixed_val,
      SizeType fixed_size_val,
      const SimpleReader::CppReadTraits& cpp_read_traits,
      SimpleWriter::CppWriteTraitsGenerator* cpp_write_traits_generator);

    /* BaseType */
    virtual BaseDescriptor_var as_descriptor() noexcept;

    virtual BaseReader_var as_reader() noexcept;

    virtual BaseWriter_var as_writer() noexcept;

    /* BaseDescriptor */
    virtual SimpleDescriptor_var as_simple() noexcept;

    /* BaseReader/BaseWriter */
    virtual BaseDescriptor_var descriptor() noexcept;

  protected:
    virtual ~SimpleType() noexcept {}
  };

  typedef ReferenceCounting::SmartPtr<SimpleType>
    SimpleType_var;
}

namespace Declaration
{
  inline
  SimpleType::SimpleType(
    const char* name_val,
    bool is_fixed_val,
    SizeType fixed_size_val,
    const SimpleReader::CppReadTraits& cpp_read_traits,
    SimpleWriter::CppWriteTraitsGenerator* cpp_write_traits_generator)
    : BaseType(name_val),
      BaseDescriptor(name_val),
      BaseReader(name_val),
      SimpleDescriptor(name_val, is_fixed_val, fixed_size_val),
      SimpleReader(name_val, cpp_read_traits),
      SimpleWriter(name_val, cpp_write_traits_generator)
  {}

  inline
  BaseDescriptor_var
  SimpleType::as_descriptor() noexcept
  {
    return ReferenceCounting::add_ref(this);
  }

  inline
  BaseReader_var
  SimpleType::as_reader() noexcept
  {
    return ReferenceCounting::add_ref(this);
  }

  inline
  BaseWriter_var
  SimpleType::as_writer() noexcept
  {
    return ReferenceCounting::add_ref(this);
  }

  inline
  SimpleDescriptor_var
  SimpleType::as_simple() noexcept
  {
    return ReferenceCounting::add_ref(this);
  }

  inline
  BaseDescriptor_var
  SimpleType::descriptor() noexcept
  {
    return ReferenceCounting::add_ref(this);
  }
}

#endif /*PLAIN_DECLARATION_SIMPLETYPE_HPP*/
