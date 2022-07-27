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
#ifndef REQUESTOPERATIONLOADER_HPP
#define REQUESTOPERATIONLOADER_HPP

#include <Generics/ActiveObject.hpp>
#include <ProfilingCommons/PlainStorage3/FileReader.hpp>

#include "RequestOperationProcessor.hpp"

namespace AdServer
{
namespace RequestInfoSvcs
{
  class RequestOperationLoader:
    public virtual ReferenceCounting::AtomicImpl
  {
  public:
    DECLARE_EXCEPTION(Exception, eh::DescriptiveException);

    enum Operation
    {
      OP_CHANGE = 0,
      OP_IMPRESSION,
      OP_ACTION,
      OP_REQUEST_ACTION
    };

    RequestOperationLoader(
      RequestOperationProcessor* request_operation_processor)
      noexcept;

    bool
    process_file(
      unsigned long& processed_lines_count,
      const char* file,
      Generics::ActiveObject* interrupter)
      /*throw(Exception)*/;

  protected:
    virtual
    ~RequestOperationLoader() noexcept
    {}

  private:
    void
    read_change_request_user_id_(
      ProfilingCommons::FileReader& file_reader,
      Generics::MemBuf& membuf)
      /*throw(Exception)*/;

    void
    skip_change_request_user_id_(
      ProfilingCommons::FileReader& file_reader)
      /*throw(Exception)*/;

    void
    read_impression_(
      ProfilingCommons::FileReader& file_reader,
      Generics::MemBuf& membuf)
      /*throw(Exception)*/;

    void
    read_action_(
      ProfilingCommons::FileReader& file_reader,
      Generics::MemBuf& membuf)
      /*throw(Exception)*/;

    void
    read_request_action_(
      ProfilingCommons::FileReader& file_reader,
      Generics::MemBuf& membuf)
      /*throw(Exception)*/;

    void
    skip_single_buffer_operation_(
      ProfilingCommons::FileReader& file_reader)
      /*throw(Exception)*/;

    void
    prepare_mem_buf_(
      Generics::MemBuf& membuf,
      unsigned long size)
      noexcept;

  private:
    RequestOperationProcessor_var request_operation_processor_;
  };

  typedef ReferenceCounting::SmartPtr<RequestOperationLoader>
    RequestOperationLoader_var;
}
}

#endif /*REQUESTOPERATIONLOADER_HPP*/
