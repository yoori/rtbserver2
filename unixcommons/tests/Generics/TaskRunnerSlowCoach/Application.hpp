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
// Application.hpp
#ifndef _TEST_APPLICATION_TASK_RUNNER_HPP_INCLUDED_
#define _TEST_APPLICATION_TASK_RUNNER_HPP_INCLUDED_ 

#include <Generics/TaskRunner.hpp>
#include <TestCommons/ActiveObjectCallback.hpp>

class TestTasker
{
public:
  TestTasker() /*throw (eh::Exception)*/;

  virtual
  ~TestTasker() throw ();

  void
  do_test() /*throw (eh::Exception)*/;

private:
  void
  spawn_tasker_(std::size_t threads_number, std::size_t queue_size = 0)
    /*throw (eh::Exception)*/;

  Generics::ActiveObjectCallback_var task_runner_callback_;
  Generics::TaskRunner_var task_runner_;
};

//////////////////////////////////////////////////////////////////////////
// Implementations

TestTasker::TestTasker() /*throw (eh::Exception)*/
  : task_runner_callback_(
      new TestCommons::ActiveObjectCallbackStreamImpl(
            std::cerr, "TaskRunnerSlowCoach"))
{
}

TestTasker::~TestTasker() throw ()
{
  if (task_runner_.in())
  {
    task_runner_->deactivate_object();
    task_runner_->wait_object();
  }
}

void
TestTasker::spawn_tasker_(std::size_t threads_number,
                          std::size_t queue_size)
  /*throw (eh::Exception)*/
{
  if (task_runner_.in())
  {
    task_runner_->deactivate_object();
    task_runner_->wait_object();
  }
  task_runner_ =
    new Generics::TaskRunner(task_runner_callback_,
      threads_number, 0, queue_size);
  task_runner_->activate_object();
}

#endif  // _TEST_APPLICATION_TASK_RUNNER_HPP_INCLUDED_
