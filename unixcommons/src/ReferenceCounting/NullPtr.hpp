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
#ifndef REFERENCECOUNTING_NULLPTR_HPP
#define REFERENCECOUNTING_NULLPTR_HPP


#if __GNUC__ == 4 && __GNUC_MINOR__ == 4
namespace ReferenceCounting
{
  struct NullPtr
  {
    template <typename T>
    operator T*() const throw ();
    template <typename T, typename D>
    operator D T::*() const throw ();
    operator bool() const throw ();
    bool
    operator ==(const NullPtr&) const throw ();
    bool
    operator !=(const NullPtr&) const throw ();

    NullPtr() throw () = delete;
    void
    operator &() throw () = delete;
    void
    operator =(NullPtr&) throw () = delete;
    void
    operator =(NullPtr&&) throw () = delete;
  };
}

static const ReferenceCounting::NullPtr nullptr(nullptr);

namespace std
{
  typedef decltype(nullptr) nullptr_t;

  template <typename T>
  typename add_rvalue_reference<T>::type
  declval() throw ();
}


namespace ReferenceCounting
{
  template <typename T>
  NullPtr::operator T*() const throw ()
  {
    return 0;
  }

  template <typename T, typename D>
  NullPtr::operator D T::*() const throw ()
  {
    return 0;
  }

  inline
  NullPtr::operator bool() const throw ()
  {
    return false;
  }

  inline
  bool
  NullPtr::operator ==(const NullPtr&) const throw ()
  {
    return true;
  }

  inline
  bool
  NullPtr::operator !=(const NullPtr&) const throw ()
  {
    return false;
  }
}
#endif

#endif
