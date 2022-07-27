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
#include "BaseType.hpp"
#include "BaseDescriptor.hpp"
#include "BaseReader.hpp"
#include "BaseWriter.hpp"
#include "BaseTemplate.hpp"

namespace Declaration
{
  BaseType::BaseType(const char* name_val)
    : name_(name_val)
  {}

  const char*
  BaseType::name() const
  {
    return name_.c_str();
  }

  BaseDescriptor_var
  BaseType::as_descriptor() noexcept
  {
    return BaseDescriptor_var();
  }

  BaseReader_var
  BaseType::as_reader() noexcept
  {
    return BaseReader_var();
  }

  BaseWriter_var
  BaseType::as_writer() noexcept
  {
    return BaseWriter_var();
  }

  BaseTemplate_var
  BaseType::as_template() noexcept
  {
    return BaseTemplate_var();
  }
}

