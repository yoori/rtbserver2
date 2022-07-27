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

#ifndef __AUTOTESTS_COMMONS_ADMINS_CREATIVEADMIN_HPP
#define __AUTOTESTS_COMMONS_ADMINS_CREATIVEADMIN_HPP

#include "Admins.hpp"

namespace AutoTest
{
  class CreativeAdmin:  
    public BaseAdminCmd<CreativeAdmin, 7>  
  {  
    public:    
      class Expected      
      {      
        friend class CreativeAdmin;        
        public:        
          Expected() {}          
          Expected& ccid (const std::string& val);          
          Expected& ccid(unsigned long val);          
          Expected& campaign_id (const std::string& val);          
          Expected& campaign_id(unsigned long val);          
          Expected& creative_format (const std::string& val);          
          Expected& sizes (const std::string& val);          
          Expected& categories (const std::string& val);          
          Expected& weight (const std::string& val);          
          Expected& status (const std::string& val);          
          bool has_status () const;          
          std::string status () const;          
                
          enum FieldName          
          {          
            CCID = 0,            
            CAMPAIGN_ID,            
            CREATIVE_FORMAT,            
            SIZES,            
            CATEGORIES,            
            WEIGHT,            
            STATUS            
          };          
        protected:        
          FieldIndexMap values_;          
      };      
        
    public:    
      typedef BaseAdminCmd<CreativeAdmin, FIELDS_COUNT> Base;    
        
      void make_cmd (const char* address,      
        const char* ccid      
      )      
      {      
        address_ = address;        
        AdminParams params;        
        if (ccid)        
        {        
          params.push_back(AdminParamPair("ccid=", ccid));          
        }        
        make_admin_cmd(*this, "creative", address, params, static_cast<size_t>(CampaignManager));      
      }      
      CreativeAdmin(      
        const char* address,      
        const char* ccid      
      )      
      {      
        make_cmd(address, ccid);      
      }      
      CreativeAdmin(      
        const std::string& address,      
        const char* ccid      
      )      
      {      
        make_cmd(address.c_str(), ccid);      
      }      
      CreativeAdmin(      
        const char* address,      
        const std::string& ccid      
      )      
      {      
        make_cmd(address, ccid.c_str());      
      }      
      CreativeAdmin(      
        const std::string& address,      
        const std::string& ccid      
      )      
      {      
        make_cmd(address.c_str(), ccid.c_str());      
      }      
      CreativeAdmin(      
        const char* address,      
        unsigned long ccid      
      )      
      {      
        make_cmd(address, strof(ccid).c_str());      
      }      
      CreativeAdmin(      
        const std::string& address,      
        unsigned long ccid      
      )      
      {      
        make_cmd(address.c_str(), strof(ccid).c_str());      
      }      
      const char* ccid (unsigned int i = 0);      
      const char* campaign_id (unsigned int i = 0);      
      const char* creative_format (unsigned int i = 0);      
      const char* sizes (unsigned int i = 0);      
      const char* categories (unsigned int i = 0);      
      const char* weight (unsigned int i = 0);      
      const char* status (unsigned int i = 0);      
      bool check(const Expected& expected, bool exist = true)      
        /*throw(eh::Exception)*/;      
      bool check(const std::string& expected, bool exist = true)      
        /*throw(eh::Exception)*/;      
  };  
    
}
namespace AutoTest
{
  inline  
  CreativeAdmin::Expected&  
  CreativeAdmin::Expected::ccid(const std::string& val)  
  {  
     values_.insert(std::make_pair(CCID, ComparableRegExp(val)));  
     return *this;  
  }  
  inline  
  const char*  
  CreativeAdmin::ccid (unsigned int i)  
  {  
    if (empty() || values_[0].size() != FIELDS_COUNT) return 0;  
    return values_[i][Expected::CCID].c_str();  
  }  
  inline  
  CreativeAdmin::Expected&  
  CreativeAdmin::Expected::ccid(unsigned long val)  
  {  
     values_.insert(std::make_pair(CCID, ComparableRegExp(strof(val))));  
     return *this;  
  }  
  inline  
  CreativeAdmin::Expected&  
  CreativeAdmin::Expected::campaign_id(const std::string& val)  
  {  
     values_.insert(std::make_pair(CAMPAIGN_ID, ComparableRegExp(val)));  
     return *this;  
  }  
  inline  
  const char*  
  CreativeAdmin::campaign_id (unsigned int i)  
  {  
    if (empty() || values_[0].size() != FIELDS_COUNT) return 0;  
    return values_[i][Expected::CAMPAIGN_ID].c_str();  
  }  
  inline  
  CreativeAdmin::Expected&  
  CreativeAdmin::Expected::campaign_id(unsigned long val)  
  {  
     values_.insert(std::make_pair(CAMPAIGN_ID, ComparableRegExp(strof(val))));  
     return *this;  
  }  
  inline  
  CreativeAdmin::Expected&  
  CreativeAdmin::Expected::creative_format(const std::string& val)  
  {  
     values_.insert(std::make_pair(CREATIVE_FORMAT, ComparableRegExp(val)));  
     return *this;  
  }  
  inline  
  const char*  
  CreativeAdmin::creative_format (unsigned int i)  
  {  
    if (empty() || values_[0].size() != FIELDS_COUNT) return 0;  
    return values_[i][Expected::CREATIVE_FORMAT].c_str();  
  }  
  inline  
  CreativeAdmin::Expected&  
  CreativeAdmin::Expected::sizes(const std::string& val)  
  {  
     values_.insert(std::make_pair(SIZES, ComparableRegExp(val)));  
     return *this;  
  }  
  inline  
  const char*  
  CreativeAdmin::sizes (unsigned int i)  
  {  
    if (empty() || values_[0].size() != FIELDS_COUNT) return 0;  
    return values_[i][Expected::SIZES].c_str();  
  }  
  inline  
  CreativeAdmin::Expected&  
  CreativeAdmin::Expected::categories(const std::string& val)  
  {  
     values_.insert(std::make_pair(CATEGORIES, ComparableRegExp(val)));  
     return *this;  
  }  
  inline  
  const char*  
  CreativeAdmin::categories (unsigned int i)  
  {  
    if (empty() || values_[0].size() != FIELDS_COUNT) return 0;  
    return values_[i][Expected::CATEGORIES].c_str();  
  }  
  inline  
  CreativeAdmin::Expected&  
  CreativeAdmin::Expected::weight(const std::string& val)  
  {  
     values_.insert(std::make_pair(WEIGHT, ComparableRegExp(val)));  
     return *this;  
  }  
  inline  
  const char*  
  CreativeAdmin::weight (unsigned int i)  
  {  
    if (empty() || values_[0].size() != FIELDS_COUNT) return 0;  
    return values_[i][Expected::WEIGHT].c_str();  
  }  
  inline  
  CreativeAdmin::Expected&  
  CreativeAdmin::Expected::status(const std::string& val)  
  {  
     values_.insert(std::make_pair(STATUS, ComparableRegExp(val)));  
     return *this;  
  }  
  inline  
  bool  
  CreativeAdmin::Expected::has_status() const  
  {  
    FieldIndexMap::const_iterator it = values_.find(STATUS);  
    return it != values_.end();  
  }  
  inline  
  std::string  
  CreativeAdmin::Expected::status() const  
  {  
    FieldIndexMap::const_iterator it = values_.find(STATUS);  
    return it->second->str();  
  }  
  inline  
  const char*  
  CreativeAdmin::status (unsigned int i)  
  {  
    if (empty() || values_[0].size() != FIELDS_COUNT) return 0;  
    return values_[i][Expected::STATUS].c_str();  
  }  
}
#endif  // __AUTOTESTS_COMMONS_ADMINS_CREATIVEADMIN_HPP

