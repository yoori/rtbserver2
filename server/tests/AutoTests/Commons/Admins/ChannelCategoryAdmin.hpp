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

#ifndef __AUTOTESTS_COMMONS_ADMINS_CHANNELCATEGORYADMIN_HPP
#define __AUTOTESTS_COMMONS_ADMINS_CHANNELCATEGORYADMIN_HPP

#include "Admins.hpp"

namespace AutoTest
{
  class ChannelCategoryAdmin:  
    public BaseAdminCmd<ChannelCategoryAdmin, 3>  
  {  
    public:    
      class Expected      
      {      
        friend class ChannelCategoryAdmin;        
        public:        
          Expected() {}          
          Expected& channel_id (const std::string& val);          
          Expected& channel_id(unsigned long val);          
          Expected& parent_channel_id (const std::string& val);          
          Expected& parent_channel_id(unsigned long val);          
          Expected& timestamp (const std::string& val);          
                
          enum FieldName          
          {          
            CHANNEL_ID = 0,            
            PARENT_CHANNEL_ID,            
            TIMESTAMP            
          };          
        protected:        
          FieldIndexMap values_;          
      };      
        
    public:    
      typedef BaseAdminCmd<ChannelCategoryAdmin, FIELDS_COUNT> Base;    
        
      void make_cmd (const char* address,      
        const char* category      
      )      
      {      
        address_ = address;        
        AdminParams params;        
        if (category)        
        {        
          params.push_back(AdminParamPair("channel_id=", category));          
        }        
        make_admin_cmd(*this, "category_channel", address, params, static_cast<size_t>(CampaignManager));      
      }      
      ChannelCategoryAdmin(      
        const char* address,      
        const char* category      
      )      
      {      
        make_cmd(address, category);      
      }      
      ChannelCategoryAdmin(      
        const std::string& address,      
        const char* category      
      )      
      {      
        make_cmd(address.c_str(), category);      
      }      
      ChannelCategoryAdmin(      
        const char* address,      
        const std::string& category      
      )      
      {      
        make_cmd(address, category.c_str());      
      }      
      ChannelCategoryAdmin(      
        const std::string& address,      
        const std::string& category      
      )      
      {      
        make_cmd(address.c_str(), category.c_str());      
      }      
      ChannelCategoryAdmin(      
        const char* address,      
        unsigned long category      
      )      
      {      
        make_cmd(address, strof(category).c_str());      
      }      
      ChannelCategoryAdmin(      
        const std::string& address,      
        unsigned long category      
      )      
      {      
        make_cmd(address.c_str(), strof(category).c_str());      
      }      
      const char* channel_id (unsigned int i = 0);      
      const char* parent_channel_id (unsigned int i = 0);      
      const char* timestamp (unsigned int i = 0);      
      bool check(const Expected& expected, bool exist = true)      
        /*throw(eh::Exception)*/;      
      bool check(const std::string& expected, bool exist = true)      
        /*throw(eh::Exception)*/;      
  };  
    
}
namespace AutoTest
{
  inline  
  ChannelCategoryAdmin::Expected&  
  ChannelCategoryAdmin::Expected::channel_id(const std::string& val)  
  {  
     values_.insert(std::make_pair(CHANNEL_ID, ComparableRegExp(val)));  
     return *this;  
  }  
  inline  
  const char*  
  ChannelCategoryAdmin::channel_id (unsigned int i)  
  {  
    if (empty() || values_[0].size() != FIELDS_COUNT) return 0;  
    return values_[i][Expected::CHANNEL_ID].c_str();  
  }  
  inline  
  ChannelCategoryAdmin::Expected&  
  ChannelCategoryAdmin::Expected::channel_id(unsigned long val)  
  {  
     values_.insert(std::make_pair(CHANNEL_ID, ComparableRegExp(strof(val))));  
     return *this;  
  }  
  inline  
  ChannelCategoryAdmin::Expected&  
  ChannelCategoryAdmin::Expected::parent_channel_id(const std::string& val)  
  {  
     values_.insert(std::make_pair(PARENT_CHANNEL_ID, ComparableRegExp(val)));  
     return *this;  
  }  
  inline  
  const char*  
  ChannelCategoryAdmin::parent_channel_id (unsigned int i)  
  {  
    if (empty() || values_[0].size() != FIELDS_COUNT) return 0;  
    return values_[i][Expected::PARENT_CHANNEL_ID].c_str();  
  }  
  inline  
  ChannelCategoryAdmin::Expected&  
  ChannelCategoryAdmin::Expected::parent_channel_id(unsigned long val)  
  {  
     values_.insert(std::make_pair(PARENT_CHANNEL_ID, ComparableRegExp(strof(val))));  
     return *this;  
  }  
  inline  
  ChannelCategoryAdmin::Expected&  
  ChannelCategoryAdmin::Expected::timestamp(const std::string& val)  
  {  
     values_.insert(std::make_pair(TIMESTAMP, ComparableRegExp(val)));  
     return *this;  
  }  
  inline  
  const char*  
  ChannelCategoryAdmin::timestamp (unsigned int i)  
  {  
    if (empty() || values_[0].size() != FIELDS_COUNT) return 0;  
    return values_[i][Expected::TIMESTAMP].c_str();  
  }  
}
#endif  // __AUTOTESTS_COMMONS_ADMINS_CHANNELCATEGORYADMIN_HPP

