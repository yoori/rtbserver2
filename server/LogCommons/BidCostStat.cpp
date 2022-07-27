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

#include "BidCostStat.hpp"
#include <LogCommons/LogCommons.ipp>

namespace AdServer {
namespace LogProcessing {

template <> const char* BidCostStatTraits::B::base_name_ = "BidCostStat";
template <> const char* BidCostStatTraits::B::signature_ = "BidCostStat";
template <> const char* BidCostStatTraits::B::current_version_ = "2.5";

std::istream&
operator>>(std::istream& is, BidCostStatKey& key)
{
  is >> key.adv_sdate_;
  if (is)
  {
    key.invariant();
    key.calc_hash_();
  }
  return is;
}

std::ostream&
operator<<(std::ostream& os, const BidCostStatKey& key)
  /*throw(eh::Exception)*/
{
  key.invariant();
  os << key.adv_sdate_;
  return os;
}

FixedBufStream<TabCategory>&
operator>>(FixedBufStream<TabCategory>& is, BidCostStatInnerKey& key)
  /*throw(eh::Exception)*/
{
  TokenizerInputArchive<> ia(is);
  ia >> key;
  if (is)
  {
    key.invariant();
    key.calc_hash_();
  }
  return is;
}

std::ostream&
operator<<(std::ostream& os, const BidCostStatInnerKey& key)
  /*throw(eh::Exception)*/
{
  TabOutputArchive oa(os);
  oa << key;
  return os;
}

FixedBufStream<TabCategory>&
operator>>(FixedBufStream<TabCategory>& is, BidCostStatInnerData& data)
  /*throw(eh::Exception)*/
{
  TokenizerInputArchive<Aux_::NoInvariants> ia(is);
  is >> data;
  return is;
}

std::ostream&
operator<<(std::ostream& os, const BidCostStatInnerData& data)
  /*throw(eh::Exception)*/
{
  SimpleTabOutputArchive oa(os);
  oa << data;
  return os;
}

} // namespace LogProcessing
} // namespace AdServer

