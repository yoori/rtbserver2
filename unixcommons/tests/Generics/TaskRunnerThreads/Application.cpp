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
// Application.cpp

#include <iostream>

#include <Generics/TaskRunner.hpp>

#include <Logger/StreamLogger.hpp>
#include <Logger/ActiveObjectCallback.hpp>


class TRunner : public Generics::TaskRunner
{
public:
  TRunner(Generics::ActiveObjectCallback* callback,
    unsigned threads_number, unsigned start_threads)
    /*throw (InvalidArgument, Exception, eh::Exception)*/;


  unsigned
  number_of_threads() const throw ();

protected:
  virtual
  ~TRunner() throw ();
};
typedef ReferenceCounting::QualPtr<TRunner> TRunner_var;

TRunner::TRunner(Generics::ActiveObjectCallback* callback,
  unsigned threads_number, unsigned start_threads)
  /*throw (InvalidArgument, Exception, eh::Exception)*/
  : Generics::TaskRunner(callback, threads_number, 0, 0, start_threads)
{
}

TRunner::~TRunner() throw ()
{
}

unsigned
TRunner::number_of_threads() const throw ()
{
  return thread_runner_.running();
}

class STask : public Generics::TaskImpl
{
public:
  virtual
  void
  execute() /*throw (eh::Exception)*/;

protected:
  virtual
  ~STask() throw ();
};

STask::~STask() throw ()
{
}

void
STask::execute() /*throw (eh::Exception)*/
{
  sleep(rand() % 10);
}


int
main()
{
  try
  {
    Logging::FLogger_var logger(new Logging::OStream::Logger(
      Logging::OStream::Config(std::cerr)));
    Generics::ActiveObjectCallback_var callback(
      new Logging::ActiveObjectCallbackImpl(logger));

    Generics::Task_var task(new STask);

    TRunner_var tr(new TRunner(callback, 30, 1));
    for (unsigned j = 4; j > 0; j--)
    {
      tr->enqueue_task(task);
    }
    tr->activate_object();
    for (unsigned i = 0; i < 30; i++)
    {
      sleep(1);
      std::cout << tr->number_of_threads() << " " <<
        tr->task_count() << std::endl;
      for (unsigned j = rand() % 5; j > 0; j--)
      {
        tr->enqueue_task(task);
      }
    }
    tr->deactivate_object();
    tr->wait_object();
  }
  catch (...)
  {
    std::cerr << "FAIL: unknown exception raised" << std::endl;
  }

  return 0;
}
