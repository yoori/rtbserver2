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
#pragma once

#include <list>
#include <pthread.h>

#include <boost/asio.hpp>

#include <gears/Lock.hpp>
#include <gears/Condition.hpp>
#include <gears/Time.hpp>
#include <gears/CompositeActiveObject.hpp>
#include <gears/DelegateActiveObject.hpp>

#include <core/Frontends/FCGIRequestHandler.hpp>

namespace AdServer
{
namespace Frontends
{
  // FCGIServer
  class FCGIServer: public Gears::CompositeActiveObject
  {
  public:
    DECLARE_EXCEPTION(Exception, Gears::DescriptiveException);

    struct State
    {
      State() noexcept;
    };

    typedef std::shared_ptr<State> State_var;

  public:
    FCGIServer(
      Gears::Logger_var logger,
      AdServer::HTTP::FCGIRequestHandler_var frontend,
      Gears::ActiveObjectCallback_var callback,
      const Gears::SubString& bind_address,
      unsigned long backlog,
      unsigned long join_threads)
      /*throw (Gears::Exception)*/;

    virtual
    ~FCGIServer() noexcept;

    HTTP::FCGIRequestHandler_var
    handler() noexcept;

    /*
    virtual void
    deactivate_object()
    ;
    */

    virtual void
    wait_object()
      /*throw (Exception, Gears::Exception)*/;

  protected:
    typedef boost::asio::local::stream_protocol::endpoint EndpointType;
    typedef boost::asio::local::stream_protocol::acceptor AcceptorType;
    class Connection;
    typedef std::shared_ptr<Connection> Connection_var;

    class ResponseWriter;

    // wrapper for FCGI::HttpResponse that implement
    // response writing by call (instead return context)
    struct Response
    {
    public:
      Response(Connection_var conn);

      FCGI::HttpResponse&
      response();

      void
      send(int code);

    private:
      std::vector<char> wbuf_;
      std::unique_ptr<FCGI::HttpResponse> response_;
    };

  protected:
    Gears::Logger*
    logger_i_() noexcept;

    void
    create_accept_stub_();

    void
    handle_accept(
      const Connection_var& accepted_connection,
      const boost::system::error_code& error);

  private:
    Gears::ActiveObjectCallback_var callback_;
    Gears::Logger_var logger_;
    HTTP::FCGIRequestHandler_var frontend_;

    std::shared_ptr<boost::asio::io_service> io_service_;
    std::shared_ptr<AcceptorType> acceptor_;

    State_var state_;

    std::atomic<int> accept_ordered_;
  };

  typedef std::shared_ptr<FCGIServer> FCGIServer_var;
}
}
