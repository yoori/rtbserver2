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
// file      : ReferenceCounting/DefaultImpl.hpp
// author    : Boris Kolpackov <boris@kolpackov.net>
// copyright : Copyright (c) 2002-2003 Boris Kolpackov
// license   : http://kolpackov.net/license.html

#ifndef REFERENCE_COUNTING_DEFAULT_IMPL_HPP
#define REFERENCE_COUNTING_DEFAULT_IMPL_HPP

#include <cassert>

#include <Sync/NullSynchPolicy.hpp>

#include <ReferenceCounting/Interface.hpp>


namespace ReferenceCounting
{
  // Default reference counter implementation with parameterized
  // synchronization policy. It is assumed that none of the SynchPolicy
  // types throw any logic exceptions. If in fact they do then these
  // exceptions won't be handled and will be automatically converted
  // to system exceptions.

  template <typename SynchPolicy = Sync::Policy::Null>
  class DefaultImpl :
    public virtual Interface,
    private Generics::Uncopyable
  {
  public:
    virtual
    void
    add_ref() const throw ();

    virtual
    void
    remove_ref() const throw ();

  protected:
    DefaultImpl() throw ();
    virtual
    ~DefaultImpl() throw ();


  private:
    typedef typename SynchPolicy::Mutex Mutex;
    typedef typename SynchPolicy::WriteGuard Guard;

    mutable Mutex lock_;
    mutable unsigned long ref_count_;
  };
}

namespace ReferenceCounting
{
  template <typename SynchPolicy>
  DefaultImpl<SynchPolicy>::DefaultImpl() throw ()
    : ReferenceCounting::Interface(), lock_(), ref_count_(1)
  {
  }

  template <typename SynchPolicy>
  DefaultImpl<SynchPolicy>::~DefaultImpl() throw ()
  {
#ifndef NVALGRIND
    RunningOnValgrind<>::check_ref_count(ref_count_);
#endif
  }

  template <typename SynchPolicy>
  void
  DefaultImpl<SynchPolicy>::add_ref() const throw ()
  {
    Guard guard(lock_);
    ref_count_++;
  }

  template <typename SynchPolicy>
  void
  DefaultImpl<SynchPolicy>::remove_ref() const throw ()
  {
    bool delete_this;

    {
      Guard guard(lock_);

      assert(ref_count_ > 0);
      delete_this = !--ref_count_;
    }

    if (delete_this)
    {
      delete this;
    }
  }
}

#endif
