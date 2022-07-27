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
#include <sstream>

#include "Application.hpp"

namespace
{
  const char usage[] = "usage: AdServerTest <log_level> <test_configfile_path>";
}


int main (int argc, char** argv)
{
  if(argc != 3)
  {
    std::cerr << "error: test configuration file path not specified" << std::endl <<
      usage << std::endl;
    exit(1);
  }
  try
    {
      ACE::init ();
      Application app(atoi(argv[1]), argv[2]);
      app.init();
      app.run();
      ACE::fini ();
    }
  catch (eh::Exception& e)
    {
      std::cerr << "Exception:" << e.what() << std::endl;
      exit(1);      
    }
  catch (...)
    {
      std::cerr << "Unexpected exception" << std::endl;
      exit(1);      
    }
}
