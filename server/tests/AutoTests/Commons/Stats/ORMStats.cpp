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
#include <tests/AutoTests/Commons/Common.hpp>

namespace AutoTest
{
  namespace ORM
  {

    Generics::ExtendedTime
    default_date()
    {
      Generics::ExtendedTime t = AutoTest::Time().get_gm_time();
      return t;
    }

    bool calc_ctr(StatsDB::IConn& connection)
    {
      return SerializeQueryManager::instance().
        execute(
          connection,
          connection.get_query(
            "select ctr.init(), "
            "ctr.pub_tag_adjustments(),"
            "ctr.keyword_targeted_text_groups(),"
            "ctr.keyword_targeted_text_groups_tow(),"
            "ctr.cpc_groups();"));
    }

    bool
    update_channel_display_status(
      StatsDB::IConn& conn,
      int channel_id)
    {
      bool result = true;

      StatsDB::Query query(
        conn.get_query(
          "select displaystatus.bulk_update_display_status("
          "array[('channel', :1)]::displaystatus.table_id[]);"));
      query.set(channel_id);

      {
        typedef ORMRestorer<PQ::Channel> ORMChannel;
        typedef ReferenceCounting::SmartPtr<ORMChannel> Channel_var;
        
        Channel_var channel =
          new ORMChannel(
            conn, channel_id);

        const char UNSUPPORTED_TYPES[] = "KGS";
        
        if (strstr(UNSUPPORTED_TYPES, channel->type.value().c_str()) == 0)
        {
          channel->status = "D";
          result = channel->update(false);
        }
          
        result &=
          SerializeQueryManager::instance().execute(conn, query);
      }

      return result &&
        SerializeQueryManager::instance().execute(conn, query);
    }

    bool
    update_display_status(
      BaseUnit* test,
      const char* object_name,
      int id)
    {
      AutoTest::DBC::Conn conn(test->open_pq());
      
      StatsDB::Query query(
        conn.query(
          "select displaystatus.bulk_update_display_status("
          "array[(:1, :2)]::displaystatus.table_id[]);"));
      query.set(tolower(object_name));
      query.set(id);

      return SerializeQueryManager::instance().execute(
        conn, query);  
    }
   
    Generics::Time
    get_tz_ofset(
      BaseUnit* test,
      const std::string& tzname) /*throw(eh::Exception)*/
    {
      try
      {
        int tz_ofset;
        StatsDB::Conn connection(test->open_pq());
        connection.ask(
          "select extract(epoch from now() - now() "
          "at time zone 'GMT' at time zone tzname) from timezone where tzname = :1",
          tzname,
          tz_ofset);
        return Generics::Time(tz_ofset);
      }
      catch (eh::Exception& e)
      {
        Stream::Error ostr;
        ostr << "Unknown timezone '" << tzname << "'";
        ostr << " (" << e.what() << ")";
        throw UnknownTimezone(ostr);
      }
    }

    Generics::ExtendedTime
    trunc_hourly(const Generics::ExtendedTime& date)
    {
      Generics::ExtendedTime sdate = date;
      sdate.tm_sec = 0;
      sdate.tm_min = 0;
      sdate.tm_usec = 0;
      return sdate;
    }

    // class Selectable
    Selectable::Selectable() :
      initial_(false)
    { }
    
    Selectable::~Selectable()
    { }

    bool
    Selectable::select(
      StatsDB::IConn& connection,
      bool initial)
    {
      initial_ = initial;
      return this->query_select_(connection);
    }
   
    // class OneRowObject
    
    OneRowObject::~OneRowObject ()
    {}

    bool
    OneRowObject::ask(
      StatsDB::Query& query)
    {
      return query.get_one(StatsDB::result_getter(this, &OneRowObject::get));
    }
  }//ORM
}//AutoTest
