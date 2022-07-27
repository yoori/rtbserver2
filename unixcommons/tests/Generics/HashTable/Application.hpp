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
 * @file   Application.hpp
 * @author Karen Aroutiounov
 */

#ifndef GENERICS_HASHTABLE_APPLICATION_HPP
#define GENERICS_HASHTABLE_APPLICATION_HPP

#include <eh/Exception.hpp>
#include <Generics/Statistics.hpp>


namespace Generics
{
  class Application
  {
  public:
    DECLARE_EXCEPTION(Exception, eh::DescriptiveException);
    DECLARE_EXCEPTION(InvalidArgument, Exception);
    DECLARE_EXCEPTION(InvalidOperationOrder, Exception);

  public:
    Application() /*throw (eh::Exception)*/;

    virtual
    ~Application() throw ();

    void
    init(int& argc, char** argv)
      /*throw (InvalidArgument, Exception, eh::Exception)*/;

    void
    run() /*throw (InvalidOperationOrder, Exception, eh::Exception)*/;

    bool
    active() /*throw (eh::Exception)*/;
    void
    stop() /*throw (Exception, eh::Exception)*/;

  private:

    void
    print_results() /*throw (eh::Exception)*/;

    void
    test() /*throw (Exception, eh::Exception)*/;
    void
    test_iteration() /*throw (Exception, eh::Exception)*/;

    void
    test_string_table() /*throw (Exception, eh::Exception)*/;
    void
    test_long_table() /*throw (Exception, eh::Exception)*/;
    void
    test_inserter_table() /*throw (Exception, eh::Exception)*/;
    void
    test_inserter_set() /*throw (Exception, eh::Exception)*/;

  private:
    typedef Sync::PosixRWLock Mutex_;
    typedef Sync::PosixRGuard Read_Guard_;
    typedef Sync::PosixWGuard Write_Guard_;

    mutable Mutex_ lock_;

    bool active_;
    Generics::Time execution_time_;

    Generics::Time start_time_;
    Generics::Time stop_time_;

    Generics::ActiveObjectCallback_var callback_;
    Statistics::Collection_var statistics_;
  };
}

///////////////////////////////////////////////////////////////////////////////
// Inlines
///////////////////////////////////////////////////////////////////////////////

namespace Generics
{
  //
  // Application class
  //

  inline bool
  Application::active() /*throw (eh::Exception)*/
  {
    Read_Guard_ guard(lock_);
    return active_;
  }
}

#endif
