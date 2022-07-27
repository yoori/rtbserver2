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
#include <iostream>

#include <eh/Exception.hpp>
#include <Stream/MemoryStream.hpp>
#include <Generics/Time.hpp>
#include <CORBACommons/Stats.hpp>


namespace
{
  const char USAGE[] = "Usage: StatsTool <url>";

  DECLARE_EXCEPTION(Exception, eh::DescriptiveException);
  DECLARE_EXCEPTION(InvalidArgument, Exception);
}

template <typename T>
void
print(const CORBA::Any& any) /*throw (CORBA::Exception, eh::Exception)*/
{
  T value;
  any >>= value;
  std::cout << value;
}

int
main(int argc, char* argv[])
{
  try
  {
    try
    {
      CORBA::ORB_var orb = CORBA::ORB_init(argc, argv);

      if (CORBA::is_nil(orb))
      {
        throw InvalidArgument("CORBA::ORB_init failed");
      }

      if (argc != 2)
      {
        throw InvalidArgument("Invalid number of arguments");
      }

      CORBA::Object_var obj = orb->string_to_object(argv[1]);

      if (CORBA::is_nil(obj))
      {
        Stream::Error ostr;
        ostr << "string_to_object failed for '" << argv[1] << "'";
        throw Exception(ostr);
      }

      CORBACommons::ProcessStatsControl_var stats_control;
      try
      {
        stats_control = CORBACommons::ProcessStatsControl::_narrow(obj);
      }
      catch (...)
      {
      }

      if (CORBA::is_nil(stats_control))
      {
        Stream::Error ostr;
        ostr << "CORBACommons::ProcessStatsControl::_narrow failed for '" <<
          argv[1] << "'";
        throw Exception(ostr);
      }

      CORBACommons::StatsValueSeq_var stats;
      try
      {
        stats = stats_control->get_stats();
      }
      catch (const
        CORBACommons::ProcessStatsControl::ImplementationException&)
      {
        throw Exception("Received "
          "CORBACommons::ProcessStatsControl::ImplementationException");
      }

      std::cout << "Total: " << stats->length() << " stats(s)" << std::endl;
      for (size_t i = 0; i < stats->length(); i++)
      {
        const CORBA::Any& value = stats[i].value;
        CORBA::TypeCode_var type_code = value.type();

        std::cout << stats[i].key << "=";

        switch (type_code->kind())
        {
        case CORBA::tk_longlong:
          print<CORBA::LongLong>(value);
          break;
        case CORBA::tk_ulonglong:
          print<CORBA::ULongLong>(value);
          break;
        case CORBA::tk_long:
          print<CORBA::Long>(value);
          break;
        case CORBA::tk_ulong:
          print<CORBA::ULong>(value);
          break;
        case CORBA::tk_double:
          print<CORBA::Double>(value);
          break;
        case CORBA::tk_string:
          print<const CORBA::Char*>(value);
          break;
        default:
          std::cout << "UNKNOWN TYPE: " << type_code->kind();
          break;
        }

        std::cout << std::endl;
      }

      orb->destroy();

      return 0;
    }
    catch (...)
    {
      std::cerr << "StatsTool: ";
      throw;
    }
  }
  catch (const InvalidArgument& ex)
  {
    std::cerr << ex.what() << std::endl << USAGE << std::endl;
  }
  catch (const eh::Exception& ex)
  {
    std::cerr << ex.what() << std::endl;
  }
  catch (const CORBA::Exception& ex)
  {
    std::cerr << ex << std::endl;
  }
  catch (...)
  {
    std::cerr << "unknown exception" << std::endl;
  }

  return -1;
}
