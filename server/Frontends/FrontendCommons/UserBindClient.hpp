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
#ifndef USERBINDCLIENT_HPP_
#define USERBINDCLIENT_HPP_

#include <eh/Exception.hpp>
#include <Sync/SyncPolicy.hpp>
#include <ReferenceCounting/AtomicImpl.hpp>
#include <CORBACommons/CorbaAdapters.hpp>

#include <xsd/Frontends/FeConfig.hpp>
#include <UserInfoSvcs/UserBindController/UserBindOperationDistributor.hpp>

namespace FrontendCommons
{
  class UserBindClient:
    public virtual ReferenceCounting::AtomicImpl,
    public Generics::CompositeActiveObject
  {
  public:
    typedef xsd::AdServer::Configuration::
      CommonFeConfigurationType::UserBindControllerGroup_sequence
      UserBindControllerGroupSeq;

  public:
    UserBindClient(
      const UserBindControllerGroupSeq& user_bind_controller_group,
      const CORBACommons::CorbaClientAdapter* corba_client_adapter,
      Logging::Logger* logger)
      noexcept;

    virtual ~UserBindClient() noexcept {};

    AdServer::UserInfoSvcs::UserBindMapper*
    user_bind_mapper() noexcept;

  private:
    AdServer::UserInfoSvcs::UserBindOperationDistributor_var user_bind_mapper_;
    //AdServer::UserInfoSvcs::UserBindMapper_var user_bind_mapper_;
  };

  typedef ReferenceCounting::SmartPtr<UserBindClient>
    UserBindClient_var;
}

#endif /*USERBINDCLIENT_HPP_*/
