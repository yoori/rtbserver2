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

#ifndef __AUTOTESTS_COMMONS_ADMINS_COLOCATIONADMIN_HPP
#define __AUTOTESTS_COMMONS_ADMINS_COLOCATIONADMIN_HPP

#include "Admins.hpp"

namespace AutoTest
{
  class ColocationAdmin:  
    public BaseAdminCmd<ColocationAdmin, 4>  
  {  
    public:    
      class Expected      
      {      
        friend class ColocationAdmin;        
        public:        
          Expected() {}          
          Expected& colo_id (const std::string& val);          
          Expected& colo_id(unsigned long val);          
          Expected& colo_rate_id (const std::string& val);          
          Expected& colo_rate_id(unsigned long val);          
          Expected& account_id (const std::string& val);          
          Expected& account_id(unsigned long val);          
          Expected& revenue_share (const std::string& val);          
          Expected& revenue_share(unsigned long val);          
                
          enum FieldName          
          {          
            COLO_ID = 0,            
            COLO_RATE_ID,            
            ACCOUNT_ID,            
            REVENUE_SHARE            
          };          
        protected:        
          FieldIndexMap values_;          
      };      
        
    public:    
      typedef BaseAdminCmd<ColocationAdmin, FIELDS_COUNT> Base;    
        
      void make_cmd (const char* address,      
        const char* colo      
      )      
      {      
        address_ = address;        
        AdminParams params;        
        if (colo)        
        {        
          params.push_back(AdminParamPair("colo_id=", colo));          
        }        
        make_admin_cmd(*this, "colocations", address, params, static_cast<size_t>(CampaignManager));      
      }      
      ColocationAdmin(      
        const char* address,      
        const char* colo      
      )      
      {      
        make_cmd(address, colo);      
      }      
      ColocationAdmin(      
        const std::string& address,      
        const char* colo      
      )      
      {      
        make_cmd(address.c_str(), colo);      
      }      
      ColocationAdmin(      
        const char* address,      
        const std::string& colo      
      )      
      {      
        make_cmd(address, colo.c_str());      
      }      
      ColocationAdmin(      
        const std::string& address,      
        const std::string& colo      
      )      
      {      
        make_cmd(address.c_str(), colo.c_str());      
      }      
      ColocationAdmin(      
        const char* address,      
        unsigned long colo      
      )      
      {      
        make_cmd(address, strof(colo).c_str());      
      }      
      ColocationAdmin(      
        const std::string& address,      
        unsigned long colo      
      )      
      {      
        make_cmd(address.c_str(), strof(colo).c_str());      
      }      
      const char* colo_id (unsigned int i = 0);      
      const char* colo_rate_id (unsigned int i = 0);      
      const char* account_id (unsigned int i = 0);      
      const char* revenue_share (unsigned int i = 0);      
      bool check(const Expected& expected, bool exist = true)      
        /*throw(eh::Exception)*/;      
      bool check(const std::string& expected, bool exist = true)      
        /*throw(eh::Exception)*/;      
  };  
    
}
namespace AutoTest
{
  inline  
  ColocationAdmin::Expected&  
  ColocationAdmin::Expected::colo_id(const std::string& val)  
  {  
     values_.insert(std::make_pair(COLO_ID, ComparableRegExp(val)));  
     return *this;  
  }  
  inline  
  const char*  
  ColocationAdmin::colo_id (unsigned int i)  
  {  
    if (empty() || values_[0].size() != FIELDS_COUNT) return 0;  
    return values_[i][Expected::COLO_ID].c_str();  
  }  
  inline  
  ColocationAdmin::Expected&  
  ColocationAdmin::Expected::colo_id(unsigned long val)  
  {  
     values_.insert(std::make_pair(COLO_ID, ComparableRegExp(strof(val))));  
     return *this;  
  }  
  inline  
  ColocationAdmin::Expected&  
  ColocationAdmin::Expected::colo_rate_id(const std::string& val)  
  {  
     values_.insert(std::make_pair(COLO_RATE_ID, ComparableRegExp(val)));  
     return *this;  
  }  
  inline  
  const char*  
  ColocationAdmin::colo_rate_id (unsigned int i)  
  {  
    if (empty() || values_[0].size() != FIELDS_COUNT) return 0;  
    return values_[i][Expected::COLO_RATE_ID].c_str();  
  }  
  inline  
  ColocationAdmin::Expected&  
  ColocationAdmin::Expected::colo_rate_id(unsigned long val)  
  {  
     values_.insert(std::make_pair(COLO_RATE_ID, ComparableRegExp(strof(val))));  
     return *this;  
  }  
  inline  
  ColocationAdmin::Expected&  
  ColocationAdmin::Expected::account_id(const std::string& val)  
  {  
     values_.insert(std::make_pair(ACCOUNT_ID, ComparableRegExp(val)));  
     return *this;  
  }  
  inline  
  const char*  
  ColocationAdmin::account_id (unsigned int i)  
  {  
    if (empty() || values_[0].size() != FIELDS_COUNT) return 0;  
    return values_[i][Expected::ACCOUNT_ID].c_str();  
  }  
  inline  
  ColocationAdmin::Expected&  
  ColocationAdmin::Expected::account_id(unsigned long val)  
  {  
     values_.insert(std::make_pair(ACCOUNT_ID, ComparableRegExp(strof(val))));  
     return *this;  
  }  
  inline  
  ColocationAdmin::Expected&  
  ColocationAdmin::Expected::revenue_share(const std::string& val)  
  {  
     values_.insert(std::make_pair(REVENUE_SHARE, ComparableRegExp(val)));  
     return *this;  
  }  
  inline  
  const char*  
  ColocationAdmin::revenue_share (unsigned int i)  
  {  
    if (empty() || values_[0].size() != FIELDS_COUNT) return 0;  
    return values_[i][Expected::REVENUE_SHARE].c_str();  
  }  
  inline  
  ColocationAdmin::Expected&  
  ColocationAdmin::Expected::revenue_share(unsigned long val)  
  {  
     values_.insert(std::make_pair(REVENUE_SHARE, ComparableRegExp(strof(val))));  
     return *this;  
  }  
}
#endif  // __AUTOTESTS_COMMONS_ADMINS_COLOCATIONADMIN_HPP

