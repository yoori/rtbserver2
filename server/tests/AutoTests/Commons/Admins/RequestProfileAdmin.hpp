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

#ifndef __AUTOTESTS_COMMONS_ADMINS_REQUESTPROFILEADMIN_HPP
#define __AUTOTESTS_COMMONS_ADMINS_REQUESTPROFILEADMIN_HPP

#include "Admins.hpp"

namespace AutoTest
{
  class RequestProfileAdmin:  
    public BaseAdminCmd<RequestProfileAdmin, 1>  
  {  
    public:    
      class Expected      
      {      
        friend class RequestProfileAdmin;        
        public:        
          Expected() {}          
          Expected& fraud (const std::string& val);          
                
          enum FieldName          
          {          
            FRAUD = 0            
          };          
        protected:        
          FieldIndexMap values_;          
      };      
        
    public:    
      typedef BaseAdminCmd<RequestProfileAdmin, FIELDS_COUNT> Base;    
        
      void make_cmd (const char* address,      
        const char* requestid,      
        RequestInfoSrv service      
      )      
      {      
        address_ = address;        
        AdminParams params;        
        {        
          params.push_back(AdminParamPair("", requestid ? requestid : ""));          
        }        
        make_admin_cmd(*this, "print-request", address, params, static_cast<size_t>(service));      
        add_cmd_i("--align");      
      }      
      RequestProfileAdmin(      
        const char* address,      
        const char* requestid,      
        RequestInfoSrv service = RequestInfoManager      
      )      
      {      
        make_cmd(address, requestid, service);      
      }      
      RequestProfileAdmin(      
        const std::string& address,      
        const char* requestid,      
        RequestInfoSrv service = RequestInfoManager      
      )      
      {      
        make_cmd(address.c_str(), requestid, service);      
      }      
      RequestProfileAdmin(      
        const char* address,      
        const std::string& requestid,      
        RequestInfoSrv service = RequestInfoManager      
      )      
      {      
        make_cmd(address, requestid.c_str(), service);      
      }      
      RequestProfileAdmin(      
        const std::string& address,      
        const std::string& requestid,      
        RequestInfoSrv service = RequestInfoManager      
      )      
      {      
        make_cmd(address.c_str(), requestid.c_str(), service);      
      }      
      const char* fraud (unsigned int i = 0);      
      bool check(const Expected& expected, bool exist = true)      
        /*throw(eh::Exception)*/;      
      bool check(const std::string& expected, bool exist = true)      
        /*throw(eh::Exception)*/;      
  };  
    
}
namespace AutoTest
{
  inline  
  RequestProfileAdmin::Expected&  
  RequestProfileAdmin::Expected::fraud(const std::string& val)  
  {  
     values_.insert(std::make_pair(FRAUD, ComparableRegExp(val)));  
     return *this;  
  }  
  inline  
  const char*  
  RequestProfileAdmin::fraud (unsigned int i)  
  {  
    if (empty() || values_[0].size() != FIELDS_COUNT) return 0;  
    return values_[i][Expected::FRAUD].c_str();  
  }  
}
#endif  // __AUTOTESTS_COMMONS_ADMINS_REQUESTPROFILEADMIN_HPP

