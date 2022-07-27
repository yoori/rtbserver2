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
#ifndef FRONTENDCOMMONS_FRONTENDTASKPOOL_HPP_
#define FRONTENDCOMMONS_FRONTENDTASKPOOL_HPP_

#include <String/SubString.hpp>
#include <ReferenceCounting/AtomicImpl.hpp>
#include <ReferenceCounting/SmartPtr.hpp>
#include <Stream/MemoryStream.hpp>
#include <Generics/AtomicInt.hpp>
#include <Generics/CompositeActiveObject.hpp>
#include <Generics/TaskRunner.hpp>
#include <Logger/ActiveObjectCallback.hpp>

#include "FrontendInterface.hpp"

namespace FrontendCommons
{
  class FrontendTaskPool:
    public virtual FrontendInterface,
    public Generics::CompositeActiveObject
  {
  public:
    FrontendTaskPool(
      Generics::ActiveObjectCallback* callback,
      unsigned long threads,
      unsigned long max_pending_tasks)
      /*throw(eh::Exception)*/;

    virtual bool
    will_handle(const String::SubString& uri) noexcept = 0;

    virtual void
    handle_request(
      FCGI::HttpRequestHolder_var request_holder,
      FCGI::HttpResponseWriter_var response_writer)
      noexcept;

    virtual void
    handle_request_noparams(
      FCGI::HttpRequestHolder_var request_holder,
      FCGI::HttpResponseWriter_var response_writer)
      noexcept;

  protected:
    class HandleRequestTask;

  protected:
    virtual
    ~FrontendTaskPool() noexcept = default;

    virtual void
    handle_request_(
      FCGI::HttpRequestHolder_var request_holder,
      FCGI::HttpResponseWriter_var response_writer)
      noexcept = 0;

    virtual void
    handle_request_noparams_(
      FCGI::HttpRequestHolder_var request_holder,
      FCGI::HttpResponseWriter_var response_writer)
      noexcept;

    void
    push_handle_request_task_(
      FCGI::HttpRequestHolder_var request_holder,
      FCGI::HttpResponseWriter_var response_writer,
      bool noparams)
      noexcept;

  protected:
    const unsigned long threads_;
    const unsigned long max_pending_tasks_;

    //Logging::LoggerCallbackHolder callback_holder_;
    Generics::TaskRunner_var task_runner_;
    Generics::AtomicInt task_count_;
  };
}

#endif /*FRONTENDCOMMONS_FRONTENDTASKPOOL_HPP_*/
