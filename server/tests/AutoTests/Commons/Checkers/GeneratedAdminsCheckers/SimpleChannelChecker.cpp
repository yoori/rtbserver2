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

#include <tests/AutoTests/Commons/Admins/AdminsContainer.hpp>
#include "SimpleChannelChecker.hpp"
          
#include <tests/AutoTests/Commons/Stats/ORMStats.hpp>

namespace AutoTest
{
  bool  
  SimpleChannelChecker::check(bool throw_error)  
    /*throw (CheckFailed, eh::Exception)*/  
  {
    AdminExistCheck remote_exists =
      !expected_.has_status() ||
         expected_.status() == "A" ||
           expected_.status() == "W"?
        exists_: AEC_NOT_EXISTS;

    AdminsArray<SimpleChannelAdmin, CT_ALL> central_admins;

    central_admins.initialize(
      test_,
      CTE_CENTRAL,
      STE_CAMPAIGN_SERVER,
      id_);

    AdminsArray<SimpleChannelAdmin, CT_ALL> remote_admins;

    remote_admins.initialize(
      test_,
      CTE_ALL_REMOTE,
      STE_CAMPAIGN_SERVER,
      id_);

    if (central_admins.empty() && remote_admins.empty())
    {
      throw CheckFailed("Admin containers are empty!");
    }

    central_admins.log(Logger::thlog());
    remote_admins.log(Logger::thlog());

    return
      (central_admins.empty() ||
        admin_checker(
          central_admins,
          expected_,
          exists_).
            check(throw_error)) &&
      (remote_admins.empty() ||
        admin_checker(
          remote_admins,
          remote_exists == AEC_EXISTS? expected_: Expected(),
          remote_exists).
            check(throw_error));
        
  }  
}
