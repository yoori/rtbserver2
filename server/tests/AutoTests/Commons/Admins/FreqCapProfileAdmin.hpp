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

#ifndef __AUTOTESTS_COMMONS_ADMINS_FREQCAPPROFILEADMIN_HPP
#define __AUTOTESTS_COMMONS_ADMINS_FREQCAPPROFILEADMIN_HPP

#include "Admins.hpp"

namespace AutoTest
{
  class FreqCapProfileAdmin:  
    public BaseAdminCmd<FreqCapProfileAdmin, 4>  
  {  
    static const unsigned long DEFAULT_SKIP = 1;  
    public:    
      class Expected      
      {      
        friend class FreqCapProfileAdmin;        
        public:        
          Expected() {}          
          Expected& fc_id (const std::string& val);          
          Expected& wirtual (const std::string& val);          
          Expected& total_impressions (const std::string& val);          
          Expected& last_impressions (const std::string& val);          
                
          enum FieldName          
          {          
            FC_ID = 0,            
            VIRTUAL,            
            TOTAL_IMPRESSIONS,            
            LAST_IMPRESSIONS            
          };          
        protected:        
          FieldIndexMap values_;          
      };      
        
    public:    
      typedef BaseAdminCmd<FreqCapProfileAdmin, FIELDS_COUNT> Base;    
        
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
        make_admin_cmd(*this, "print-freq-cap", address, params, static_cast<size_t>(service));      
      }      
      FreqCapProfileAdmin(      
        const char* address,      
        const char* uid,      
        bool temp = false,      
        UserInfoSrv service = UserInfoManagerController      
      )      
        :Base(DEFAULT_SKIP)      
      {      
        make_cmd(address, uid, temp, service);      
      }      
      FreqCapProfileAdmin(      
        const std::string& address,      
        const char* uid,      
        bool temp = false,      
        UserInfoSrv service = UserInfoManagerController      
      )      
        :Base(DEFAULT_SKIP)      
      {      
        make_cmd(address.c_str(), uid, temp, service);      
      }      
      FreqCapProfileAdmin(      
        const char* address,      
        const std::string& uid,      
        bool temp = false,      
        UserInfoSrv service = UserInfoManagerController      
      )      
        :Base(DEFAULT_SKIP)      
      {      
        make_cmd(address, uid.c_str(), temp, service);      
      }      
      FreqCapProfileAdmin(      
        const std::string& address,      
        const std::string& uid,      
        bool temp = false,      
        UserInfoSrv service = UserInfoManagerController      
      )      
        :Base(DEFAULT_SKIP)      
      {      
        make_cmd(address.c_str(), uid.c_str(), temp, service);      
      }      
      const char* fc_id (unsigned int i = 0);      
      const char* wirtual (unsigned int i = 0);      
      const char* total_impressions (unsigned int i = 0);      
      const char* last_impressions (unsigned int i = 0);      
      bool check(const Expected& expected, bool exist = true)      
        /*throw(eh::Exception)*/;      
      bool check(const std::string& expected, bool exist = true)      
        /*throw(eh::Exception)*/;      
  };  
    
}
namespace AutoTest
{
  inline  
  FreqCapProfileAdmin::Expected&  
  FreqCapProfileAdmin::Expected::fc_id(const std::string& val)  
  {  
     values_.insert(std::make_pair(FC_ID, ComparableRegExp(val)));  
     return *this;  
  }  
  inline  
  const char*  
  FreqCapProfileAdmin::fc_id (unsigned int i)  
  {  
    if (empty() || values_[0].size() != FIELDS_COUNT) return 0;  
    return values_[i][Expected::FC_ID].c_str();  
  }  
  inline  
  FreqCapProfileAdmin::Expected&  
  FreqCapProfileAdmin::Expected::wirtual(const std::string& val)  
  {  
     values_.insert(std::make_pair(VIRTUAL, ComparableRegExp(val)));  
     return *this;  
  }  
  inline  
  const char*  
  FreqCapProfileAdmin::wirtual (unsigned int i)  
  {  
    if (empty() || values_[0].size() != FIELDS_COUNT) return 0;  
    return values_[i][Expected::VIRTUAL].c_str();  
  }  
  inline  
  FreqCapProfileAdmin::Expected&  
  FreqCapProfileAdmin::Expected::total_impressions(const std::string& val)  
  {  
     values_.insert(std::make_pair(TOTAL_IMPRESSIONS, ComparableRegExp(val)));  
     return *this;  
  }  
  inline  
  const char*  
  FreqCapProfileAdmin::total_impressions (unsigned int i)  
  {  
    if (empty() || values_[0].size() != FIELDS_COUNT) return 0;  
    return values_[i][Expected::TOTAL_IMPRESSIONS].c_str();  
  }  
  inline  
  FreqCapProfileAdmin::Expected&  
  FreqCapProfileAdmin::Expected::last_impressions(const std::string& val)  
  {  
     values_.insert(std::make_pair(LAST_IMPRESSIONS, ComparableRegExp(val)));  
     return *this;  
  }  
  inline  
  const char*  
  FreqCapProfileAdmin::last_impressions (unsigned int i)  
  {  
    if (empty() || values_[0].size() != FIELDS_COUNT) return 0;  
    return values_[i][Expected::LAST_IMPRESSIONS].c_str();  
  }  
}
#endif  // __AUTOTESTS_COMMONS_ADMINS_FREQCAPPROFILEADMIN_HPP

