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

#include "SiteChannelStat.hpp"
#include <LogCommons/LogCommons.ipp>

namespace AdServer {
namespace LogProcessing {

template <> const char* SiteChannelStatTraits::B::base_name_ = "SiteChannelStat";
template <> const char* SiteChannelStatTraits::B::signature_ = "SiteChannelStat";
template <> const char* SiteChannelStatTraits::B::current_version_ = "1.1";

std::istream&
operator>>(std::istream &is, SiteChannelStatKey &key)
{
  is >> key.sdate_;
  read_eol(is);
  is >> key.colo_id_;
  key.calc_hash();
  return is;
}

std::ostream&
operator<<(std::ostream &os, const SiteChannelStatKey &key)
  /*throw(eh::Exception)*/
{
  os << key.sdate_ << '\n' << key.colo_id_;
  return os;
}

std::istream&
operator>>(std::istream &is, SiteChannelStatInnerKey &key)
  /*throw(eh::Exception)*/
{
  is >> key.tag_id_;
  read_tab(is);
  is >> key.channel_id_;
  key.calc_hash();
  return is;
}

std::ostream&
operator<<(std::ostream &os, const SiteChannelStatInnerKey &key)
  /*throw(eh::Exception)*/
{
  os << key.tag_id_ << '\t';
  os << key.channel_id_;
  return os;
}

std::istream&
operator>>(std::istream &is, SiteChannelStatInnerData &data)
  /*throw(eh::Exception)*/
{
  is >> data.imps_;
  read_tab(is);
  is >> data.adv_revenue_;
  read_tab(is);
  is >> data.pub_revenue_;
  if (is)
  {
    data.invariant();
  }
  return is;
}

std::ostream&
operator<<(std::ostream &os, const SiteChannelStatInnerData &data)
  /*throw(eh::Exception)*/
{
  data.invariant();
  os << data.imps_ << '\t';
  os << data.adv_revenue_ << '\t';
  os << data.pub_revenue_;
  return os;
}

} // namespace LogProcessing
} // namespace AdServer

