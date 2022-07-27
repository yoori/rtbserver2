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
#ifndef GENERICS_HOLDING_HASH_ADAPTER_HPP
#define GENERICS_HOLDING_HASH_ADAPTER_HPP

/* TODO: this file should be merged with Generics/HashTableAdapters.hpp */

#include <String/SubString.hpp>

#include <Generics/Hash.hpp>

namespace Generics
{
  class SubStringNoAlloc : public String::SubString
  {
  public:
    template <class S>
    SubStringNoAlloc(const S& text)
      : String::SubString(text) {}

    SubStringNoAlloc(const char* c, size_t l)
      : String::SubString(c, l) {}
  };

  class HoldingHashAdapter
  {
  public:
    typedef String::SubString text_type;

  public:
    HoldingHashAdapter()
      noexcept;

    HoldingHashAdapter(const String::SubString& text)
      noexcept;

    HoldingHashAdapter(const SubStringNoAlloc& text)
      noexcept;

    template <typename Traits, typename Alloc>
    HoldingHashAdapter(const std::basic_string<char, Traits, Alloc>& text)
      noexcept;

    HoldingHashAdapter(size_t hash, const String::SubString& text)
      noexcept;

    bool
    operator ==(const HoldingHashAdapter& src) const
      noexcept;

    bool
    operator ==(const String::SubString& src) const
      noexcept;

    bool
    operator ==(const std::string& src) const
      noexcept;

    bool
    operator <(const HoldingHashAdapter& src) const
      noexcept;

    size_t
    hash() const
      noexcept;

    operator const String::SubString&() const
      noexcept;

    operator String::SubString() const
      noexcept;

    /* String::SubString accessors */
    const String::SubString&
    text() const noexcept;

    String::SubString::ConstPointer
    data() const
      noexcept
    {
      return text_.data();
    }

    String::SubString::SizeType
    length() const
      noexcept
    {
      return text_.length();
    }

    String::SubString::SizeType
    size() const
      noexcept
    {
      return text_.size();
    }

    /* std::string accessors */
    std::string str() const noexcept;
    operator const std::string&() const noexcept;

  protected:
    void
    calc_hash_()
      noexcept;

  protected:
    std::string holder_;
    String::SubString text_;
    size_t hash_;
  };

//
// HoldingHashAdapter class
//
  inline
  HoldingHashAdapter::HoldingHashAdapter()
    noexcept
    : hash_(0)
  {
  }

  inline
  HoldingHashAdapter::HoldingHashAdapter(const String::SubString& text)
    noexcept
    : holder_(text.str()), text_(holder_)
  {
    calc_hash_();
  }

  inline
  HoldingHashAdapter::HoldingHashAdapter(const SubStringNoAlloc& text)
    noexcept
    : text_(text)
  {
    calc_hash_();
  }

  template <typename Traits, typename Alloc>
  HoldingHashAdapter::HoldingHashAdapter(
    const std::basic_string<char, Traits, Alloc>& text) noexcept
    : holder_(text), text_(holder_)
  {
    calc_hash_();
  }

  inline
  HoldingHashAdapter::HoldingHashAdapter(size_t hash,
    const String::SubString& text)
    noexcept
    : holder_(text.str()), text_(holder_), hash_(hash)
  {
  }

  inline
  bool
  HoldingHashAdapter::operator ==(const HoldingHashAdapter& src) const
    noexcept
  {
    return text_ == src.text_;
  }

  inline
  bool
  HoldingHashAdapter::operator ==(const String::SubString& src) const
    noexcept
  {
    return text_ == src;
  }

  inline
  bool
  HoldingHashAdapter::operator ==(const std::string& src) const
    noexcept
  {
    return text_ == src;
  }

  inline
  bool
  HoldingHashAdapter::operator <(const HoldingHashAdapter& src) const
    noexcept
  {
    return text_ < src.text_;
  }

  inline
  size_t
  HoldingHashAdapter::hash() const noexcept
  {
    return hash_;
  }

  inline
  HoldingHashAdapter::operator const String::SubString&() const noexcept
  {
    return text_;
  }

  inline
  HoldingHashAdapter::operator String::SubString() const noexcept
  {
    return text_;
  }

  inline
  const String::SubString&
  HoldingHashAdapter::text() const noexcept
  {
    return text_;
  }

  inline
  std::string
  HoldingHashAdapter::str() const
    noexcept
  {
    return text_.str();
  }

  inline
  HoldingHashAdapter::operator const std::string&()
    const noexcept
  {
    return holder_;
  }

  inline
  void
  HoldingHashAdapter::calc_hash_() noexcept
  {
    Murmur64Hash hash(hash_);
    hash_add(hash, text_);
  }
}

#endif
