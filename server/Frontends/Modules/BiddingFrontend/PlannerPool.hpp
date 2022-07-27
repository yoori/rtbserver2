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
#ifndef SCHEDULER_POOL_HPP_
#define SCHEDULER_POOL_HPP_

#include <vector>

#include <Generics/Time.hpp>
#include <Generics/CompositeActiveObject.hpp>
#include <Generics/Scheduler.hpp>

namespace AdServer
{
namespace Bidding
{
  class PlannerPool:
    public Generics::CompositeActiveObject,
    public ReferenceCounting::AtomicImpl
  {
  public:
    PlannerPool(
      Generics::ActiveObjectCallback* callback,
      unsigned long threads,
      size_t stack_size = 0);

    void
    schedule(Generics::Goal* goal, const Generics::Time& time);

  protected:
    typedef std::vector<Generics::Planner_var> PlannerArray;

  protected:
    virtual
    ~PlannerPool() noexcept = default;

  protected:
    Generics::AtomicUInt planner_pos_;
    PlannerArray planners_;
  };

  typedef ReferenceCounting::SmartPtr<PlannerPool> PlannerPool_var;
}
}

#endif
