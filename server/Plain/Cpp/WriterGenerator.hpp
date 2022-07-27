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
#ifndef PLAIN_CPP_WRITERGENERATOR_HPP
#define PLAIN_CPP_WRITERGENERATOR_HPP

#include <string>
#include <iostream>

#include <Declaration/SimpleDescriptor.hpp>
#include <Declaration/SimpleWriter.hpp>
#include <Declaration/StructDescriptor.hpp>
#include <Declaration/StructWriter.hpp>
#include <Declaration/CompleteTemplateDescriptor.hpp>

namespace Cpp
{
  class WriterGenerator
  {
  public:
    WriterGenerator(
      std::ostream& out_hpp,
      std::ostream& out_cpp,
      const char* offset)
      noexcept;

    /* X_DefaultBuffers */
    void generate_default_buffers_decl(
      Declaration::StructDescriptor* struct_descriptor)
      noexcept;

    void generate_default_buffers_impl(
      Declaration::StructDescriptor* struct_descriptor)
      noexcept;

    /* X_ProtectedWriter */
    void generate_protected_decl(
      Declaration::StructDescriptor* struct_descriptor)
      noexcept;

    void generate_protected_impl(
      Declaration::StructDescriptor* struct_descriptor)
      noexcept;

    /* X */
    void generate_decl(
      Declaration::StructWriter* struct_writer)
      noexcept;

    void generate_impl(
      Declaration::StructWriter* struct_writer)
      noexcept;

  private:
    /* X_ProtectedWriter & X */
    void generate_common_funs_decl_(const char* name) noexcept;

    void generate_common_funs_impl_(
      const char* class_name,
      const Declaration::StructDescriptor* struct_descriptor)
      noexcept;

    void generate_swap_impl_(
      const char* class_name,
      Declaration::StructDescriptor* struct_descriptor) noexcept;

    /* X */
    void generate_field_types_decl_(
      Declaration::StructWriter* writer) noexcept;

    void generate_accessors_decl_(
      Declaration::StructWriter* writer) noexcept;

    void generate_accessors_impl_(
      Declaration::StructWriter* writer) noexcept;

  private:
    std::ostream& out_;
    std::ostream& out_cpp_;
    std::string offset_;
  };
}

#endif /*PLAIN_CPP_WRITERGENERATOR_HPP*/
