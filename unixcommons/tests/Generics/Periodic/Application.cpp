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
#include <Generics/Periodic.hpp>

#include <Logger/StreamLogger.hpp>

Logging::QLogger_var out;

class PeriodicPrint : public Generics::PeriodicTask
{
public:
  PeriodicPrint(int time) throw ();

  virtual
  void
  task(bool forced) throw ();

protected:
  virtual
  ~PeriodicPrint() throw ();

private:
  int index_;
};


PeriodicPrint::PeriodicPrint(int time) throw ()
  : Generics::PeriodicTask(Generics::Time(time)), index_(time)
{
}

void
PeriodicPrint::task(bool forced) throw ()
{
  out->stream(Logging::Logger::INFO) << index_ << (forced ? " forced" : "");
}

PeriodicPrint::~PeriodicPrint() throw ()
{
}

void
test1() /*throw (eh::Exception)*/
{
  const int N = 4;
  Generics::PeriodicTask_var tasks[N];
  Generics::PeriodicRunner_var pr(
    new Generics::PeriodicRunner(0));
  for (int i = 0; i < N; i++)
  {
    pr->add_task(tasks[i] = new PeriodicPrint(i + 1), true);
  }

  out->stream(Logging::Logger::INFO) << "forward";

  pr->activate_object();

  sleep(10);

  out->stream(Logging::Logger::INFO) << "backward";
  for (int i = 0; i < N; i++)
  {
    tasks[i]->set_period(Generics::Time(N - i));
  }
  sleep(10);

  out->stream(Logging::Logger::INFO) << "force all";
  for (int i = 0; i < 3; i++)
  {
    pr->enforce_start_all();
    sleep(1);
  }

  out->stream(Logging::Logger::INFO) << "force 0";
  for (int i = 0; i < 5; i++)
  {
    tasks[0]->enforce_start();
  }
  sleep(1);

  pr->deactivate_object();
  pr->wait_object();

}

int
main()
{
  std::cout << "Periodic tests started.." << std::endl;
  try
  {
    out = new Logging::OStream::Logger(Logging::OStream::Config(std::cout));
    test1();
    std::cout << "SUCCESS" << std::endl;
  }
  catch (const eh::Exception& ex)
  {
    std::cerr << "FAIL: " << ex.what() << std::endl;
  }
  catch (...)
  {
    std::cerr << "FAIL: unknown exception raised" << std::endl;
  }

  return 0;
}
