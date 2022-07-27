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
#ifndef ACCEPTORDESCRIPTORHANDLER_HPP_
#define ACCEPTORDESCRIPTORHANDLER_HPP_

#include "DescriptorHandlerPoller.hpp"

namespace AdServer
{
  class AcceptorDescriptorHandler: public DescriptorHandler
  {
  public:
    AcceptorDescriptorHandler(
      unsigned long port,
      DescriptorHandlerPoller::Proxy* poller_proxy)
      /*throw(Exception)*/;

    virtual int
    fd() const noexcept;

    // return false if need stop loop
    virtual unsigned long
    read() /*throw(Exception)*/;

    // return false if need stop loop
    virtual unsigned long
    write() /*throw(Exception)*/;

    virtual void
    stopped() noexcept;

  protected:
    virtual
    ~AcceptorDescriptorHandler() noexcept;

    void
    accept_() /*throw(Exception)*/;

    virtual DescriptorHandler_var
    create_descriptor_handler(int fd)
      noexcept = 0;

  protected:
    DescriptorHandlerPoller::Proxy_var proxy_;
    int fd_;
  };
}

namespace AdServer
{
}

#endif /*ACCEPTORDESCRIPTORHANDLER_HPP_*/
