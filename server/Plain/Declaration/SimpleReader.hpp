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
#ifndef _SIMPLEREADER_HPP_
#define _SIMPLEREADER_HPP_

#include <ReferenceCounting/DefaultImpl.hpp>
#include "BaseReader.hpp"

namespace Declaration
{
  class SimpleReader: public virtual BaseReader
  {
  public:
    struct CppReadTraits
    {
      CppReadTraits(
        const char* read_type_name_val,
        const char* read_type_cast_val,
        bool read_type_cast_with_size_val,
        const char* read_type_val,
        const char* field_type_suffix_val = "")
        : read_type_name(read_type_name_val),
          read_type_cast(read_type_cast_val),
          read_type_cast_with_size(read_type_cast_with_size_val),
          read_type(read_type_val),
          field_type_suffix(field_type_suffix_val)
      {}

      // read accessor return type
      std::string read_type_name;
      // (const void*, unsigned long buf_size) -> read_type_name
      std::string read_type_cast;
      bool read_type_cast_with_size;
      std::string read_type;
      std::string field_type_suffix;
    };

    SimpleReader(
      const char* name_val,
      const CppReadTraits& cpp_read_traits)
      noexcept;

    /* BaseReader */
    virtual SimpleReader_var as_simple_reader() noexcept;

    const CppReadTraits& cpp_read_traits() const noexcept;

  protected:
    virtual ~SimpleReader() noexcept {}

  private:
    CppReadTraits cpp_read_traits_;
  };

  typedef ReferenceCounting::SmartPtr<SimpleReader>
    SimpleReader_var;
}

namespace Declaration
{
  inline
  SimpleReader::SimpleReader(
    const char* name_val,
    const CppReadTraits& cpp_read_traits)
    noexcept
    : BaseType(name_val),
      BaseReader(name_val),
      cpp_read_traits_(cpp_read_traits)
  {}

  inline
  SimpleReader_var
  SimpleReader::as_simple_reader() noexcept
  {
    return ReferenceCounting::add_ref(this);
  }

  inline
  const SimpleReader::CppReadTraits&
  SimpleReader::cpp_read_traits() const noexcept
  {
    return cpp_read_traits_;
  }
}

#endif /*_SIMPLEREADER_HPP_*/
