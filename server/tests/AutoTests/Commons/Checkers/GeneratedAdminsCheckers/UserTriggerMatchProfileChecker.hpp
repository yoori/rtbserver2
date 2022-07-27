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

#ifndef __AUTOTESTS_COMMONS_ADMINS_USERTRIGGERMATCHPROFILECHECKER_HPP
#define __AUTOTESTS_COMMONS_ADMINS_USERTRIGGERMATCHPROFILECHECKER_HPP

#include <tests/AutoTests/Commons/Admins/UserTriggerMatchProfileAdmin.hpp>
#include <tests/AutoTests/Commons/Checkers/AdminsChecker.hpp>
#include <tests/AutoTests/Commons/Admins/AdminsContainer.hpp>
#include <tests/AutoTests/Commons/Checkers/Checker.hpp>

namespace AutoTest
{
  template<class ExpectedType, CheckType ch = CT_ONE>
  class UserTriggerMatchProfileChecker_:  
    public AutoTest::Checker  
  {  
    public:    
            
      typedef ExpectedType Expected;

      UserTriggerMatchProfileChecker_(      
        BaseUnit* test,      
        const std::string& uid,      
        bool temp,      
        const Expected& expected,      
        AdminExistCheck exists = AEC_EXISTS) :      
        test_(test),      
        uid_(uid),      
        temp_(temp),      
        expected_(expected),      
        exists_(exists)      
        {}      
            
      virtual ~UserTriggerMatchProfileChecker_() noexcept {}      
            
      bool check(bool throw_error = true) /*throw (CheckFailed, eh::Exception)*/;      
            
    private:    
            
      BaseUnit* test_;      
      std::string uid_;      
      bool temp_;      
      Expected expected_;      
      AdminExistCheck exists_;      
            
  };

  typedef UserTriggerMatchProfileChecker_<UserTriggerMatchProfileAdmin::Expected> UserTriggerMatchProfileChecker;
  typedef UserTriggerMatchProfileChecker_<std::string, CT_ONE_NOT_EXPECTED> UserTriggerMatchProfileEmptyChecker;
}

#include "UserTriggerMatchProfileChecker.tpp"

#endif  // __AUTOTESTS_COMMONS_ADMINS_USERTRIGGERMATCHPROFILECHECKER_HPP

