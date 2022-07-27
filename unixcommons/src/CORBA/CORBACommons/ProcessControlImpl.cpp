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
 * @file   CORBACommons/ProcessControlImpl.cpp
 * @author Karen Aroutiounov [karen@peopleonpage.com]
 * Implements class for CORBA process control
 */

#include <CORBACommons/ProcessControlImpl.hpp>


namespace CORBACommons
{
  //
  // OrbShutdowner class
  //

  OrbShutdowner::OrbShutdowner() throw ()
  {
  }

  OrbShutdowner::~OrbShutdowner() throw ()
  {
  }


  //
  // SimpleOrbShutdowner class
  //

  SimpleOrbShutdowner::SimpleOrbShutdowner(CORBA::ORB_ptr orb) throw ()
    : orb_(CORBA::ORB::_duplicate(orb))
  {
  }

  SimpleOrbShutdowner::~SimpleOrbShutdowner() throw ()
  {
  }

  void
  SimpleOrbShutdowner::shutdown(bool type) throw ()
  {
    if (!CORBA::is_nil(orb_))
    {
      try
      {
        orb_->shutdown(type);
      }
      catch (...)
      {
      }
    }
  }


  //
  // ProcessControlImpl class
  //

  ProcessControlImpl::ProcessControlImpl(OrbShutdowner* shutdowner)
    /*throw (InvalidArgument, Exception, eh::Exception)*/
    : shutdowner_(::ReferenceCounting::add_ref(shutdowner)),
      job_(new ShutdownJob(shutdowner_)), thread_runner_(job_, 1)
  {
    try
    {
      thread_runner_.start();
    }
    catch (const eh::Exception& e)
    {
      Stream::Error ostr;
      ostr << FNS << "eh::Exception caught:" << e.what();
      throw Exception(ostr);
    }
  }

  ProcessControlImpl::~ProcessControlImpl() throw ()
  {
    job_->wake(false);
  }

  void
  ProcessControlImpl::wait() /*throw (eh::Exception)*/
  {
    thread_runner_.wait_for_completion();
  }

  void
  ProcessControlImpl::shutdown(CORBA::Boolean wait_for_completion)
    /*throw (CORBA::SystemException)*/
  {
    try
    {
      if (shutdowner_)
      {
        if (wait_for_completion)
        {
          job_->wake(true);
        }
        else
        {
          job_->wake(false);
          shutdowner_->shutdown(false);
        }
      }
    }
    catch (...)
    {
      // nothing to do for now
    }
  }


  //
  // ProcessControlImpl::ShutdownJob class
  //

  ProcessControlImpl::ShutdownJob::ShutdownJob(
    OrbShutdowner_var& shutdowner) throw ()
    : shutdowner_(shutdowner), sem_(0)
  {
  }

  ProcessControlImpl::ShutdownJob::~ShutdownJob() throw ()
  {
  }

  void
  ProcessControlImpl::ShutdownJob::work() throw ()
  {
    sem_.acquire();
    if (shutdown_ && shutdowner_)
    {
      shutdowner_->shutdown(true);
    }
  }

  void
  ProcessControlImpl::ShutdownJob::wake(bool shutdown) throw ()
  {
    shutdown_ = shutdown;
    sem_.release();
  }
}
