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

#ifndef __AUTOTESTS_COMMONS_ADMINS_HISTORYPROFILEADMIN_HPP
#define __AUTOTESTS_COMMONS_ADMINS_HISTORYPROFILEADMIN_HPP

#include "Admins.hpp"

namespace AutoTest
{
  class HistoryProfileAdmin:  
    public BaseAdminCmd<HistoryProfileAdmin, 3>  
  {  
    static const unsigned long DEFAULT_SKIP = 1;  
    public:    
      class Expected      
      {      
        friend class HistoryProfileAdmin;        
        public:        
          Expected() {}          
          Expected& page_channels (const std::string& val);          
          Expected& search_channels (const std::string& val);          
          Expected& url_channels (const std::string& val);          
                
          enum FieldName          
          {          
            PAGE_CHANNELS = 0,            
            SEARCH_CHANNELS,            
            URL_CHANNELS            
          };          
        protected:        
          FieldIndexMap values_;          
      };      
        
    public:    
      typedef BaseAdminCmd<HistoryProfileAdmin, FIELDS_COUNT> Base;    
        
      void make_cmd (const char* address,      
        const char* uid,      
        bool temp,      
        UserInfoSrv service      
      )      
      {      
        address_ = address;        
        AdminParams params;        
        if (uid)        
        {        
          if (temp)          
          {          
            params.push_back(AdminParamPair("--tuid=", uid));            
          }          
          else          
          {          
            params.push_back(AdminParamPair("--uid=", uid));            
          }          
        }        
        make_admin_cmd(*this, "print-history", address, params, static_cast<size_t>(service));      
      }      
      HistoryProfileAdmin(      
        const char* address,      
        const char* uid,      
        bool temp = false,      
        UserInfoSrv service = UserInfoManagerController      
      )      
        :Base(DEFAULT_SKIP)      
      {      
        make_cmd(address, uid, temp, service);      
      }      
      HistoryProfileAdmin(      
        const std::string& address,      
        const char* uid,      
        bool temp = false,      
        UserInfoSrv service = UserInfoManagerController      
      )      
        :Base(DEFAULT_SKIP)      
      {      
        make_cmd(address.c_str(), uid, temp, service);      
      }      
      HistoryProfileAdmin(      
        const char* address,      
        const std::string& uid,      
        bool temp = false,      
        UserInfoSrv service = UserInfoManagerController      
      )      
        :Base(DEFAULT_SKIP)      
      {      
        make_cmd(address, uid.c_str(), temp, service);      
      }      
      HistoryProfileAdmin(      
        const std::string& address,      
        const std::string& uid,      
        bool temp = false,      
        UserInfoSrv service = UserInfoManagerController      
      )      
        :Base(DEFAULT_SKIP)      
      {      
        make_cmd(address.c_str(), uid.c_str(), temp, service);      
      }      
      const char* page_channels (unsigned int i = 0);      
      const char* search_channels (unsigned int i = 0);      
      const char* url_channels (unsigned int i = 0);      
      bool check(const Expected& expected, bool exist = true)      
        /*throw(eh::Exception)*/;      
      bool check(const std::string& expected, bool exist = true)      
        /*throw(eh::Exception)*/;      
  };  
    
}
namespace AutoTest
{
  inline  
  HistoryProfileAdmin::Expected&  
  HistoryProfileAdmin::Expected::page_channels(const std::string& val)  
  {  
     values_.insert(std::make_pair(PAGE_CHANNELS, ComparableRegExp(val)));  
     return *this;  
  }  
  inline  
  const char*  
  HistoryProfileAdmin::page_channels (unsigned int i)  
  {  
    if (empty() || values_[0].size() != FIELDS_COUNT) return 0;  
    return values_[i][Expected::PAGE_CHANNELS].c_str();  
  }  
  inline  
  HistoryProfileAdmin::Expected&  
  HistoryProfileAdmin::Expected::search_channels(const std::string& val)  
  {  
     values_.insert(std::make_pair(SEARCH_CHANNELS, ComparableRegExp(val)));  
     return *this;  
  }  
  inline  
  const char*  
  HistoryProfileAdmin::search_channels (unsigned int i)  
  {  
    if (empty() || values_[0].size() != FIELDS_COUNT) return 0;  
    return values_[i][Expected::SEARCH_CHANNELS].c_str();  
  }  
  inline  
  HistoryProfileAdmin::Expected&  
  HistoryProfileAdmin::Expected::url_channels(const std::string& val)  
  {  
     values_.insert(std::make_pair(URL_CHANNELS, ComparableRegExp(val)));  
     return *this;  
  }  
  inline  
  const char*  
  HistoryProfileAdmin::url_channels (unsigned int i)  
  {  
    if (empty() || values_[0].size() != FIELDS_COUNT) return 0;  
    return values_[i][Expected::URL_CHANNELS].c_str();  
  }  
}
#endif  // __AUTOTESTS_COMMONS_ADMINS_HISTORYPROFILEADMIN_HPP

