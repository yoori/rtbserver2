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

#include "CmpStat.hpp"
#include <LogCommons/LogCommons.ipp>

namespace AdServer {
namespace LogProcessing {

template <> const char* CmpStatTraits::B::base_name_ = "CMPStat";
template <> const char* CmpStatTraits::B::signature_ = "CMPStat";
template <> const char* CmpStatTraits::B::current_version_ = "3.3";

const CmpStatInnerKey::DeliveryThresholdT
  CmpStatInnerKey::max_delivery_threshold_value_("1.00000");

const CmpStatInnerKey_V_2_3::DeliveryThresholdT
  CmpStatInnerKey_V_2_3::max_delivery_threshold_value_("1.00000");

std::istream&
operator>>(std::istream& is, CmpStatKey& key)
{
  is >> key.sdate_;
  read_eol(is);
  is >> key.adv_sdate_;
  read_eol(is);
  is >> key.colo_id_;
  key.calc_hash_();
  return is;
}

std::ostream&
operator<<(std::ostream& os, const CmpStatKey& key)
  /*throw(eh::Exception)*/
{
  os << key.sdate_ << '\n' << key.adv_sdate_ << '\n' << key.colo_id_;
  return os;
}

FixedBufStream<TabCategory>&
operator>>(FixedBufStream<TabCategory>& is, CmpStatInnerKey& key)
  /*throw(eh::Exception)*/
{
  is >> key.publisher_account_id_;
  is >> key.tag_id_;
  is >> key.size_id_;
  is >> key.country_code_;
  is >> key.currency_exchange_id_;
  is >> key.delivery_threshold_;
  is >> key.adv_account_id_;
  is >> key.campaign_id_;
  is >> key.ccg_id_;
  is >> key.cc_id_;
  is >> key.channel_id_;
  is >> key.channel_rate_id_;
  is >> key.fraud_;
  is >> key.walled_garden_;
  if (is)
  {
    key.invariant_();
    key.calc_hash_();
  }
  return is;
}

std::ostream&
operator<<(std::ostream& os, const CmpStatInnerKey& key)
  /*throw(eh::Exception)*/
{
  key.invariant_();
  os << key.publisher_account_id_ << '\t';
  os << key.tag_id_ << '\t';
  os << key.size_id_ << '\t';
  os << key.country_code_ << '\t';
  os << key.currency_exchange_id_ << '\t';
  os << key.delivery_threshold_ << '\t';
  os << key.adv_account_id_ << '\t';
  os << key.campaign_id_ << '\t';
  os << key.ccg_id_ << '\t';
  os << key.cc_id_ << '\t';
  os << key.channel_id_ << '\t';
  os << key.channel_rate_id_ << '\t';
  os << key.fraud_ << '\t';
  os << key.walled_garden_;
  return os;
}

FixedBufStream<TabCategory>&
operator>>(FixedBufStream<TabCategory>& is, CmpStatInnerData& data)
  /*throw(eh::Exception)*/
{
  is >> data.imps_;
  is >> data.clicks_;
  is >> data.cmp_amount_;
  is >> data.adv_amount_cmp_;
  is >> data.cmp_sys_amount_;
  if (is)
  {
    data.invariant_();
  }
  return is;
}

std::ostream&
operator<<(std::ostream& os, const CmpStatInnerData& data)
  /*throw(eh::Exception)*/
{
  data.invariant_();
  os << data.imps_ << '\t';
  os << data.clicks_ << '\t';
  os << data.cmp_amount_ << '\t';
  os << data.adv_amount_cmp_ << '\t';
  os << data.cmp_sys_amount_;
  return os;
}

FixedBufStream<TabCategory>&
operator>>(FixedBufStream<TabCategory>& is, CmpStatInnerKey_V_2_3& key)
  /*throw(eh::Exception)*/
{
  is >> key.publisher_account_id_;
  is >> key.tag_id_;
  is >> key.country_code_;
  is >> key.currency_exchange_id_;
  is >> key.delivery_threshold_;
  is >> key.adv_account_id_;
  is >> key.campaign_id_;
  is >> key.ccg_id_;
  is >> key.cc_id_;
  is >> key.channel_id_;
  is >> key.channel_rate_id_;
  is >> key.fraud_;
  is >> key.walled_garden_;
  if (is)
  {
    key.invariant_();
    key.calc_hash_();
  }
  return is;
}

} // namespace LogProcessing
} // namespace AdServer

