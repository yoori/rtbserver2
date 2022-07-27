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
#ifndef AD_SERVER_LOG_PROCESSING_DB_CONNECTION_FACTORY_HPP
#define AD_SERVER_LOG_PROCESSING_DB_CONNECTION_FACTORY_HPP


#include <string>

#include <eh/Exception.hpp>

#include <Generics/ActiveObject.hpp>
#include <ReferenceCounting/AtomicImpl.hpp>

#include <Commons/Postgres/Environment.hpp>
#include <Commons/Postgres/Connection.hpp>
#include <Commons/Postgres/ConnectionPool.hpp>

namespace AdServer {
namespace LogProcessing {

class DbConnectionFactory: public ReferenceCounting::AtomicImpl
{
public:
  DECLARE_EXCEPTION(Exception, eh::DescriptiveException);
  DECLARE_EXCEPTION(NotActive, Exception);

protected:
  virtual ~DbConnectionFactory() noexcept {}
};

typedef ReferenceCounting::SmartPtr<DbConnectionFactory>
  DbConnectionFactory_var;

class PostgresConnectionFactoryImpl:
  public Generics::ActiveObject,
  public DbConnectionFactory
{
public:
  PostgresConnectionFactoryImpl(): initialized_() {}

  void
  initialize(const char* conn);

  Commons::Postgres::Connection_var get_connection();

  void activate_object() /*throw(ActiveObject::AlreadyActive)*/;

  void deactivate_object() noexcept;

  void wait_object() noexcept;

  bool active() noexcept;

private:
  virtual
  ~PostgresConnectionFactoryImpl() noexcept {}

  Commons::Postgres::Environment_var env_;
  Commons::Postgres::ConnectionPool_var conn_pool_;
  bool initialized_;
};

typedef ReferenceCounting::SmartPtr<PostgresConnectionFactoryImpl>
  PostgresConnectionFactoryImpl_var;

} // namespace LogProcessing
} // namespace AdServer

#endif /* AD_SERVER_LOG_PROCESSING_DB_CONNECTION_FACTORY_HPP */

