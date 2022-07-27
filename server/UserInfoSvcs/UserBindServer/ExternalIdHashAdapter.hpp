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
#ifndef EXTERNAL_ID_HASH_ADAPTER_HPP_
#define EXTERNAL_ID_HASH_ADAPTER_HPP_

namespace AdServer
{
namespace UserInfoSvcs
{
  class ExternalIdHashAdapter
  {
  public:
    class EncodingSelector;

  public:
    ExternalIdHashAdapter() noexcept;

    ExternalIdHashAdapter(const String::SubString& text, size_t hash)
      noexcept;

    ExternalIdHashAdapter(ExternalIdHashAdapter&& init) noexcept;

    ExternalIdHashAdapter(const ExternalIdHashAdapter& init) noexcept;

    ExternalIdHashAdapter&
    operator=(const ExternalIdHashAdapter& init) noexcept;

    ExternalIdHashAdapter&
    operator=(ExternalIdHashAdapter&& init) noexcept;

    ~ExternalIdHashAdapter() noexcept;

    bool
    operator==(const ExternalIdHashAdapter& right) const noexcept;

    size_t
    hash() const noexcept;

    std::string
    text() const noexcept;

    unsigned char
    encoder_id() const noexcept;

  protected:
    void
    free_buf_() noexcept;

  protected:
    void* data_;
  };  
};
};

namespace AdServer
{
namespace UserInfoSvcs
{
  // StringDefHashAdapter
  inline
  ExternalIdHashAdapter::
  ExternalIdHashAdapter() noexcept
    : data_(0)
  {}

  inline
  ExternalIdHashAdapter::
  ExternalIdHashAdapter(ExternalIdHashAdapter&& init)
    noexcept
  {
    data_ = init.data_;
    init.data_ = 0;
  }

  inline
  size_t
  ExternalIdHashAdapter::
  hash() const
    noexcept
  {
    return data_ ? *static_cast<uint32_t*>(data_) : 0;
  }
};
};

#endif /*EXTERNAL_ID_HASH_ADAPTER_HPP_*/
