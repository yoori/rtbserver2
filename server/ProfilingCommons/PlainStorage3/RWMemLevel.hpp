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
#ifndef RWMEMPLEVEL_HPP
#define RWMEMPLEVEL_HPP

#include <Sync/SyncPolicy.hpp>
#include <ReferenceCounting/AtomicImpl.hpp>

#include "BaseLevel.hpp"
#include "ReadMemLevel.hpp"

namespace AdServer
{
namespace ProfilingCommons
{
  //
  // RWMemLevel
  //
  template<typename KeyType, typename KeySerializerType>
  class RWMemLevel:
    public RWBaseLevel<KeyType>,
    public ReferenceCounting::AtomicImpl,
    protected MemLevelHolder<KeyType>
  {
  public:
    class KeyIteratorImpl:
      public ReadBaseLevel<KeyType>::KeyIterator,
      public ReferenceCounting::AtomicImpl
    {
    public:
      KeyIteratorImpl(
        const RWMemLevel<KeyType, KeySerializerType>* read_mem_level)
        noexcept;

      virtual bool
      get_next(
        KeyType& key,
        ProfileOperation& operation,
        Generics::Time& access_time)
        noexcept;

    protected:
      virtual ~KeyIteratorImpl() noexcept
      {}

    private:
      const ReferenceCounting::ConstPtr<
        RWMemLevel<KeyType, KeySerializerType> > rw_mem_level_;
      bool initialized_;
      KeyType cur_key_;
    };

    class IteratorImpl:
      public ReadBaseLevel<KeyType>::Iterator,
      public ReferenceCounting::AtomicImpl
    {
    public:
      IteratorImpl(
        const RWMemLevel<KeyType, KeySerializerType>* read_mem_level)
        noexcept;

      virtual bool
      get_next(
        KeyType& key,
        ProfileOperation& operation,
        Generics::Time& access_time)
        /*throw(typename ReadBaseLevel<KeyType>::Exception)*/;

      virtual Generics::ConstSmartMemBuf_var
      get_profile()
        /*throw(typename ReadBaseLevel<KeyType>::Exception)*/;

    protected:
      virtual ~IteratorImpl() noexcept
      {}

    private:
      const ReferenceCounting::ConstPtr<
        RWMemLevel<KeyType, KeySerializerType> > rw_mem_level_;
      bool initialized_;
      KeyType cur_key_;
    };

    ReferenceCounting::SmartPtr<ReadMemLevel<KeyType> >
    convert_to_read_mem_level()
      noexcept;

    virtual CheckProfileResult
    check_profile(const KeyType& key) const
      /*throw(typename RWBaseLevel<KeyType>::Exception)*/;

    virtual GetProfileResult
    get_profile(const KeyType& key) const
      /*throw(typename RWBaseLevel<KeyType>::Exception)*/;

    virtual typename ReadBaseLevel<KeyType>::KeyIterator_var
    get_key_iterator() const
      noexcept;

    virtual typename ReadBaseLevel<KeyType>::Iterator_var
    get_iterator(unsigned long read_buffer_size) const
      noexcept;

    virtual unsigned long
    size() const
      noexcept;

    virtual unsigned long
    area_size() const
      noexcept;

    virtual unsigned long
    merge_free_size() const
      noexcept;

    virtual Generics::Time
    min_access_time() const
      noexcept;

    virtual Generics::ConstSmartMemBuf_var
    save_profile(
      const KeyType& key,
      const Generics::ConstSmartMemBuf* mem_buf,
      ProfileOperation operation,
      unsigned long next_size,
      const Generics::Time& now)
      /*throw(typename RWBaseLevel<KeyType>::Exception)*/;

    virtual unsigned long
    remove_profile(
      const KeyType& key,
      unsigned long next_size)
      /*throw(typename RWBaseLevel<KeyType>::Exception)*/;

    void
    clear_expired(
      const Generics::Time& expire_time)
      /*throw(typename RWBaseLevel<KeyType>::Exception)*/;

  protected:
    virtual ~RWMemLevel() noexcept
    {}

    unsigned long
    eval_area_size_(const KeyType& key) const
      noexcept;

  private:
    typedef Sync::Policy::PosixThreadRW SyncPolicy;

  private:
    mutable SyncPolicy::Mutex lock_;
    KeySerializerType key_serializer_;
  };
}
}

#include "RWMemLevel.tpp"

#endif /*RWMEMLEVEL_HPP*/
