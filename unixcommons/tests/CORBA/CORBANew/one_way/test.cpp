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

#ifdef ORB_TAO
#define ADVANCED
#endif

pid_t pid;

static void
run()
{
  switch (pid = fork())
  {
  case -1:
    exit(-1);

  case 0:
    std::cerr << "Exec\n";
    execl("./test_server", "./test_server", NULL);
    exit(-1);

  default:
    sleep(1);
    break;
  }
}

#ifdef ADVANCED
void*
orbrun(void* orb)
{
  static_cast<CORBA::ORB_ptr>(orb)->run();
  return NULL;
}
#endif

static void
one_way(Echo_ptr echo)
{
  try
  {
    echo->one_way();
    sleep(1);
  }
  catch (...)
  {
    std::cerr << "Exception\n";
  }
}

int
main()
{
  //TAO_debug_level = 100;

  run();

  char* argv[] = { "",
#ifdef TAO
    "-ORBSkipServiceConfigOpen",
#endif
#ifdef ADVANCED
#if 0
    "-ORBGestalt",
    "Local",
#endif
#if 0
    "-ORBSvcConfDirective",
    "dynamic FT_ClientService_Activate "
      "Service_Object * "
      "TAO_FT_ClientORB:_make_TAO_FT_ClientService_Activate() \"\"",
#endif
#if 0
    "-ORBSvcConfDirective",
    "remove FT_ClientService_Activate",
#endif
#endif
    NULL };
  int argc = sizeof(argv) / sizeof(*argv) - 1;

  CORBA::ORB_var orb = CORBA::ORB_init(argc, argv);

#ifdef ORB_MICO
  const char LOC[] = "corbaloc::localhost:1025/Default/CustomPoa/Echo";
#else
  const char LOC[] = "corbaloc::localhost:1025/Echo";
#endif

#ifdef ADVANCED
  pthread_t id;
  pthread_create(&id, NULL, orbrun, orb.in());
#endif

  CORBA::Object_var obj = orb->string_to_object(LOC);
  Echo_var echoref = Echo::_narrow(obj);
  if (CORBA::is_nil(echoref))
  {
    std::cerr << "Can't narrow reference to type Echo (or it was nil)." << std::endl;
    return 1;
  }

  one_way(echoref);

  kill(pid, SIGKILL);
  sleep(1);

  one_way(echoref);

  run();

#if 0
  echoref->two_way();
#endif

  std::cerr << "Sending\n";
  one_way(echoref);
  std::cerr << "Sent\n";

  orb->destroy();

  kill(pid, SIGINT);

  return 0;
}
