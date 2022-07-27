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

#include "PublisherInventory.hpp"

namespace AutoTest
{
  namespace ORM  
  {  
    ///////////////////////////////// PublisherInventory    
    template<>    
    BasicStats<PublisherInventory, 3>::names_type const    
    BasicStats<PublisherInventory, 3>::field_names = {    
      ".imps",      
      ".requests",      
      ".revenue"      
    };    
    void    
    PublisherInventory::print_idname (std::ostream& out) const    
    {    
      const char* sep = " ";      
      static const char* fsep = ", ";      
      out << description_ << " <";      
      if (key_.pub_sdate_used())      
      {      
        out << sep; 
        out << "pub_sdate = '";
        if (key_.pub_sdate_is_null())
          out << "null";
        else
          out <<  key_.pub_sdate().get_gm_time().format("%Y-%m-%d") << '\'';        
        sep = fsep;        
      }      
      if (key_.tag_id_used())      
      {      
        out << sep; 
        out << "tag_id = ";
        if (key_.tag_id_is_null())
          out << "null";
        else
          out << key_.tag_id();        
        sep = fsep;        
      }      
      if (key_.cpm_used())      
      {      
        out << sep; 
        out << "cpm = ";
        if (key_.cpm_is_null())
          out << "null";
        else
          out << key_.cpm();        
        sep = fsep;        
      }      
      out << " >" << std::endl;      
    }    
    bool    
    PublisherInventory::query_select_(StatsDB::IConn& connection)    
    {    
      std::string key_PublisherInventory;      
      {      
        std::ostringstream kstr;        
        int ckey = 1;        
        const char* sep = "";        
        static const char* fsep = " and ";        
        if (key_.pub_sdate_used())        
        {        
          if (key_.pub_sdate_is_null())          
          {          
            kstr << sep << "pub_sdate is null";            
            sep = fsep;            
          }          
          else if (key_.pub_sdate() == Generics::Time::ZERO)          
          {          
            kstr << sep << "pub_sdate = '-infinity'";            
            sep = fsep;            
          }          
          else          
          {          
            kstr << sep << "pub_sdate = :"<< ckey++;            
            sep = fsep;            
          }          
        }        
        if (key_.tag_id_used())        
        {        
          if (key_.tag_id_is_null())          
          {          
            kstr << sep << "tag_id is null";            
            sep = fsep;            
          }          
          else          
          {          
            kstr << sep << "tag_id = :" << ckey++;            
            sep = fsep;            
          }          
        }        
        if (key_.cpm_used())        
        {        
          if (key_.cpm_is_null())          
          {          
            kstr << sep << "cpm is null";            
            sep = fsep;            
          }          
          else          
          {          
            kstr << sep << "TRUNC(cpm, 2) = TRUNC(:" << ckey++ << ", 2)";            
            sep = fsep;            
          }          
        }        
        key_PublisherInventory = kstr.str();        
      }      
      std::ostringstream qstr;      
      qstr <<      
        "SELECT "        
          "SUM(imps), "          
          "SUM(requests), "          
          "SUM(revenue) "          
        "FROM PublisherInventory "        
        "WHERE ";        
      qstr << key_PublisherInventory;      
      StatsDB::Query query(connection.get_query(qstr.str()));      
      if (key_.pub_sdate_used() && !key_.pub_sdate_is_null() &&
        key_.pub_sdate() != Generics::Time::ZERO)      
        query.set(key_.pub_sdate().get_gm_time().get_date());        
      if (key_.tag_id_used() && !key_.tag_id_is_null())      
        query.set(key_.tag_id());        
      if (key_.cpm_used() && !key_.cpm_is_null())      
        query.set(key_.cpm());        
      return ask(query);      
    }    
  }  
}
