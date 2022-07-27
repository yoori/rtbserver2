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

#include "Request_v354.hpp"
#include <LogCommons/LogCommons.ipp>

namespace AdServer {
namespace LogProcessing {

const RequestData_V_3_5_4::DeliveryThresholdT
  RequestData_V_3_5_4::DataHolder::max_delivery_threshold_value_("1.00000");

FixedBufStream<TabCategory>&
operator>>(FixedBufStream<TabCategory>& is, RequestData_V_3_5_4& data)
  /*throw(eh::Exception)*/
{
  data.holder_ = new RequestData_V_3_5_4::DataHolder;
  TokenizerInputArchive<> ia(is);
  ia >> *data.holder_;
  return is;
}

} // namespace LogProcessing
} // namespace AdServer
