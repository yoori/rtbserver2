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


#ifndef CHANNEL_CLUSTER_CONTROLLER_HPP
#define CHANNEL_CLUSTER_CONTROLLER_HPP

#include <ReferenceCounting/ReferenceCounting.hpp>
#include <eh/Exception.hpp>
#include <Generics/ActiveObject.hpp>
#include <CORBACommons/CorbaAdapters.hpp>
#include <CORBACommons/ProcessControl.hpp>
#include <ChannelSvcs/ChannelManagerController/ChannelClusterControl.hpp>

  class ChannelClusterSessionFactoryImpl :
    public virtual OBV_AdServer::ChannelSvcs::ChannelClusterSession,
    public virtual CORBACommons::ReferenceCounting::CorbaRefCountImpl<
      CORBA::ValueFactoryBase>
  {
  public:
    ChannelClusterSessionFactoryImpl(
      Generics::ActiveObjectCallback* callback = 0) noexcept;

    virtual ~ChannelClusterSessionFactoryImpl() noexcept {};

    virtual CORBA::ValueBase* create_for_unmarshal();

    void report_error(
      Generics::ActiveObjectCallback::Severity severity,
      const String::SubString& description,
      const char* error_code = 0) noexcept;

  private:
    Generics::ActiveObjectCallback_var callback_;

  };

namespace AdServer
{
namespace ChannelSvcs
{
  class ChannelClusterSessionImpl:
    public virtual OBV_AdServer::ChannelSvcs::ChannelClusterSession
  {
  public:
    ChannelClusterSessionImpl(Generics::ActiveObjectCallback* callback)
      noexcept;

    ChannelClusterSessionImpl(
      const AdServer::ChannelSvcs::ProcessControlDescriptionSeq& descr)
      noexcept;

    virtual ~ChannelClusterSessionImpl() noexcept{};

    virtual CORBACommons::IProcessControl::ALIVE_STATUS is_alive() noexcept;

    virtual void shutdown(CORBA::Boolean) noexcept;

    virtual char* comment() /*throw(CORBACommons::OutOfMemory)*/;

    void report_error(
      Generics::ActiveObject* /*object*/,
      Generics::ActiveObjectCallback::Severity /*severity*/,
      const char* /*description*/,
      const char* /*error_code*/) noexcept {} ;

  private:
    Generics::ActiveObjectCallback_var callback_;
  };

  class ChannelClusterSessionFactory
  {
  public:
    DECLARE_EXCEPTION(Exception, eh::DescriptiveException);

    static void init(
      CORBACommons::CorbaClientAdapter& corba_client_adapter,
      Generics::ActiveObjectCallback* callback)
      /*throw(eh::Exception)*/;
  };
}
}

#endif //CHANNEL_CLUSTER_CONTROLLER_HPP

