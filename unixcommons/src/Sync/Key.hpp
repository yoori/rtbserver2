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
#ifndef SYNC_KEY_HPP
#define SYNC_KEY_HPP

#include <pthread.h>

#include <eh/Errno.hpp>

#include <Generics/Uncopyable.hpp>
#include <Generics/Function.hpp>


namespace Sync
{
  /**
   * Performs access to thread-specific data stored as pointers
   */
  template <typename Data>
  class Key : private Generics::Uncopyable
  {
  public:
    DECLARE_EXCEPTION(Exception, eh::DescriptiveException);

    /**
     * Create thread-specific key
     * @param destructor optional destructor called for data on thread
     * termination
     */
    explicit
    Key(void (*destructor)(void*) = 0) /*throw (Exception)*/;

    /**
     * Store data for the current thread
     * @param data to store
     */
    void
    set_data(Data* data) /*throw (Exception)*/;

    /**
     * Get stored data for the current thread
     * @return stored data
     */
    Data*
    get_data() throw ();

  private:
    pthread_key_t key_;
  };
}

namespace Sync
{
  template <typename Data>
  Key<Data>::Key(void (*destructor)(void*)) /*throw (Exception)*/
  {
    const int RES = pthread_key_create(&key_, destructor);
    if (RES)
    {
      eh::throw_errno_exception<Exception>(RES, FNE,
        "Failed to create key");
    }
  }

  template <typename Data>
  void
  Key<Data>::set_data(Data* data) /*throw (Exception)*/
  {
    const int RES = pthread_setspecific(key_, data);
    if (RES)
    {
      eh::throw_errno_exception<Exception>(RES, FNE,
        "Failed to set data");
    }
  }

  template <typename Data>
  Data*
  Key<Data>::get_data() throw ()
  {
    return static_cast<Data*>(pthread_getspecific(key_));
  }
}

#endif
