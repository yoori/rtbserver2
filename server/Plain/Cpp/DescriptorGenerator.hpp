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
#ifndef PLAIN_CPP_DESCRIPTORGENERATOR_HPP
#define PLAIN_CPP_DESCRIPTORGENERATOR_HPP

#include <string>
#include <iostream>

#include <Declaration/SimpleDescriptor.hpp>
#include <Declaration/SimpleReader.hpp>
#include <Declaration/SimpleWriter.hpp>
#include <Declaration/StructDescriptor.hpp>
#include <Declaration/CompleteTemplateDescriptor.hpp>

namespace Cpp
{
  /* DescriptorGenerator:
   *   generate descriptor struct with field offsets
   *   generate _WriterBase struct: container for load and resave value
   *     inside writer that don't declare accessor for field with this type
   */
  class DescriptorGenerator
  {
  public:
    DescriptorGenerator(
      std::ostream& out_hpp,
      std::ostream& out_cpp,
      const char* offset)
      noexcept;

    void generate_decl(
      Declaration::StructDescriptor* struct_descriptor)
      noexcept;

    void generate_impl(
      Declaration::StructDescriptor* struct_descriptor)
      noexcept;

  private:
    void generate_descriptor_base_decl_(
      const Declaration::StructDescriptor* descriptor) noexcept;

  private:
    std::ostream& out_;
    std::ostream& out_cpp_;
    std::string offset_;
  };
}

#endif /*PLAIN_CPP_DESCRIPTORGENERATOR_HPP*/
