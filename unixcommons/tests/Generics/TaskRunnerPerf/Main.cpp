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
#include <unistd.h>

#include <iostream>
#include <fstream>
#include <vector>
#include <memory>
#include <thread>

#include <Sync/PosixLock.hpp>
#include <Sync/Condition.hpp>
#include <Generics/TaskRunner.hpp>
#include <Generics/TaskPool.hpp>

#include <TestCommons/ActiveObjectCallback.hpp>

struct State
{
  State()
    : tasks(0)
  {}

  void inc()
  {
    Sync::PosixGuard guard(lock);
    ++tasks;
  }

  void dec()
  {
    Sync::PosixGuard guard(lock);
    if(--tasks == 0)
    {
      cond.signal();
    }
  }

  void wait()
  {
    Sync::ConditionalGuard guard(cond, lock);
    while(tasks != 0)
    {
      guard.wait();
    }
  }

  Sync::PosixMutex lock;
  int tasks;
  Sync::Conditional cond;
};

class TaskImpl :
  public Generics::Task,
  public ReferenceCounting::AtomicImpl
{
public:
  TaskImpl(State* state)
    throw ();

  virtual void
  execute() throw ();

private:
  Generics::TaskExecutor_var task_runner_;
  State* state_;
};

TaskImpl::TaskImpl(State* state) throw ()
  : state_(state)
{
  state_->inc();
}

void
TaskImpl::execute() throw ()
{
  state_->dec();
}

void
provider_task(Generics::TaskExecutor* task_runner, State* state)
{
  for(int i = 0; i < 300000; ++i)
  {
    task_runner->enqueue_task(Generics::Task_var(new TaskImpl(state)));
  }
}

int
main()
{
  State state;

  try
  {
    Generics::ActiveObjectCallback_var task_runner_callback(
      new TestCommons::ActiveObjectCallbackStreamImpl(
        std::cerr, "TaskRunnerQueue"));

    /*
    Generics::TaskRunner_var task_runner(
      new Generics::TaskRunner(
        task_runner_callback, 6));
    */
    Generics::TaskExecutor_var task_runner(
      new Generics::TaskPool(
        task_runner_callback, 20));

    task_runner->activate_object();

    std::vector<std::unique_ptr<std::thread> > threads;
    for(int i = 0; i < 20; ++i)
    {
      threads.emplace_back(new std::thread(provider_task, task_runner.in(), &state));
    }

    for(auto th_it = threads.begin(); th_it != threads.end(); ++th_it)
    {
      (*th_it)->join();
    }

    state.wait();

    std::cout << "finished" << std::endl;

    task_runner->deactivate_object();
    task_runner->wait_object();

    std::cout << "deactivated" << std::endl;

    sleep(1000);

    return 0;
  }
  catch (const eh::Exception& ex)
  {
    std::cerr << ex.what() << std::endl;
  }

  return -1;
}
