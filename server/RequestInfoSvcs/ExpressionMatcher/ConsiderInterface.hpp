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
#ifndef REQUESTINFOSVCS_EXPRESSIONMATCHER_CONSIDERINTERFACE_HPP_
#define REQUESTINFOSVCS_EXPRESSIONMATCHER_CONSIDERINTERFACE_HPP_

#include "InventoryActionProcessor.hpp"

namespace AdServer
{
  namespace RequestInfoSvcs
  {
    class ConsiderInterface
    {
    public:
      virtual
      ~ConsiderInterface() noexcept
      {}

      virtual void
      consider_click(
        const AdServer::Commons::RequestId& request_id,
        const Generics::Time& time)
        noexcept = 0;

      virtual void
      consider_impression(
        const AdServer::Commons::UserId& user_id,
        const AdServer::Commons::RequestId& request_id,
        const Generics::Time& time,
        const ChannelIdSet& channels)
        noexcept = 0;
    };
  }
}

#endif /* REQUESTINFOSVCS_EXPRESSIONMATCHER_CONSIDERINTERFACE_HPP_ */
