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
#ifndef COMMONS_ZMQSOCKETHOLDER_HPP_
#define COMMONS_ZMQSOCKETHOLDER_HPP_

#include <ReferenceCounting/AtomicImpl.hpp>
#include <ReferenceCounting/SmartPtr.hpp>
#include <Sync/SyncPolicy.hpp>
#include <Commons/zmq.hpp>

namespace AdServer
{
namespace Commons
{
  struct ZmqSocketHolder: public ReferenceCounting::AtomicImpl
  {
  public:
    DECLARE_EXCEPTION(Exception, eh::DescriptiveException);

    typedef Sync::Policy::PosixThread SyncPolicy;

    struct SendGuard
    {
    public:
      SendGuard(ZmqSocketHolder& holder);

      virtual
      ~SendGuard() noexcept;

      bool
      send(
        zmq::message_t& msg,
        int flags,
        const char* part_name)
        /*throw(eh::Exception)*/;

    protected:
      ZmqSocketHolder& socket_holder_;
    };

  public:
    ZmqSocketHolder(zmq::context_t& zmq_context, const char* address)
      /*throw(eh::Exception)*/;

    ZmqSocketHolder(zmq::context_t& zmq_context, int type)
      /*throw(eh::Exception)*/;

    zmq::socket_t&
    sock_i()
    {
      return sock_;
    }

  protected:
    virtual ~ZmqSocketHolder() noexcept
    {}

    void
    init_sock_();

  protected:
    SyncPolicy::Mutex lock_;
    zmq::socket_t sock_;
  };

  typedef ReferenceCounting::SmartPtr<ZmqSocketHolder>
    ZmqSocketHolder_var;
}
}

#endif /*COMMONS_ZMQSOCKETHOLDER_HPP_*/
