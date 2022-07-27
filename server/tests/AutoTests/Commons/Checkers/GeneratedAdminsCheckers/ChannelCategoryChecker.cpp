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
#include "ChannelCategoryChecker.hpp"

namespace AutoTest
{
  bool
  ChannelCategoryChecker::check(bool throw_error)
    /*throw (CheckFailed, eh::Exception)*/
  {  
    AdminsArray<ChannelCategoryAdmin, CT_ALL> admins;
  
    admins.initialize(
      test_,
      CTE_ALL,
      srv_type_by_index(
        static_cast<size_t>(CampaignManager)),
      category_);
    
    return admin_checker(
      admins,
      expected_,
      exists_).check(throw_error);
  }  
}
