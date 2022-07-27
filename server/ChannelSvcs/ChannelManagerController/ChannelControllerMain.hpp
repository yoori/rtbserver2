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

#ifndef AD_CHANNEL_SVCS_CONTROLLER_MAIN_HPP_
#define AD_CHANNEL_SVCS_CONTROLLER_MAIN_HPP_

#include <eh/Exception.hpp>
#include <Generics/Time.hpp>
#include <Generics/Singleton.hpp>

#include <CORBACommons/CorbaAdapters.hpp>
#include <CORBACommons/ProcessControl.hpp>
#include <Commons/ProcessControlVarsImpl.hpp>

#include <xsd/ChannelSvcs/ChannelManagerControllerConfig.hpp>
#include "ChannelControllerImpl.hpp"

class ChannelControllerApp_:
  public AdServer::Commons::ProcessControlVarsLoggerImpl
{
public:
  DECLARE_EXCEPTION(Exception, eh::DescriptiveException);
  //DECLARE_EXCEPTION(InvalidArgument, Exception);

public:
  ChannelControllerApp_() /*throw (eh::Exception)*/;
  virtual ~ChannelControllerApp_() noexcept{};

  void main(int& argc, char** argv) noexcept;

protected:
  //
  // IDL:CORBACommons/IProcessControl/shutdown:1.0
  //
  virtual void shutdown(CORBA::Boolean wait_for_completion)
    /*throw(CORBA::SystemException)*/;

  //
  // IDL:CORBACommons/IProcessControl/is_alive:1.0
  //
  virtual CORBACommons::IProcessControl::ALIVE_STATUS
  is_alive() /*throw(CORBA::SystemException)*/;

private:

  typedef std::unique_ptr<xsd::AdServer::Configuration::
    ChannelControllerConfigType> ConfigPtr;

private:
  void load_config_(const char* name) /*throw(Exception)*/;
  void init_corba_() /*throw(Exception)*/;

private:
  CORBACommons::CorbaServerAdapter_var corba_server_adapter_;
  CORBACommons::CorbaConfig corba_config_;

  ConfigPtr configuration_;

  AdServer::ChannelSvcs::ChannelControllerImpl_var controller_impl_;

  typedef Sync::PosixMutex ShutdownMutex;
  typedef Sync::PosixGuard ShutdownGuard;

  ShutdownMutex shutdown_lock_;
};

typedef ReferenceCounting::SmartPtr<ChannelControllerApp_>
  ChannelControllerApp_var;

typedef Generics::Singleton<ChannelControllerApp_, ChannelControllerApp_var>
  ChannelControllerApp;

#endif /*AD_CHANNEL_SVCS_CONTROLLER_MAIN_HPP_*/
