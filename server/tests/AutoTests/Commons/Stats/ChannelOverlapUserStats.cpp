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

#include "ChannelOverlapUserStats.hpp"

namespace AutoTest
{
  namespace ORM  
  {  
    ///////////////////////////////// ChannelOverlapUserStats    
    template<>    
    BasicStats<ChannelOverlapUserStats, 1>::names_type const    
    BasicStats<ChannelOverlapUserStats, 1>::field_names = {    
      ".users"      
    };    
    void    
    ChannelOverlapUserStats::print_idname (std::ostream& out) const    
    {    
      const char* sep = " ";      
      static const char* fsep = ", ";      
      out << description_ << " <";      
      if (key_.channel1_used())      
      {      
        out << sep; 
        out << "channel1 = ";
        if (key_.channel1_is_null())
          out << "null";
        else
          out << key_.channel1();        
        sep = fsep;        
      }      
      if (key_.channel2_used())      
      {      
        out << sep; 
        out << "channel2 = ";
        if (key_.channel2_is_null())
          out << "null";
        else
          out << key_.channel2();        
        sep = fsep;        
      }      
      if (key_.sdate_used())      
      {      
        out << sep; 
        out << "sdate = '";
        if (key_.sdate_is_null())
          out << "null";
        else
          out <<  key_.sdate().get_gm_time().format("%Y-%m-%d") << '\'';        
        sep = fsep;        
      }      
      out << " >" << std::endl;      
    }    
    bool    
    ChannelOverlapUserStats::query_select_(StatsDB::IConn& connection)    
    {    
      std::string key_ChannelOverlapUserStats;      
      {      
        std::ostringstream kstr;        
        int ckey = 1;        
        const char* sep = "";        
        static const char* fsep = " and ";        
        if (key_.channel1_used())        
        {        
          if (key_.channel1_is_null())          
          {          
            kstr << sep << "channel1_id is null";            
            sep = fsep;            
          }          
          else          
          {          
            kstr << sep << "channel1_id = :" << ckey++;            
            sep = fsep;            
          }          
        }        
        if (key_.channel2_used())        
        {        
          if (key_.channel2_is_null())          
          {          
            kstr << sep << "channel2_id is null";            
            sep = fsep;            
          }          
          else          
          {          
            kstr << sep << "channel2_id = :" << ckey++;            
            sep = fsep;            
          }          
        }        
        if (key_.sdate_used())        
        {        
          if (key_.sdate_is_null())          
          {          
            kstr << sep << "sdate is null";            
            sep = fsep;            
          }          
          else if (key_.sdate() == Generics::Time::ZERO)          
          {          
            kstr << sep << "sdate = '-infinity'";            
            sep = fsep;            
          }          
          else          
          {          
            kstr << sep << "sdate = :"<< ckey++;            
            sep = fsep;            
          }          
        }        
        key_ChannelOverlapUserStats = kstr.str();        
      }      
      std::ostringstream qstr;      
      qstr <<      
        "SELECT "        
          "SUM(unique_users) "          
        "FROM ChannelOverlapUserStats "        
        "WHERE ";        
      qstr << key_ChannelOverlapUserStats;      
      StatsDB::Query query(connection.get_query(qstr.str()));      
      if (key_.channel1_used() && !key_.channel1_is_null())      
        query.set(key_.channel1());        
      if (key_.channel2_used() && !key_.channel2_is_null())      
        query.set(key_.channel2());        
      if (key_.sdate_used() && !key_.sdate_is_null() &&
        key_.sdate() != Generics::Time::ZERO)      
        query.set(key_.sdate().get_gm_time().get_date());        
      return ask(query);      
    }    
  }  
}
