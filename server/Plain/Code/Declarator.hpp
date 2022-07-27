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
#ifndef _CODE_DECLARATOR_HPP_
#define _CODE_DECLARATOR_HPP_

#include <ReferenceCounting/DefaultImpl.hpp>
#include <ReferenceCounting/SmartPtr.hpp>

#include <Declaration/BaseDescriptor.hpp>
#include <Declaration/BaseTemplate.hpp>
#include <Declaration/SimpleType.hpp>
#include <Declaration/StructDescriptor.hpp>
#include <Declaration/CompleteTemplateDescriptor.hpp>
#include <Declaration/StructReader.hpp>
#include <Declaration/StructWriter.hpp>
#include <Declaration/Namespace.hpp>

#include "Element.hpp"
#include "IncludeElement.hpp"
#include "TypeElement.hpp"
#include "TypeDefElement.hpp"
#include "NamespaceElement.hpp"

namespace Code
{
  class Declarator: public ReferenceCounting::DefaultImpl<>
  {
  public:
    DECLARE_EXCEPTION(AlreadyDefined, eh::DescriptiveException);
    
  public:
    Declarator(
      Declaration::Namespace* root_namespace,
      Code::ElementList* elements)
      noexcept;

    void open_namespace(const char* name) noexcept;

    void close_namespace() noexcept;

    Declaration::Namespace_var current_namespace() noexcept;

    /*
    void open_include(const char* file_name) noexcept;

    void close_include() noexcept;
    */

    Declaration::StructDescriptor_var
    declare_struct(
      const char* name,
      Declaration::StructDescriptor::FieldList* fields)
      noexcept;

    Declaration::StructReader_var
    declare_struct_reader(
      const char* name,
      Declaration::StructDescriptor* struct_descriptor,
      Declaration::StructReader::FieldReaderList* decl_list)
      noexcept;

    Declaration::StructWriter_var
    declare_struct_writer(
      const char* name,
      Declaration::StructDescriptor* struct_descriptor,
      Declaration::StructWriter::FieldWriterList* decl_list)
      noexcept;

  private:
    Declaration::Namespace_var root_namespace_;
    Code::ElementList_var elements_;

    Declaration::Namespace_var current_namespace_;
  };

  typedef ReferenceCounting::SmartPtr<Declarator>
    Declarator_var;
}

#endif
