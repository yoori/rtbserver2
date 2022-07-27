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

#include "SiteStat.hpp"
#include <LogCommons/LogCommons.ipp>

namespace AdServer {
namespace LogProcessing {

template <> const char* SiteStatTraits::B::base_name_ =
  "SiteStat";
template <> const char* SiteStatTraits::B::signature_ =
  "SiteStat";
template <> const char* SiteStatTraits::B::current_version_ =
  "1.0"; // Last change: AdServer v2.0

std::istream&
operator>>(std::istream& is, SiteStatKey& key)
{
  is >> key.isp_sdate_;
  read_eol(is);
  is >> key.colo_id_;
  if (is)
  {
    key.invariant();
    key.calc_hash_();
  }
  return is;
}

std::ostream&
operator<<(std::ostream& os, const SiteStatKey& key)
  /*throw(eh::Exception)*/
{
  key.invariant();
  os << key.isp_sdate_ << '\n' << key.colo_id_;
  return os;
}

FixedBufStream<TabCategory>&
operator>>(FixedBufStream<TabCategory>& is, SiteStatInnerKey& key)
  /*throw(eh::Exception)*/
{
  is >> key.site_id_;
  if (is)
  {
    key.invariant();
  }
  return is;
}

std::ostream&
operator<<(std::ostream& os, const SiteStatInnerKey& key)
  /*throw(eh::Exception)*/
{
  key.invariant();
  os << key.site_id_;
  return os;
}

FixedBufStream<TabCategory>&
operator>>(FixedBufStream<TabCategory>& is, SiteStatInnerData& data)
  /*throw(eh::Exception)*/
{
  is >> data.daily_reach_;
  is >> data.monthly_reach_;
  return is;
}

std::ostream&
operator<<(std::ostream& os, const SiteStatInnerData& data)
  /*throw(eh::Exception)*/
{
  os << data.daily_reach_ << '\t';
  os << data.monthly_reach_;
  return os;
}

} // namespace LogProcessing
} // namespace AdServer

