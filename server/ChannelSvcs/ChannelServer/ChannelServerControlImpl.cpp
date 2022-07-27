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

#include <ReferenceCounting/DefaultImpl.hpp>
#include <ReferenceCounting/ReferenceCounting.hpp>

#include <eh/Exception.hpp>
#include <CORBACommons/CorbaAdapters.hpp>
#include <CORBACommons/ServantImpl.hpp>
#include <ChannelSvcs/ChannelServer/ChannelServer_s.hpp>
#include "ChannelServerControlImpl.hpp"
#include "ChannelServerImpl.hpp"

namespace AdServer
{
namespace ChannelSvcs
{

  /**
   * Implementation of control part ChannelServer
   */
  ChannelServerControlImpl::ChannelServerControlImpl(
      ChannelServerCustomImpl* custom) noexcept
      : custom_impl_(ReferenceCounting::add_ref(custom))
  {
  }

  //
  // IDL:AdServer/ChannelSvcs/ChannelServerControl/set_sources:1.0
  //
  void ChannelServerControlImpl::set_sources(
      const ::AdServer::ChannelSvcs::ChannelServerControl::DBSourceInfo& db_info,
      const ::AdServer::ChannelSvcs::ChunkKeySeq& sources)
      /*throw(AdServer::ChannelSvcs::ImplementationException)*/
  {
    WriteGuard_ guard(lock_);
    custom_impl_->set_sources(db_info, sources);
  }


  //
  // IDL:AdServer/ChannelSvcs/ChannelServerControl/set_proxy_sources:1.0
  //
  void ChannelServerControlImpl::set_proxy_sources(
      const ::AdServer::ChannelSvcs::
      ChannelServerControl::ProxySourceInfo& proxy_info,
      const ::AdServer::ChannelSvcs::ChunkKeySeq& sources)
      /*throw(AdServer::ChannelSvcs::ImplementationException)*/
  {
    custom_impl_->set_proxy_sources(proxy_info, sources);
  }

  //
  // IDL:AdServer/ChannelSvcs/ChannelServerControl/check_configuration:1.0
  //
  ::CORBA::ULong ChannelServerControlImpl::check_configuration()
    noexcept
  {
    return custom_impl_->check_configuration();
  }

  ChannelServerControlImpl::~ChannelServerControlImpl() noexcept
  {
  }

} /* ChannelSvcs */
} /* AdServer */


