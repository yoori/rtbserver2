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
#ifndef COMMONS_STRINGHOLDER_HPP
#define COMMONS_STRINGHOLDER_HPP

#include <string>

#include <ReferenceCounting/AtomicImpl.hpp>
#include <ReferenceCounting/SmartPtr.hpp>
#include <Generics/Hash.hpp>
#include <Generics/Hash.hpp>

namespace AdServer
{
namespace Commons
{
  /* const std::string holder for decrease
   *   number of std::string copy construction
   */
  class StringHolder: public ReferenceCounting::AtomicImpl
  {
  public:
    template <typename... T>
    explicit
    StringHolder(T... data) /*throw (eh::Exception)*/
      : str_(std::forward<T>(data)...)
    {
    }

    StringHolder(const String::SubString& str)
      : str_(str.data(), str.length())
    {}
    
    const std::string*
    operator ->() const noexcept
    {
      return &str_;
    }

    const std::string&
    str() const noexcept
    {
      return str_;
    }

    bool
    operator ==(const StringHolder& arg) const noexcept
    {
      return this == &arg || str_ == arg.str_;
    }

  private:
    virtual
    ~StringHolder() noexcept = default;

  private:
    std::string str_;
  };
  typedef ReferenceCounting::SmartPtr<
    StringHolder, ReferenceCounting::PolicyAssert>
    StringHolder_var;

  class StringHolderHashAdapter
  {
  public:
    StringHolderHashAdapter() noexcept
      : hash_(0)
    {
    }

    explicit
    StringHolderHashAdapter(StringHolder* str) noexcept
      : value_(ReferenceCounting::add_ref(str))
    {
      Generics::Murmur64Hash hash(hash_);
      hash_add(hash, value_->str());
    }
    
    StringHolder_var
    value() const noexcept
    {
      return value_;
    }

    bool
    operator ==(const StringHolderHashAdapter& right) const noexcept
    {
      return value_->str() == right.value_->str();
    }

    size_t
    hash() const noexcept
    {
      return hash_;
    }

  private:
    StringHolder_var value_;
    size_t hash_;
  };

  /**
   * Wrapper over StringHolder
   */
  class ImmutableString
  {
  public:
    typedef ReferenceCounting::ConstPtr<StringHolder,
      ReferenceCounting::PolicyAssert> CStringHolder_var;

    template <typename... T>
    explicit
    ImmutableString(T... data) /*throw (eh::Exception)*/
      : string_holder_(new StringHolder(std::forward<T>(data)...))
    {
    }

    template <typename T>
    ImmutableString&
    operator =(T&& data) /*throw (eh::Exception)*/
    {
      string_holder_ = new StringHolder(std::forward<T>(data));
      return *this;
    }

    const std::string&
    str() const noexcept
    {
      return string_holder_->str();
    }

    bool
    empty() const noexcept
    {
      return string_holder_->str().empty();
    }

    bool
    operator <(const ImmutableString& arg) const noexcept
    {
      return str() < arg.str();
    }

    bool
    operator ==(const ImmutableString& arg) const noexcept
    {
      return str() == arg.str();
    }

    bool
    operator !=(const ImmutableString& arg) const noexcept
    {
      return str() != arg.str();
    }

  private:
    CStringHolder_var string_holder_;
  };
}
}

inline
std::ostream&
operator <<(std::ostream& os, const AdServer::Commons::ImmutableString& arg)
  /*throw (eh::Exception)*/
{
  os << arg.str();
  return os;
}

#endif /*COMMONS_STRINGHOLDER_HPP*/
