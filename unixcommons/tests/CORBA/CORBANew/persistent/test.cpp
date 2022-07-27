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
#include "echo.hpp"

class Echo_i : public POA_Echo
{
public:
  virtual char*
  echoString(const char* message) throw ();
};

char*
Echo_i::echoString(const char* message) throw ()
{
  return CORBA::string_dup(message);
}

int
main()
{
#ifdef ORB_OMNI
  char ENDPOINT[] = "-ORBendPoint";
  char ADDR[] = "giop:tcp:localhost:1025";
#endif
#ifdef ORB_MICO
  char ENDPOINT[] = "-ORBIIOPAddr";
  char ADDR[] = "inet:localhost:1025";
#endif
#ifdef ORB_TAO
  char ENDPOINT[] = "-ORBEndpoint";
  char ADDR[] = "iiop://localhost:1025";
#endif
  char* argv[] = { "", ENDPOINT, ADDR, NULL };
  int argc = sizeof(argv) / sizeof(*argv) - 1;
  CORBA::ORB_var orb = CORBA::ORB_init(argc, argv, ORB_NAME);

#ifdef ORB_OMNI
  CORBA::Object_var obj = orb->resolve_initial_references("omniINSPOA");
#else
  CORBA::Object_var obj = orb->resolve_initial_references("RootPOA");
#endif
  PortableServer::POA_var root_poa = PortableServer::POA::_narrow(obj);
  PortableServer::POAManager_var pman = root_poa->the_POAManager();
  pman->activate();

  Echo_i* myecho = new Echo_i();
#ifdef ORB_TAO
  root_poa->activate_object(myecho);

  CORBA::String_var ior_string = orb->object_to_string(myecho->_this());

  CORBA::Object_var tobj = orb->resolve_initial_references("IORTable");
  IORTable::Table_var table = IORTable::Table::_narrow(tobj.in());

  table->bind("Echo", ior_string.in());
#else
#ifdef ORB_OMNI
  PortableServer::POA_var poa = root_poa;
#else
  CORBA::PolicyList pl;
  pl.length(2);
  pl[0] = root_poa->create_lifespan_policy(PortableServer::PERSISTENT);
  pl[1] = root_poa->create_id_assignment_policy(PortableServer::USER_ID);

  PortableServer::POA_var poa = root_poa->create_POA("CustomPoa", pman, pl);
#endif

  PortableServer::ObjectId_var oid =
    PortableServer::string_to_ObjectId("Echo");

  poa->activate_object_with_id(oid, myecho);
#endif

  //puts(orb->object_to_string(poa->id_to_reference(oid.in())));

  if (!fork())
  {
#ifdef ORB_MICO
    const char LOC[] = "corbaloc::localhost:1025/Default/CustomPoa/Echo";
#else
    const char LOC[] = "corbaloc::localhost:1025/Echo";
#endif
    execl("./test_client", "./test_client", LOC, NULL);
  }
  myecho->_remove_ref();

  orb->run();

  return 0;
}
