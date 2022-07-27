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
#ifndef USER_INFO_CLUSTER_CONTROLLER_HPP
#define USER_INFO_CLUSTER_CONTROLLER_HPP

#include <ReferenceCounting/ReferenceCounting.hpp>
#include <eh/Exception.hpp>
#include <Generics/ActiveObject.hpp>
#include <CORBACommons/CorbaAdapters.hpp>
#include <CORBACommons/ProcessControl.hpp>
#include <UserInfoSvcs/UserInfoManagerController/UserInfoClusterControl.hpp>

#include <UserInfoSvcs/UserInfoManager/UserInfoManager.hpp>
#include <UserInfoSvcs/UserInfoManager/UserInfoManagerControl.hpp>

namespace AdServer
{
  namespace UserInfoSvcs
  {
    typedef std::vector<CORBACommons::CorbaObjectRef> UIMRefVector;
    typedef std::vector<AdServer::UserInfoSvcs::UserInfoManager_var> UIMVector;

    class UserInfoClusterControlImpl:
      public CORBACommons::ProcessControlDefault<
        POA_CORBACommons::IProcessControl>
    {
    public:
      UserInfoClusterControlImpl()
        noexcept;

      UserInfoClusterControlImpl(
        const CORBACommons::CorbaClientAdapter* corba_client_adapter,
        const UIMRefVector& uims,
        const std::vector<std::string>& hosts)
        noexcept;

      virtual CORBACommons::IProcessControl::ALIVE_STATUS is_alive() noexcept;

      virtual char* comment() /*throw(CORBACommons::OutOfMemory)*/;

    private:
      virtual
      ~UserInfoClusterControlImpl() noexcept;

      CORBACommons::CorbaClientAdapter_var corba_client_adapter_;
      UIMVector uims_;
      std::vector<std::string> hosts_;
    };
    
    typedef ReferenceCounting::SmartPtr<UserInfoClusterControlImpl>
      UserInfoClusterControlImpl_var;

  }
}

#endif //USER_INFO_CLUSTER_CONTROLLER_HPP
