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
// file      : ReferenceCounting/Interface.hpp
// author    : Boris Kolpackov <boris@kolpackov.net>
// copyright : Copyright (c) 2002-2003 Boris Kolpackov
// license   : http://kolpackov.net/license.html

#ifndef REFERENCE_COUNTING_INTERFACE_HPP
#define REFERENCE_COUNTING_INTERFACE_HPP

#ifdef DEV_DEBUG
#include <valgrind/valgrind.h>
#else
#ifndef NVALGRIND
#define NVALGRIND
#endif
#endif

#include <Generics/Uncopyable.hpp>


namespace ReferenceCounting
{
  // Interface to a reference-countable object. Note that _remove_ref ()
  // member function has a no-throw semantic. Even though it can lead to
  // a diagnostic loss it was made no-throw because it has a destructor
  // semantic.

  class Interface
  {
  public:
    virtual
    void
    add_ref() const throw () = 0;

    virtual
    void
    remove_ref() const throw () = 0;

  protected:
    Interface() throw ();
    Interface(const volatile Interface& iface) throw ();

    virtual
    ~Interface() throw ();

  private:
    void
    operator =(const volatile Interface& iface) throw ();
  };

  template <typename Type>
  Type*
  add_ref(Type* ptr) throw ();

#ifndef NVALGRIND
  template <const int C = 0>
  class RunningOnValgrind
  {
  public:
    template <typename RefCount>
    static
    void
    check_ref_count(RefCount ref_count) throw ();

  private:
    static const int FLAG_;

    static
    int
    running_on_valgrind() throw ();
  };
#endif
}

namespace ReferenceCounting
{
  //
  // Interface class
  //

  inline
  Interface::Interface() throw ()
  {
  }

  inline
  Interface::Interface(const volatile Interface& /*iface*/) throw ()
  {
  }

  inline
  Interface::~Interface() throw ()
  {
  }


  template <typename Type>
  inline
  Type*
  add_ref (Type* ptr) throw ()
  {
    if (ptr)
    {
      ptr->add_ref();
    }
    return ptr;
  }


#ifndef NVALGRIND
  //
  // RunningOnValgrind class
  //

  template <const int C>
  int
  RunningOnValgrind<C>::running_on_valgrind() throw ()
  {
    int flag = RUNNING_ON_VALGRIND;
    return flag;
  }

  template <const int C>
  template <typename RefCount>
  void
  RunningOnValgrind<C>::check_ref_count(RefCount ref_count) throw ()
  {
    if (ref_count && FLAG_)
    {
      new char;
    }
  }

  template <const int C>
  const int RunningOnValgrind<C>::FLAG_ = running_on_valgrind();
#endif
}

#endif
