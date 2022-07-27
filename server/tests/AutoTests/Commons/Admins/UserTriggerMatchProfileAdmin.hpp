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

#ifndef __AUTOTESTS_COMMONS_ADMINS_USERTRIGGERMATCHPROFILEADMIN_HPP
#define __AUTOTESTS_COMMONS_ADMINS_USERTRIGGERMATCHPROFILEADMIN_HPP

#include "Admins.hpp"

namespace AutoTest
{
  class UserTriggerMatchProfileAdmin:  
    public BaseAdminCmd<UserTriggerMatchProfileAdmin, 5>  
  {  
    public:    
      class Expected      
      {      
        friend class UserTriggerMatchProfileAdmin;        
        public:        
          Expected() {}          
          Expected& user_id (const std::string& val);          
          Expected& page_matches (const std::string& val);          
          Expected& search_matches (const std::string& val);          
          Expected& url_matches (const std::string& val);          
          Expected& requests (const std::string& val);          
                
          enum FieldName          
          {          
            USER_ID = 0,            
            PAGE_MATCHES,            
            SEARCH_MATCHES,            
            URL_MATCHES,            
            REQUESTS            
          };          
        protected:        
          FieldIndexMap values_;          
      };      
        
    public:    
      typedef BaseAdminCmd<UserTriggerMatchProfileAdmin, FIELDS_COUNT> Base;    
        
      void make_cmd (const char* address,      
        const char* uid,      
        bool temp      
      )      
      {      
        address_ = address;        
        AdminParams params;        
        if (uid)        
        {        
          params.push_back(AdminParamPair("--user_id=", uid));          
        }        
        if (temp)        
        {        
          params.push_back(AdminParamPair("--temporary", ""));          
        }        
        make_admin_cmd(*this, "print-user-trigger-match", address, params, static_cast<size_t>(ExpressionMatcher));      
      }      
      UserTriggerMatchProfileAdmin(      
        const char* address,      
        const char* uid,      
        bool temp = false      
      )      
      {      
        make_cmd(address, uid, temp);      
      }      
      UserTriggerMatchProfileAdmin(      
        const std::string& address,      
        const char* uid,      
        bool temp = false      
      )      
      {      
        make_cmd(address.c_str(), uid, temp);      
      }      
      UserTriggerMatchProfileAdmin(      
        const char* address,      
        const std::string& uid,      
        bool temp = false      
      )      
      {      
        make_cmd(address, uid.c_str(), temp);      
      }      
      UserTriggerMatchProfileAdmin(      
        const std::string& address,      
        const std::string& uid,      
        bool temp = false      
      )      
      {      
        make_cmd(address.c_str(), uid.c_str(), temp);      
      }      
      const char* user_id (unsigned int i = 0);      
      const char* page_matches (unsigned int i = 0);      
      const char* search_matches (unsigned int i = 0);      
      const char* url_matches (unsigned int i = 0);      
      const char* requests (unsigned int i = 0);      
      bool check(const Expected& expected, bool exist = true)      
        /*throw(eh::Exception)*/;      
      bool check(const std::string& expected, bool exist = true)      
        /*throw(eh::Exception)*/;      
  };  
    
}
namespace AutoTest
{
  inline  
  UserTriggerMatchProfileAdmin::Expected&  
  UserTriggerMatchProfileAdmin::Expected::user_id(const std::string& val)  
  {  
     values_.insert(std::make_pair(USER_ID, ComparableRegExp(val)));  
     return *this;  
  }  
  inline  
  const char*  
  UserTriggerMatchProfileAdmin::user_id (unsigned int i)  
  {  
    if (empty() || values_[0].size() != FIELDS_COUNT) return 0;  
    return values_[i][Expected::USER_ID].c_str();  
  }  
  inline  
  UserTriggerMatchProfileAdmin::Expected&  
  UserTriggerMatchProfileAdmin::Expected::page_matches(const std::string& val)  
  {  
     values_.insert(std::make_pair(PAGE_MATCHES, ComparableRegExp(val)));  
     return *this;  
  }  
  inline  
  const char*  
  UserTriggerMatchProfileAdmin::page_matches (unsigned int i)  
  {  
    if (empty() || values_[0].size() != FIELDS_COUNT) return 0;  
    return values_[i][Expected::PAGE_MATCHES].c_str();  
  }  
  inline  
  UserTriggerMatchProfileAdmin::Expected&  
  UserTriggerMatchProfileAdmin::Expected::search_matches(const std::string& val)  
  {  
     values_.insert(std::make_pair(SEARCH_MATCHES, ComparableRegExp(val)));  
     return *this;  
  }  
  inline  
  const char*  
  UserTriggerMatchProfileAdmin::search_matches (unsigned int i)  
  {  
    if (empty() || values_[0].size() != FIELDS_COUNT) return 0;  
    return values_[i][Expected::SEARCH_MATCHES].c_str();  
  }  
  inline  
  UserTriggerMatchProfileAdmin::Expected&  
  UserTriggerMatchProfileAdmin::Expected::url_matches(const std::string& val)  
  {  
     values_.insert(std::make_pair(URL_MATCHES, ComparableRegExp(val)));  
     return *this;  
  }  
  inline  
  const char*  
  UserTriggerMatchProfileAdmin::url_matches (unsigned int i)  
  {  
    if (empty() || values_[0].size() != FIELDS_COUNT) return 0;  
    return values_[i][Expected::URL_MATCHES].c_str();  
  }  
  inline  
  UserTriggerMatchProfileAdmin::Expected&  
  UserTriggerMatchProfileAdmin::Expected::requests(const std::string& val)  
  {  
     values_.insert(std::make_pair(REQUESTS, ComparableRegExp(val)));  
     return *this;  
  }  
  inline  
  const char*  
  UserTriggerMatchProfileAdmin::requests (unsigned int i)  
  {  
    if (empty() || values_[0].size() != FIELDS_COUNT) return 0;  
    return values_[i][Expected::REQUESTS].c_str();  
  }  
}
#endif  // __AUTOTESTS_COMMONS_ADMINS_USERTRIGGERMATCHPROFILEADMIN_HPP

