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
#include<libpq-fe.h>
#include<Stream/MemoryStream.hpp>
#include<Commons/Postgres/SqlStream.hpp>
#include"Statement.hpp"

namespace AdServer
{
namespace Commons
{
  namespace Postgres
  {
    Statement::Statement(const char* query, const char* name) noexcept
      : query_(query)
    {
      if(name)
      {
        name_ = name;
      }
      else
      {
        name_ = query;
      }
    }

    void Statement::prepare_query(PGconn* conn, int count_params)
      /*throw(SqlException)*/
    {
      PGresult* res = PQprepare(
        conn,
        name_.c_str(),
        query_.c_str(),
        count_params,
        NULL);
      ExecStatusType status = PQresultStatus(res);
      PQclear(res);
      if(status != PGRES_COMMAND_OK)
      {
        Stream::Error err;
        err << "Preparing statement '" << name_
          << "' failed: " << PQresultErrorMessage(res);
        throw SqlException(err);
      }
    }

    void Statement::set_date(unsigned int param_num, const Generics::Time& date)
      /*throw (eh::Exception)*/
    {
      add_param_(date.get_gm_time().format("%Y-%m-%d"), param_num - 1);
    }

    void Statement::set_time(
      unsigned int param_num,
      const Generics::Time& time)
      /*throw (eh::Exception)*/
    {
      add_param_(time.get_gm_time().format("%H:%M:%S.%q"), param_num - 1);
    }

    void Statement::set_timestamp(
      unsigned int param_num,
      const Generics::Time& timestamp)
      /*throw (eh::Exception)*/
    {
      Generics::ExtendedTime ex_timestamp = timestamp.get_gm_time();
      std::string timestamp_str = ex_timestamp.format("%Y-%m-%d %H:%M:%S.%q");
      add_param_(timestamp_str, param_num - 1);
    }

    void Statement::set_array(
      unsigned int param_num,
      const ObjectVector& objs)
      /*throw (Exception)*/
    {
      std::ostringstream ostr;
      ostr << "{";
      for (auto it = objs.begin(); it != objs.end(); it++)
      {
        if (it != objs.begin())
        {
          ostr << ',';
        }
        SqlStream_var stream = new SqlStream();
        (*it)->writeSQL(*stream);
        ostr << "\"(" << stream->str() << ")\"";
      }
      ostr << "}";
      add_param_(ostr.str(), param_num - 1);
    }

  }
}
}

