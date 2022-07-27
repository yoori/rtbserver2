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
#ifndef AD_SERVER_LOG_PROCESSING_CHANNEL_PRICE_RANGE_HPP
#define AD_SERVER_LOG_PROCESSING_CHANNEL_PRICE_RANGE_HPP


#include <cmath>
#include <iosfwd>
#include <Generics/Time.hpp>
#include <Generics/SimpleDecimal.hpp>
#include "LogCommons.hpp"
#include "StatCollector.hpp"
#include <Commons/StringHolder.hpp>
#include <LogCommons/GenericLogIoImpl.hpp>

namespace AdServer {
namespace LogProcessing {

typedef DayTimestamp ChannelPriceRangeKey;

class ChannelPriceRangeInnerKey
{
public:
  typedef Generics::SimpleDecimal<uint64_t, 11, 1> EcpmT;

  ChannelPriceRangeInnerKey()
  :
    creative_size_(),
    country_code_(),
    channel_id_(),
    ecpm_(),
    colo_id_(),
    hash_()
  {
  }

  ChannelPriceRangeInnerKey(
    const Commons::ImmutableString& creative_size,
    const Commons::ImmutableString& country_code,
    unsigned long channel_id,
    const EcpmT& ecpm,
    unsigned long colo_id
  )
  :
    creative_size_(creative_size),
    country_code_(country_code),
    channel_id_(channel_id),
    ecpm_(ecpm),
    colo_id_(colo_id),
    hash_()
  {
    calc_hash_();
  }

  bool operator==(const ChannelPriceRangeInnerKey& rhs) const
  {
    if (&rhs == this)
    {
      return true;
    }
    return creative_size_ == rhs.creative_size_ &&
      country_code_ == rhs.country_code_ &&
      channel_id_ == rhs.channel_id_ &&
      ecpm_ == rhs.ecpm_ &&
      colo_id_ == rhs.colo_id_;
  }

  const std::string& creative_size() const
  {
    return creative_size_.str();
  }

  const std::string& country_code() const
  {
    return country_code_.str();
  }

  unsigned long channel_id() const
  {
    return channel_id_;
  }

  const EcpmT& ecpm() const
  {
    return ecpm_;
  }

  unsigned long colo_id() const
  {
    return colo_id_;
  }

  size_t hash() const
  {
    return hash_;
  }

  friend
  FixedBufStream<TabCategory>&
  operator>>(FixedBufStream<TabCategory>& is, ChannelPriceRangeInnerKey& key)
    /*throw(eh::Exception)*/;

  friend
  std::ostream&
  operator<<(std::ostream& os, const ChannelPriceRangeInnerKey& key)
    /*throw(eh::Exception)*/;

private:
  void calc_hash_()
  {
    Generics::Murmur64Hash hasher(hash_);
    hash_add(hasher, channel_id_);
    hash_add(hasher, colo_id_);
    hash_add(hasher, ecpm_);
    hash_add(hasher, creative_size_.str());
    hash_add(hasher, country_code_.str());
  }

  Commons::ImmutableString creative_size_;
  Commons::ImmutableString country_code_;
  unsigned long channel_id_;
  EcpmT ecpm_;
  unsigned long colo_id_;
  size_t hash_;
};

class ChannelPriceRangeInnerData
{
public:
  typedef FixedPrecisionDouble<5> Double;

  ChannelPriceRangeInnerData() noexcept
  :
    unique_users_count_(),
    impops_()
  {
  }

  ChannelPriceRangeInnerData(
    Double unique_users_count,
    unsigned long impops
  )
    noexcept
  :
    unique_users_count_(unique_users_count),
    impops_(impops)
  {
  }

  bool
  operator==(const ChannelPriceRangeInnerData& rhs) const noexcept
  {
    return unique_users_count_ == rhs.unique_users_count_ &&
      impops_ == rhs.impops_;
  }

  ChannelPriceRangeInnerData&
  operator+=(const ChannelPriceRangeInnerData& rhs) noexcept
  {
    unique_users_count_ += rhs.unique_users_count_;
    impops_ += rhs.impops_;
    return *this;
  }

  Double
  unique_users_count() const noexcept
  {
    return unique_users_count_;
  }

  unsigned long
  impops() const noexcept
  {
    return impops_;
  }

  friend
  FixedBufStream<TabCategory>&
  operator>>(FixedBufStream<TabCategory>& is, ChannelPriceRangeInnerData& data)
    /*throw(eh::Exception)*/;

  friend
  std::ostream&
  operator<<(std::ostream& os, const ChannelPriceRangeInnerData& data)
    /*throw(eh::Exception)*/;

private:
  Double unique_users_count_;
  unsigned long impops_;
};

typedef StatCollector<
          ChannelPriceRangeKey,
          StatCollector<
            ChannelPriceRangeInnerKey,
            ChannelPriceRangeInnerData,
            false, // Don't exclude null values
            true
          >
        > ChannelPriceRangeCollector;

typedef LogDefaultTraits<ChannelPriceRangeCollector> ChannelPriceRangeTraits;

} // namespace LogProcessing
} // namespace AdServer

#endif /* AD_SERVER_LOG_PROCESSING_CHANNEL_PRICE_RANGE_HPP */

