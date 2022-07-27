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
#ifndef _USER_INFO_SVCS_USER_INFO_EXCHANGER_MAIN_HPP_
#define _USER_INFO_SVCS_USER_INFO_EXCHANGER_MAIN_HPP_

#include <eh/Exception.hpp>
#include <Generics/Time.hpp>
#include <Generics/Singleton.hpp>

#include <CORBACommons/CorbaAdapters.hpp>
#include <Commons/ProcessControlVarsImpl.hpp>

#include <UserInfoSvcs/UserInfoExchanger/UserInfoExchanger.hpp>

#include "UserInfoExchangerProxyImpl.hpp"


class UserInfoExchangerProxyApp_
  : public AdServer::Commons::ProcessControlVarsLoggerImpl
{
public:
  DECLARE_EXCEPTION(Exception, eh::DescriptiveException);
  DECLARE_EXCEPTION(InvalidArgument, Exception);

public:
  UserInfoExchangerProxyApp_() /*throw (eh::Exception)*/;

  void main(int& argc, char** argv) noexcept;

protected:
  /** CorbaCommons::ProcessControlImpl methods */
  virtual void shutdown(CORBA::Boolean wait_for_completion)
    /*throw(CORBA::SystemException)*/;

  virtual CORBACommons::IProcessControl::ALIVE_STATUS
  is_alive() /*throw(CORBA::SystemException)*/;

private:
  typedef
    AdServer::UserInfoSvcs::
    UserInfoExchangerProxyImpl::UserInfoExchangerProxyConfig
    ConfigType;
  
  virtual ~UserInfoExchangerProxyApp_() noexcept{};

  const ConfigType& config() const noexcept;

private:
  typedef std::unique_ptr<ConfigType> ConfigPtr;

  CORBACommons::CorbaServerAdapter_var corba_server_adapter_;
  CORBACommons::CorbaConfig corba_config_;

  AdServer::UserInfoSvcs::UserInfoExchangerProxyImpl_var
    user_info_exchanger_proxy_impl_;

  ConfigPtr configuration_;
  
  typedef Sync::PosixMutex ShutdownMutex;
  typedef Sync::PosixGuard ShutdownGuard;

  ShutdownMutex shutdown_lock_;
};

typedef ReferenceCounting::SmartPtr<UserInfoExchangerProxyApp_>
  UserInfoExchangerProxyApp_var;

typedef Generics::Singleton<
  UserInfoExchangerProxyApp_, UserInfoExchangerProxyApp_var>
  UserInfoExchangerProxyApp;


/** Inlines */

inline
const UserInfoExchangerProxyApp_::ConfigType&
UserInfoExchangerProxyApp_::config() const noexcept
{
  return *configuration_.get();
}

#endif /*_USER_INFO_SVCS_USER_INFO_EXCHANGER_MAIN_HPP_*/

