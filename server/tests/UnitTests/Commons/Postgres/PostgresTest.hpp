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
#ifndef POSTGRES_TEST_HPP
#define POSTGRES_TEST_HPP

#include<string>
#include<eh/Exception.hpp>
#include<Generics/Time.hpp>
#include<Generics/SimpleDecimal.hpp>
#include<Generics/ActiveObject.hpp>
#include<Commons/Postgres/Declarations.hpp>
#include<Commons/Postgres/ConnectionPool.hpp>
#include<Logger/DistributorLogger.hpp>
#include<Logger/StreamLogger.hpp>

namespace AdServer
{
  namespace Commons
  {
    namespace Postgres
    {
      class Connection;
    }
  }
  namespace UnitTests
  {
    class PostgresTest:
      public Generics::ActiveObjectCallback,
      public ReferenceCounting::AtomicImpl
    {
    public:
      DECLARE_EXCEPTION(BadParams, eh::DescriptiveException);
      DECLARE_EXCEPTION(Exception, eh::DescriptiveException);

      enum TestCase
      {
        TC_ALL,
        TC_CON,
        TC_RES,
        TC_ENV,
        TC_POOL,
        TC_ASYNC,
        TC_NUMERIC,
        TC_LOB,
        TC_OBJ,
        TC_QUERY_PERFORMANCE,
        TC_ACTIVE_QUERY
      };

      PostgresTest(int argc, char* argv[])
        /*throw(BadParams)*/;

      int run() noexcept;
      int connection_test() noexcept;
      int environment_test() noexcept;
      int resultset_test(
        bool sync,
        Commons::Postgres::DATA_FORMATS format)
        noexcept;
      int pool_test() noexcept;

      int no_db_test() noexcept;

      int numeric_test() noexcept;

      int lob_test() noexcept;

      int object_test() noexcept;

      int query_perf_test() noexcept;

      int active_query_test() noexcept;

      void query_perf_cursor(
        AdServer::Commons::Postgres::Connection* con)
        noexcept;

      void query_perf_one_row(
        AdServer::Commons::Postgres::Connection* con)
        noexcept;

      void query_perf_all_row(
        AdServer::Commons::Postgres::Connection* con)
        noexcept;

      virtual
      void
      report_error(
        Severity severity,
        const String::SubString& description,
        const char* error_code = 0) noexcept;

      void deactivate_env(
        Commons::Postgres::Environment* pool) noexcept;

      ~PostgresTest() noexcept {};
    private:
      enum
      {
        LEVEL_ERROR = ::Logging::Logger::ERROR,
        LEVEL_LOW = ::Logging::Logger::INFO,
        LEVEL_MIDDLE = ::Logging::Logger::DEBUG,
        LEVEL_HIGH  = ::Logging::Logger::TRACE
      };

      void log_(const char* message, unsigned int level = LEVEL_LOW) noexcept;

      typedef Generics::SimpleDecimal<uint64_t, 8, 2> TestDecimal;
      typedef Generics::SimpleDecimal<uint64_t, 18, 8> TestDecimal2;
      typedef Generics::ArrayAutoPtr<char> CharArray;

      struct Record
      {
        std::string string_value;
        unsigned long int_value;
        TestDecimal num_value;
        Generics::Time date_value;
        Generics::Time time_value;
        Generics::Time timestamp_value;
        char char_value;
        TestDecimal2 defnum_value;
      };

      std::string generate_file_name_() noexcept;

      std::string write_uid_file_(char* buf, unsigned size) /*throw(Exception)*/;

      CharArray read_file_(const std::string& file_name, unsigned size)
        /*throw(Exception)*/;

      void compary_content_(
        const char* array1, const char* array2, unsigned array_size)
        /*throw(Exception)*/;

      void generate_record_(Record& rec) noexcept;

      CharArray generate_uid_data_(size_t count, unsigned& size) noexcept;

      int connection_actions_(
        AdServer::Commons::Postgres::Connection* con,
        int error = 1)
        noexcept;

      int drop_table_(
        AdServer::Commons::Postgres::Connection* con,
        int error = 1,
        const String::SubString& table = String::SubString("pg_temp.PostgressTestTable"))
        noexcept;

      void init_objs_(Commons::Postgres::ObjectVector& objs)
        /*throw(eh::Exception)*/;

      template<typename T>
      unsigned long check_value_(
        const char* context,
        const T& value,
        const T& expected) noexcept;

    private:
      typedef ReferenceCounting::SmartPtr<Logging::OStream::Logger> Logger_var;

      unsigned long verbose_;
      TestCase test_case_;
      std::string database_;
      Logging::Logger_var file_logger_;
    };

    template<typename T>
    unsigned long PostgresTest::check_value_(
      const char* context,
      const T& value,
      const T& expected)
      noexcept
    {
      if(verbose_ >= 3)
      {
        Stream::Error trace;
        trace << "Compary " << value << " and " << expected;
        log_(trace.str().str().c_str(), 3);
      }
      if(value != expected)
      {
        Stream::Error err;
        err << context << " value != expected : '"
          << value << "' != '"
          << expected << '\'';
        log_(err.str().str().c_str(), 0);
        return 1;
      }
      return 0;
    }

  }
}
#endif //POSTGRES_TEST_HPP

