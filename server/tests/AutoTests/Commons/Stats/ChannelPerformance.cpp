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

#include "ChannelPerformance.hpp"

namespace AutoTest
{
  namespace ORM  
  {  
    ///////////////////////////////// ChannelPerformance    
    template<>    
    BasicStats<ChannelPerformance, 4>::names_type const    
    BasicStats<ChannelPerformance, 4>::field_names = {    
      ".imps",      
      ".clicks",      
      ".actions",      
      ".revenue"      
    };    
    void    
    ChannelPerformance::print_idname (std::ostream& out) const    
    {    
      const char* sep = " ";      
      static const char* fsep = ", ";      
      out << description_ << " <";      
      if (key_.channel_id_used())      
      {      
        out << sep; 
        out << "channel_id = ";
        if (key_.channel_id_is_null())
          out << "null";
        else
          out << key_.channel_id();        
        sep = fsep;        
      }      
      if (key_.last_use_used())      
      {      
        out << sep; 
        out << "last_use = '";
        if (key_.last_use_is_null())
          out << "null";
        else
          out <<  key_.last_use().get_gm_time().format("%Y-%m-%d") << '\'';        
        sep = fsep;        
      }      
      out << " >" << std::endl;      
    }    
    bool    
    ChannelPerformance::query_select_(StatsDB::IConn& connection)    
    {    
      Key stored_key(key_);      
      if (key_.last_use_used() && initial_)      
      {      
         key_.last_use_set_used(false);      
      }      
      std::string key_ChannelPerformance;      
      {      
        std::ostringstream kstr;        
        int ckey = 1;        
        const char* sep = "";        
        static const char* fsep = " and ";        
        if (key_.channel_id_used())        
        {        
          if (key_.channel_id_is_null())          
          {          
            kstr << sep << "channel_id is null";            
            sep = fsep;            
          }          
          else          
          {          
            kstr << sep << "channel_id = :" << ckey++;            
            sep = fsep;            
          }          
        }        
        if (key_.last_use_used())        
        {        
          if (key_.last_use_is_null())          
          {          
            kstr << sep << "last_use is null";            
            sep = fsep;            
          }          
          else if (key_.last_use() == Generics::Time::ZERO)          
          {          
            kstr << sep << "last_use = '-infinity'";            
            sep = fsep;            
          }          
          else          
          {          
            kstr << sep << "last_use = :"<< ckey++;            
            sep = fsep;            
          }          
        }        
        key_ChannelPerformance = kstr.str();        
      }      
      std::ostringstream qstr;      
      qstr <<      
        "SELECT "        
          "SUM(imps), "          
          "SUM(clicks), "          
          "SUM(actions), "          
          "SUM(revenue) "          
        "FROM ChannelUsageStatsTotal "        
        "WHERE ";        
      qstr << key_ChannelPerformance;      
      StatsDB::Query query(connection.get_query(qstr.str()));      
      if (key_.channel_id_used() && !key_.channel_id_is_null())      
        query.set(key_.channel_id());        
      if (key_.last_use_used() && !key_.last_use_is_null() &&
        key_.last_use() != Generics::Time::ZERO)      
        query.set(key_.last_use().get_gm_time().get_date());        
      key_ = stored_key;      
      return ask(query);      
    }    
  }  
}
