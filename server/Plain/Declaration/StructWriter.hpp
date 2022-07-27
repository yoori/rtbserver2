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
#ifndef _STRUCTWRITER_HPP_
#define _STRUCTWRITER_HPP_

#include <list>
#include <ReferenceCounting/DefaultImpl.hpp>
#include <ReferenceCounting/SmartPtr.hpp>
#include <Stream/MemoryStream.hpp>

#include "BaseWriter.hpp"
#include "StructDescriptor.hpp"

namespace Declaration
{
  class StructWriter:
    public virtual ReferenceCounting::AtomicImpl,
    public BaseWriter
  {
  public:
    class FieldWriter: public ReferenceCounting::AtomicImpl
    {
    public:
      FieldWriter(
        StructDescriptor::Field* field_val,
        BaseWriter* writer_val,
        const MappingSpecifierSet& mapping_specifiers)
        noexcept;

      const char* name() const noexcept;
      
      StructDescriptor::Field_var descriptor_field() const noexcept;

      BaseWriter_var writer() const noexcept;

      BaseDescriptor_var descriptor() noexcept;

      const MappingSpecifierSet&
      mapping_specifiers() const noexcept;

    protected:
      virtual ~FieldWriter() noexcept
      {}

    private:
      StructDescriptor::Field_var field_;
      BaseWriter_var writer_;
      const MappingSpecifierSet mapping_specifiers_;
    };

    typedef ReferenceCounting::SmartPtr<FieldWriter>
      FieldWriter_var;

    class FieldWriterList:
      public std::list<FieldWriter_var>,
      public ReferenceCounting::DefaultImpl<>
    {
    protected:
      virtual ~FieldWriterList() noexcept {}
    };
    
    typedef ReferenceCounting::SmartPtr<FieldWriterList>
      FieldWriterList_var;

  public:
    StructWriter(
      const char* name_val,
      BaseDescriptor* descriptor_val,
      FieldWriterList* fields_val);

    FieldWriterList_var fields() const;

    virtual BaseDescriptor_var descriptor() noexcept;

    virtual StructWriter_var as_struct_writer() noexcept;

    virtual void
    check_mapping_specifiers(
      const Declaration::MappingSpecifierSet& mapping_specifiers)
      /*throw(InvalidMappingSpecifier)*/;

  protected:
    virtual ~StructWriter() noexcept {}
    
  private:
    BaseDescriptor_var descriptor_;
    FieldWriterList_var fields_;
  };

  typedef ReferenceCounting::SmartPtr<StructWriter>
    StructWriter_var;
}

namespace Declaration
{
  // StructWriter::FieldWriter
  inline
  StructWriter::FieldWriter::FieldWriter(
    StructDescriptor::Field* field_val,
    BaseWriter* writer_val,
    const MappingSpecifierSet& mapping_specifiers)
    noexcept
    : field_(ReferenceCounting::add_ref(field_val)),
      writer_(ReferenceCounting::add_ref(writer_val)),
      mapping_specifiers_(mapping_specifiers)
  {}

  inline
  const char*
  StructWriter::FieldWriter::name() const noexcept
  {
    return field_->name();
  }

  inline
  StructDescriptor::Field_var
  StructWriter::FieldWriter::descriptor_field() const noexcept
  {
    return field_;
  }

  inline
  BaseWriter_var
  StructWriter::FieldWriter::writer() const noexcept
  {
    return writer_;
  }

  inline
  BaseDescriptor_var
  StructWriter::FieldWriter::descriptor() noexcept
  {
    return field_->descriptor();
  }

  inline
  const MappingSpecifierSet&
  StructWriter::FieldWriter::mapping_specifiers() const noexcept
  {
    return mapping_specifiers_;
  }

  // StructWriter
  inline
  StructWriter::StructWriter(
    const char* name_val,
    BaseDescriptor* descriptor_val,
    StructWriter::FieldWriterList* fields_val)
    : BaseType(name_val),
      BaseWriter(name_val),
      descriptor_(ReferenceCounting::add_ref(descriptor_val)),
      fields_(ReferenceCounting::add_ref(fields_val))
  {}

  inline
  BaseDescriptor_var
  StructWriter::descriptor() noexcept
  {
    return descriptor_;
  }

  inline
  StructWriter::FieldWriterList_var
  StructWriter::fields() const
  {
    return fields_;
  }

  inline
  StructWriter_var
  StructWriter::as_struct_writer() noexcept
  {
    return ReferenceCounting::add_ref(this);
  }

  inline
  void
  StructWriter::check_mapping_specifiers(
    const Declaration::MappingSpecifierSet& mapping_specifiers)
    /*throw(BaseWriter::InvalidMappingSpecifier)*/
  {
    if(!mapping_specifiers.empty())
    {
      // no allowed specifiers
      Stream::Error ostr;
      ostr << "Struct writer don't allow specifiers";
      throw InvalidMappingSpecifier(ostr);
    }
  }
}

#endif /*_STRUCTWRITER_HPP_*/
