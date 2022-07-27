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
#include <signal.h>
#include "echo.hpp"
#include "message.hpp"

void
hello(CORBA::Object_ptr obj)
{
  Echo_var e = Echo::_narrow(obj);

  if (CORBA::is_nil(e))
  {
    std::cerr << "cannot invoke on a nil object reference." << std::endl;
    return;
  }

  CORBA::String_var src = (const char*) "Hello!";

  MessageHolder_var message(new MessageHolder_i(src));
  MessageHolder_var dest = e->echoString(message.in());

  std::cerr << "I said, \"" << src << "\"." <<
    " The Object said, \"" << dest->message() <<"\"" << std::endl;
}

int
main(int argc, char** argv)
{
  CORBA::ORB_var orb = CORBA::ORB_init(argc, argv);

  if (argc != 2)
  {
    return 1;
  }

  orb->register_value_factory("IDL:MessageHolder:1.0",
    new MessageHolderFactory);

  for (int i = 0; i < 1000; i++)
  {
    CORBA::Object_var obj = orb->string_to_object(argv[1]);
    Echo_var echoref = Echo::_narrow(obj);
    if (CORBA::is_nil(echoref))
    {
      std::cerr << "Can't narrow reference to type Echo (or it was nil)." << std::endl;
      return 1;
    }

    hello(echoref);
  }

  {
    CORBA::Object_var obj = orb->string_to_object(argv[1]);
    Echo_var echoref = Echo::_narrow(obj);
    echoref->shutdown();
  }

  orb->destroy();

  return 0;
}
