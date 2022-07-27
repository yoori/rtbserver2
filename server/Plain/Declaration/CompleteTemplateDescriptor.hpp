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
#ifndef PLAIN_DECLARATION_COMPLETETEMPLATEDESCRIPTOR_HPP
#define PLAIN_DECLARATION_COMPLETETEMPLATEDESCRIPTOR_HPP

#include "BaseDescriptor.hpp"
#include "BaseReader.hpp"
#include "BaseWriter.hpp"

namespace Declaration
{
  class CompleteTemplateDescriptor: public virtual BaseDescriptor
  {
  public:
    DECLARE_EXCEPTION(Exception, eh::DescriptiveException);
    DECLARE_EXCEPTION(InvalidParam, Exception);

    CompleteTemplateDescriptor(
      const char* name,
      const BaseDescriptorList& args)
      noexcept;

    virtual bool is_fixed() const noexcept = 0;

    virtual SizeType fixed_size() const noexcept = 0;

    CompleteTemplateDescriptor_var
    as_complete_template() noexcept;

    BaseReader_var
    complete_template_reader(const BaseReaderList& args)
      /*throw(InvalidParam)*/;

    BaseWriter_var
    complete_template_writer(const BaseWriterList& args)
      /*throw(InvalidParam)*/;

    const BaseDescriptorList& args() const noexcept;

  protected:
    virtual ~CompleteTemplateDescriptor() noexcept {}

    virtual BaseReader_var
    create_template_reader_(const BaseReaderList& args)
      /*throw(InvalidParam)*/ = 0;

    virtual BaseWriter_var
    create_template_writer_(const BaseWriterList& args)
      /*throw(InvalidParam)*/ = 0;

  private:
    BaseDescriptorList args_;
  };

  typedef ReferenceCounting::SmartPtr<CompleteTemplateDescriptor>
    CompleteTemplateDescriptor_var;
}

#endif /*PLAIN_DECLARATION_COMPLETETEMPLATEDESCRIPTOR_HPP*/
