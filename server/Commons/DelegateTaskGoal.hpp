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
#ifndef COMMONS_DELEGATETASKGOAL_HPP_
#define COMMONS_DELEGATETASKGOAL_HPP_

#include <type_traits>

#include <Generics/TaskRunner.hpp>
#include <Generics/Scheduler.hpp>
#include <Generics/BoolFunctors.hpp>

namespace AdServer
{
  namespace Commons
  {
    typedef ReferenceCounting::QualPtr<Generics::TaskGoal>
      TaskGoal_var;

    typedef ReferenceCounting::QualPtr<Generics::GoalTask>
      GoalTask_var;

    template<typename Delegate>
    TaskGoal_var
    make_delegate_goal_task(
      const Delegate& delegate,
      Generics::TaskRunner* task_runner)
      /*throw(eh::Exception)*/;

    /**
     * create task that start execution loop (after first execution) with predefined period
     * if function will return false execution loop will be interrupted
     * if function return type is void exection loop uninterruptable
     */
    template<typename Delegate>
    GoalTask_var
    make_goal_task(
      const Delegate& delegate,
      Generics::TaskRunner* task_runner,
      Generics::Planner* planner,
      const Generics::Time& update_period)
      /*throw (eh::Exception)*/;

    template<typename Delegate>
    Generics::Task_var
    make_delegate_task(const Delegate& delegate)
      /*throw(eh::Exception)*/;

    /**
     * create task that will reexecuted for time returned from delegate
     * execution will be stopped if returned time is ZERO
     */    
    template<typename Delegate>
    GoalTask_var
    make_repeating_task(
      const Delegate& delegate,
      Generics::TaskRunner* task_runner,
      Generics::Planner* planner)
      /*throw (eh::Exception)*/;
  }
}

namespace AdServer
{
namespace Commons
{
  template<typename Delegate>
  class DelegateTask : public Generics::Task,
    public ReferenceCounting::AtomicImpl
  {
  public:
    DelegateTask(const Delegate& delegate)
      /*throw(eh::Exception)*/
      : delegate_(delegate)
    {}

    virtual void
    execute()
    noexcept
    {
      delegate_();
    }

  private:
    Delegate delegate_;

  protected:
    virtual
    ~DelegateTask() noexcept
    {}
  };

  template<typename Delegate>
  class DelegateTaskGoal : public Generics::TaskGoal
  {
  public:
    DelegateTaskGoal(
      const Delegate& delegate,
      Generics::TaskRunner* task_runner)
      /*throw(eh::Exception)*/
      : TaskGoal(task_runner), delegate_(delegate)
    {}

    virtual void
    execute()
    noexcept
    {
      delegate_();
    }

  private:
    Delegate delegate_;

  protected:
    virtual
    ~DelegateTaskGoal() noexcept
    {}
  };

  /**
   * tparam Delegate must be noexcept functor
   *   with return type convertable to bool
   */
  template <typename Delegate>
  class DelegateGoalTask : public Generics::GoalTask
  {
    DECLARE_EXCEPTION(Exception, eh::DescriptiveException);

  public:
    DelegateGoalTask(
      const Delegate& delegate,
      Generics::TaskRunner* task_runner,
      Generics::Planner* planner)
      /*throw (eh::Exception)*/
      : GoalTask(planner, task_runner),
        delegate_(delegate)
    {}

    virtual void
    execute() /*throw (eh::Exception)*/
    {
      const Generics::Time next_execution_time = call_();

      if(next_execution_time != Generics::Time::ZERO)
      {
        try
        {
          schedule(next_execution_time);
        }
        catch (const eh::Exception& ex)
        {
          Stream::Error ostr;
          ostr << __func__ << "(): schedule failed: " << ex.what();
          throw Exception(ostr);
        }
      }
    }

  protected:
    virtual
    ~DelegateGoalTask() noexcept = default;

  private:
    Generics::Time
    call_() noexcept
    {
      return delegate_();
    }

    Delegate delegate_;
  };

  template<typename FunctorType, typename ReturnType>
  struct VoidToPeriodHelper
  {
    VoidToPeriodHelper(
      const FunctorType& fun,
      const Generics::Time& /*period*/)
      : fun_(fun)
    {}

    Generics::Time
    operator()() const
    {
      return fun_();
    }

  private:
    FunctorType fun_;
  };

  template<typename FunctorType>
  struct VoidToPeriodHelper<FunctorType, void>
  {
    VoidToPeriodHelper(
      const FunctorType& fun,
      const Generics::Time& period)
      : fun_(fun),
        PERIOD_(period)
    {}

    Generics::Time
    operator()() const
    {
      return fun_(), Generics::Time::get_time_of_day() + PERIOD_;
    }

  private:
    FunctorType fun_;
    const Generics::Time PERIOD_;
  };

  template<class FunctorType>
  VoidToPeriodHelper<FunctorType, typename std::result_of<FunctorType()>::type>
  void_to_period_wrapper(
    const FunctorType& fun,
    const Generics::Time& period)
  {
    return VoidToPeriodHelper<FunctorType, typename std::result_of<FunctorType()>::type>(
      fun,
      period);
  }

  template<typename Delegate>
  Generics::Task_var
  make_delegate_task(const Delegate& delegate)
    /*throw(eh::Exception)*/
  {
    return new DelegateTask<Delegate>(delegate);
  }

  template<typename Delegate>
  TaskGoal_var
  make_delegate_goal_task(
    const Delegate& delegate,
    Generics::TaskRunner* task_runner)
    /*throw(eh::Exception)*/
  {
    return new DelegateTaskGoal<Delegate>(delegate, task_runner);
  }

  template<typename FunctorType>
  GoalTask_var
  make_functor_periodic_task_goal(
    const FunctorType& delegate,
    Generics::TaskRunner* task_runner,
    Generics::Planner* planner)
    /*throw (eh::Exception)*/
  {
    return new DelegateGoalTask<FunctorType>(
      delegate,
      task_runner,
      planner);
  }

  template<typename Delegate>
  GoalTask_var
  make_repeating_task(
    const Delegate& delegate,
    Generics::TaskRunner* task_runner,
    Generics::Planner* planner)
    /*throw (eh::Exception)*/
  {
    return make_functor_periodic_task_goal(
      delegate,
      task_runner,
      planner);
  }

  template<typename Delegate>
  GoalTask_var
  make_goal_task(
    const Delegate& delegate,
    Generics::TaskRunner* task_runner,
    Generics::Planner* planner,
    const Generics::Time& execute_period)
    /*throw (eh::Exception)*/
  {
    return make_functor_periodic_task_goal(
      void_to_period_wrapper(delegate, execute_period),
      task_runner,
      planner);
  }
}
}

#endif /* COMMONS_DELEGATETASKGOAL_HPP_ */
