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

#include "ChannelOverlapUserStat.hpp"
#include <LogCommons/LogCommons.ipp>

namespace AdServer {
namespace LogProcessing {

template <> const char*
ChannelOverlapUserStatTraits::B::base_name_ = "ChannelOverlapUserStat";

template <> const char*
ChannelOverlapUserStatTraits::B::signature_ = "ChannelOverlapUserStat";

template <> const char*
ChannelOverlapUserStatTraits::B::current_version_ = "2.5";

FixedBufStream<TabCategory>&
operator>>(
  FixedBufStream<TabCategory>& is,
  ChannelOverlapUserStatInnerKey& key
)
  /*throw(eh::Exception)*/
{
  is >> key.channel1_id_;
  is >> key.channel2_id_;
  key.calc_hash_();
  return is;
}

std::ostream&
operator<<(std::ostream& os, const ChannelOverlapUserStatInnerKey& key)
  /*throw(eh::Exception)*/
{
  os << key.channel1_id_ << '\t';
  os << key.channel2_id_;
  return os;
}

FixedBufStream<TabCategory>&
operator>>(
  FixedBufStream<TabCategory>& is,
  ChannelOverlapUserStatInnerData& data
)
  /*throw(eh::Exception)*/
{
  is >> data.unique_users_;
  return is;
}

std::ostream&
operator<<(std::ostream& os, const ChannelOverlapUserStatInnerData& data)
  /*throw(eh::Exception)*/
{
  os << data.unique_users_;
  return os;
}

} // namespace LogProcessing
} // namespace AdServer

