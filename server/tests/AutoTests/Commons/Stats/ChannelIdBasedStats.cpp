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

#include "ChannelIdBasedStats.hpp"

namespace AutoTest
{
  namespace ORM  
  {  
    ///////////////////////////////// ChannelIdBasedStats    
    template<>    
    BasicStats<ChannelIdBasedStats, 22>::names_type const    
    BasicStats<ChannelIdBasedStats, 22>::field_names = {    
      ".ChannelImpInventory.imps",      
      ".ChannelImpInventory.clicks",      
      ".ChannelImpInventory.actions",      
      ".ChannelImpInventory.revenue",      
      ".ChannelImpInventory.impops_user_count",      
      ".ChannelImpInventory.imps_user_count",      
      ".ChannelImpInventory.imps_value",      
      ".ChannelImpInventory.imps_other",      
      ".ChannelImpInventory.imps_other_user_count",      
      ".ChannelImpInventory.imps_other_value",      
      ".ChannelImpInventory.impops_no_imp",      
      ".ChannelImpInventory.impops_no_imp_user_count",      
      ".ChannelImpInventory.impops_no_imp_value",      
      ".ChannelInventory.sum_ecpm",      
      ".ChannelInventory.active_user_count",      
      ".ChannelInventory.total_user_count",      
      ".ChannelInventory.hits",      
      ".ChannelInventory.hits_urls",      
      ".ChannelInventory.hits_kws",      
      ".ChannelInventory.hits_search_kws",      
      ".ChannelInventory.hits_url_kws",      
      ".ChannelInventoryByCpm.user_count"      
    };    
    void    
    ChannelIdBasedStats::print_idname (std::ostream& out) const    
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
      if (key_.exclude_colo_used())      
      {      
        out << sep; 
        out << "exclude_colo = ";
        if (key_.exclude_colo_is_null())
          out << "null";
        else
          out << key_.exclude_colo();        
        sep = fsep;        
      }      
      out << " >" << std::endl;      
    }    
    bool    
    ChannelIdBasedStats::query_select_(StatsDB::IConn& connection)    
    {    
      std::string key_ChannelIdBasedStats;      
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
        if (key_.exclude_colo_used())        
        {        
          if (key_.exclude_colo_is_null())          
          {          
            kstr << sep << "colo_id is null";            
            sep = fsep;            
          }          
          else          
          {          
            kstr << sep << "colo_id != :" << ckey++;            
            sep = fsep;            
          }          
        }        
        key_ChannelIdBasedStats = kstr.str();        
      }      
      std::ostringstream qstr;      
      qstr <<      
        "SELECT * FROM ";        
          qstr << "("          
          "SELECT "          
            "SUM(imps), "            
            "SUM(clicks), "            
            "SUM(actions), "            
            "SUM(revenue), "            
            "SUM(impops_user_count), "            
            "SUM(imps_user_count), "            
            "SUM(imps_value), "            
            "SUM(imps_other), "            
            "SUM(imps_other_user_count), "            
            "SUM(imps_other_value), "            
            "SUM(impops_no_imp), "            
            "SUM(impops_no_imp_user_count), "            
            "SUM(impops_no_imp_value) "            
          "FROM ChannelImpInventory "          
          "WHERE ";          
          qstr << key_ChannelIdBasedStats << ") AS ChannelImpInventory,";          
          qstr << "("          
          "SELECT "          
            "SUM(sum_ecpm), "            
            "SUM(active_user_count), "            
            "SUM(total_user_count), "            
            "SUM(hits), "            
            "SUM(hits_urls), "            
            "SUM(hits_kws), "            
            "SUM(hits_search_kws), "            
            "SUM(hits_url_kws) "            
          "FROM ChannelInventory "          
          "WHERE ";          
          qstr << key_ChannelIdBasedStats << ") AS ChannelInventory,";          
          qstr << "("          
          "SELECT "          
            "SUM(user_count) "            
          "FROM ChannelInventoryByCpm "          
          "WHERE ";          
          qstr << key_ChannelIdBasedStats << ") AS ChannelInventoryByCpm";          
      StatsDB::Query query(connection.get_query(qstr.str()));      
      if (key_.channel_id_used() && !key_.channel_id_is_null())      
        query.set(key_.channel_id());        
      if (key_.exclude_colo_used() && !key_.exclude_colo_is_null())      
        query.set(key_.exclude_colo());        
      if (key_.channel_id_used() && !key_.channel_id_is_null())      
        query.set(key_.channel_id());        
      if (key_.exclude_colo_used() && !key_.exclude_colo_is_null())      
        query.set(key_.exclude_colo());        
      if (key_.channel_id_used() && !key_.channel_id_is_null())      
        query.set(key_.channel_id());        
      if (key_.exclude_colo_used() && !key_.exclude_colo_is_null())      
        query.set(key_.exclude_colo());        
      return ask(query);      
    }    
  }  
}
