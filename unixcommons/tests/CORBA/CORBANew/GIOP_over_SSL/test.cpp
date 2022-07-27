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
#include <vector>
#include "echo.hpp"
#ifdef ORB_OMNI
#include <omniORB4/sslContext.h>
#endif

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
main(int argc, char** argv)
{
#ifdef ORB_OMNI
  char ADDR[] = "giop:ssl:localhost:1025";
  char CERTIFICATE[] = "root.pem";
  char KEY[] = "server.pem";
  char PASSWORD[] = "password";
#endif
#ifdef ORB_MICO
  char ADDR[] = "ssl:inet:localhost:1025";
  char CERTIFICATE[] = "s_cert.pem";
  char KEY[] = "s_key.pem";
#endif
#ifdef ORB_TAO
  char ADDR[] = "ssliop://localhost:1026/ssl_port=1025";
#endif

#ifdef ORB_OMNI
  sslContext::certificate_authority_file = CERTIFICATE;
  sslContext::key_file = KEY;
  sslContext::key_file_password = PASSWORD;

  const char* options[][2] =
    {
      { "endPoint", ADDR },
      { 0, 0 }
    };
  CORBA::ORB_var orb = CORBA::ORB_init(argc, argv, ORB_NAME, options);
#else
  std::vector<char*> args;
  args.resize(argc);
  std::copy(argv, argv + argc, args.begin());
#ifdef ORB_MICO
  args.push_back("-ORBIIOPAddr");
  args.push_back(ADDR);
  args.push_back("-ORBSSLcert");
  args.push_back(CERTIFICATE);
  args.push_back("-ORBSSLkey");
  args.push_back(KEY);
#else
  args.push_back("-ORBSvcConf");
  args.push_back("server.conf");
  args.push_back("-ORBEndpoint");
  args.push_back(ADDR);
#endif
  args.push_back(0);
  int argsc = args.size() - 1;
  CORBA::ORB_var orb = CORBA::ORB_init(argsc, &args[0], ORB_NAME);
#endif

  CORBA::Object_var obj = orb->resolve_initial_references("RootPOA");
  PortableServer::POA_var poa = PortableServer::POA::_narrow(obj);

  Echo_i* myecho = new Echo_i();
  PortableServer::ObjectId_var myechoid = poa->activate_object(myecho);

  obj = myecho->_this();
  CORBA::String_var sior(orb->object_to_string(obj));
  if (!fork())
  {
    execl("./test_client", "./test_client", (const char*)sior, NULL);
  }
  myecho->_remove_ref();

  PortableServer::POAManager_var pman = poa->the_POAManager();
  pman->activate();

  orb->run();

  return 0;
}
