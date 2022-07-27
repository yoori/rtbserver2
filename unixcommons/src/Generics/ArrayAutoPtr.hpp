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
 * @file   Generics/ArrayAutoPtr.hpp
 * @author Dmitry Trifilov
 */

#ifndef GENERICS_ARRAYAUTOPTR_HPP
#define GENERICS_ARRAYAUTOPTR_HPP

#include <eh/Exception.hpp>


namespace Generics
{
  template <typename T>
  class ArrayAutoPtr;

  /**
   * An ArrayAutoPtr provides semantic of
   * STRICT OWNERSHIP over an array pointer.
   */
  template <typename T>
  class ArrayAutoPtr
  {
  public:
    typedef T ElementType;

    /**
     * Constructor
     */
    ArrayAutoPtr() throw ();

    /**
     * Constructor
     * @param size size of the array to allocate (zero - not to allocate)
     */
    explicit
    ArrayAutoPtr(unsigned size) /*throw (eh::Exception)*/;

    ArrayAutoPtr(ArrayAutoPtr&) throw () = delete;

    /**
     * Move constructor
     * Transforms ownership from src to the constructed object
     * @param src former owner of the array
     */
    ArrayAutoPtr(ArrayAutoPtr&& src) throw ();

    /**
     * Destructor
     * Deallocates owned array
     */
    ~ArrayAutoPtr() throw ();

    ArrayAutoPtr&
    operator =(ArrayAutoPtr& src) throw () = delete;

    /**
     * Assignment operator
     * Transforms ownership from src to the object
     * @param src former owner of the array
     */
    ArrayAutoPtr&
    operator =(ArrayAutoPtr&& src) throw ();

    /**
     * Accessor for the array
     * @return pointer to stored array
     */
    T*
    get() const throw ();

    /**
     * Accessor for element of the array
     * @param index index of the required element of the array
     * @return reference to element
     */
    T&
    operator [](unsigned index) throw ();

    /**
     * Accessor for constant element of the array
     * @param index index of the required element of the array
     * @return constant reference to element
     */
    const T&
    operator [](unsigned index) const throw ();

    /**
     * Releases ownership
     * @return previously stored pointer to the array
     */
    T*
    release() throw ();

    /**
     * Releases stored array (if any) and allocated a new one (if size is
     * positive)
     * @param size size of a new array
     */
    void
    reset(unsigned size) /*throw (eh::Exception)*/;

    /**
     * Releases stored array (if any) and resets the pointer with a new one.
     * May lead to problems (if ptr is not pointer to array of T).
     * @param ptr new pointer to hold
     */
    void
    unsafe_reset(T* ptr) throw ();

    /**
     * Never implemented thus usage will lead to error messages.
     */
    template <typename U>
    void
    unsafe_reset(U*) throw () = delete;

    /**
     * Swaps pointers of the object and src
     * @param src another object to swap pointers with
     */
    void
    swap(ArrayAutoPtr& src) throw ();

  private:
    T* ptr_;
  };


  typedef ArrayAutoPtr<char> ArrayChar;
  typedef ArrayAutoPtr<unsigned char> ArrayByte;
  typedef ArrayAutoPtr<wchar_t> ArrayWChar;
}

//==============================================================================
// Implementation
//==============================================================================
namespace Generics
{
  //
  // ArrayAutoPtr class
  //

  template <typename T>
  T*
  ArrayAutoPtr<T>::get() const throw ()
  {
    return ptr_;
  }

  template <typename T>
  T&
  ArrayAutoPtr<T>::operator [](unsigned index) throw ()
  {
    return ptr_[index];
  }

  template <typename T>
  const T&
  ArrayAutoPtr<T>::operator [](unsigned index) const throw ()
  {
    return ptr_[index];
  }

  template <typename T>
  T*
  ArrayAutoPtr<T>::release() throw ()
  {
    T* ptr(ptr_);
    ptr_ = 0;

    return ptr;
  }

  template <typename T>
  void
  ArrayAutoPtr<T>::unsafe_reset(T* ptr) throw ()
  {
    if (ptr_ != ptr)
    {
      if (ptr_)
      {
        delete [] ptr_;
      }

      ptr_ = ptr;
    }
  }

  template <typename T>
  void
  ArrayAutoPtr<T>::reset(unsigned size) /*throw (eh::Exception)*/
  {
    T* ptr = size ? new T[size] : 0;

    if (ptr_)
    {
      delete [] ptr_;
    }

    ptr_ = ptr;
  }

  template <typename T>
  void
#if __GNUC__ == 4 && __GNUC_MINOR__ == 4
  ArrayAutoPtr<T>::swap(ArrayAutoPtr&& src) throw ()
#else
  ArrayAutoPtr<T>::swap(ArrayAutoPtr& src) throw ()
#endif
  {
    std::swap(ptr_, src.ptr_);
  }

  template <typename T>
  ArrayAutoPtr<T>::ArrayAutoPtr() throw ()
    : ptr_(0)
  {
  }

  template <typename T>
  ArrayAutoPtr<T>::ArrayAutoPtr(unsigned size) /*throw (eh::Exception)*/
    : ptr_(size ? new T[size] : 0)
  {
  }

  template <typename T>
  ArrayAutoPtr<T>::ArrayAutoPtr(ArrayAutoPtr&& src) throw ()
    : ptr_(src.release())
  {
  }

  template <typename T>
  ArrayAutoPtr<T>&
  ArrayAutoPtr<T>::operator =(ArrayAutoPtr&& src) throw ()
  {
    if (this != &src)
    {
      unsafe_reset(src.release());
    }

    return *this;
  }


  template <typename T>
  ArrayAutoPtr<T>::~ArrayAutoPtr() throw ()
  {
    unsafe_reset(0);
  }


  template <typename T>
  void
  swap(ArrayAutoPtr<T>& x, ArrayAutoPtr<T>& y) throw ()
  {
    x.swap(y);
  }

#if __GNUC__ == 4 && __GNUC_MINOR__ == 4
  template <typename T>
  void
  swap(ArrayAutoPtr<T>&& x, ArrayAutoPtr<T>& y) throw ()
  {
    x.swap(y);
  }

  template <typename T>
  void
  swap(ArrayAutoPtr<T>& x, ArrayAutoPtr<T>&& y) throw ()
  {
    x.swap(y);
  }
#endif
}

#endif
