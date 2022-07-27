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
/**
 * @file PassbackContainerMTTest.hpp
 */

#ifndef PASSBACK_CONTAINER_TEST_HPP_INCLUDED
#define PASSBACK_CONTAINER_TEST_HPP_INCLUDED

#include <Sync/PosixLock.hpp>
#include <RequestInfoSvcs/RequestInfoManager/PassbackContainer.hpp>

class TestPassbackProcessorImpl :
  public AdServer::RequestInfoSvcs::PassbackProcessor,
  public virtual ReferenceCounting::AtomicImpl
{
public:
  typedef std::list<PassbackInfo> PassbackInfoList;

public:
  virtual void
  process_passback(
    const AdServer::RequestInfoSvcs::PassbackProcessor::PassbackInfo& pi)
    /*throw (AdServer::RequestInfoSvcs::PassbackProcessor::Exception)*/
  {
    Sync::PosixGuard lock(map_lock_);
    result_.push_back(pi);
  }

  const PassbackInfoList& result() const
  {
    return result_;
  }

  void clear() noexcept
  {
    result_.clear();
  }

protected:
  virtual ~TestPassbackProcessorImpl() noexcept
  {}

private:
  Sync::PosixMutex map_lock_;
  PassbackInfoList result_;
};

typedef
  ReferenceCounting::SmartPtr<TestPassbackProcessorImpl>
  TestPassbackProcessorImpl_var;

struct TestIt
{
  AdServer::RequestInfoSvcs::PassbackContainer* passback_container;
  TestPassbackProcessorImpl* passback_processor;
};

/**
 * Multithreading test
 */
bool
multi_thread_test(const TestIt* test_it) noexcept;

#endif // PASSBACK_CONTAINER_TEST_HPP_INCLUDED
