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
#include "Command.hpp"
#include "Admins.hpp"

namespace AutoTest
{

  struct ServiceDsc
  {
    const char* name;
    const char* admin;
    ServiceTypeEnum srv_type;
  };

  const ServiceDsc SERVICES[] =
  {
    { "CampaignManager", "CampaignAdmin", STE_CAMPAIGN_MANAGER },
    { "CampaignServer", "CampaignAdmin",  STE_CAMPAIGN_SERVER },
    { "UserInfoManager",  "UserInfoAdmin", STE_USER_INFO_MANAGER },
    { "UserInfoManagerController", "UserInfoAdmin", STE_USER_INFO_MANAGER_CONTROLLER },
    { "ChannelManagerController", "ChannelAdmin", STE_CHANNEL_CONTROLLER },
    { "ChannelServer", "ChannelAdmin", STE_CHANNEL_SERVER },
    { "ChannelUpdate", "ChannelAdmin", STE_CHANNEL_SERVER },
    { "ChannelSearch", "ChannelSearchAdmin", STE_CHANNEL_SEARCH_SERVER },
    { "RequestInfoManager", "RequestInfoAdmin", STE_REQUEST_INFO_MANAGER },
    { "ExpressionMatcher", "ExpressionMatcherAdmin", STE_EXPRESSION_MATCHER }
  };

  ServiceTypeEnum
  srv_type_by_index(
    size_t srv_id) /*throw(InvalidService)*/
  {
    if (srv_id >= sizeof(SERVICES)/sizeof(*SERVICES))
    {
      Stream::Error error;
      error << "Undefined service#" << srv_id;
      throw InvalidService(error);
    }
    return SERVICES[srv_id].srv_type;
  }


  void make_admin_cmd(
    ShellCmd& cmd,
    const char* aspect,
    const char* address,
    const AdminParams& params,
    size_t srv_id) /*throw(InvalidService, eh::Exception)*/
  {
    if (srv_id >= sizeof(SERVICES)/sizeof(*SERVICES))
    {
      Stream::Error error;
      error << "Undefined service#" << srv_id;
      throw InvalidService(error);
    }
    cmd.clear();
    cmd.add_cmd_i(SERVICES[srv_id].admin);
    cmd.add_cmd_i(aspect);
    for (AdminParams::const_iterator it=params.begin();
         it != params.end(); ++it)
    {
      if (it->first.empty() || *it->first.rbegin() != '=')
      {
        cmd.add_cmd_i(it->first);
        cmd.add_cmd_i(it->second);
      }
      else
      {
        cmd.add_cmd_i(it->first + it->second);
      }
    }
    cmd.add_cmd_i("-r");
    cmd.add_cmd_i(std::string("corbaloc::") + address + "/" +  SERVICES[srv_id].name);
  }
}
