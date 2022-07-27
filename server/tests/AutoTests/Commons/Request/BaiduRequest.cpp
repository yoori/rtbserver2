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

#include "BaiduRequest.hpp"

namespace AutoTest
{
  const char* BaiduRequest::BASE_URL = "/baidu";
  const char* BaiduRequest::USER_ID = "Baidu_User";
  const char* BaiduRequest::DEFAULT_IP = "5.10.16.20";

  void
  BaiduRequest::Decoder::decode(
    std::ostream& out,
    Types decode_type,
    const std::string& data) const
  {
    if (decode_type == T_RESPONSE)
    {
      Baidu::BidResponse r;
      r.ParseFromString(data);
      out << r.DebugString();
    }
    else
    {
      Baidu::BidRequest r;
      r.ParseFromString(data);
      out << r.DebugString();
    }
  }

  BaiduRequest::BaiduRequest(bool set_defs) :
    BaseRequest(BASE_URL, BaseRequest::RT_ENCODED),
    bid_adslot_(bid_request_.add_adslot()),
    bid_mobile_app_(
      bid_request_.
        mutable_mobile()->
          mutable_mobile_app()),
    content_type(
      this,
      "Content-Type",
      "application/octet-stream",
      set_defs),
    accept_encoding(
      this,
      "Accept-Encoding",
      "identity",
      set_defs),
    debug_ccg(this, "debug.ccg"),
    aid(this, "aid"),
      src(this, "src"),
    debug_time(this, "debug.time"),
    debug_size(this, "debug.size"),
    id(this, &bid_request_, "id"),
    ip(this, &bid_request_, "ip", DEFAULT_IP, set_defs),
    user_agent(this, &bid_request_, "user_agent", DEFAULT_USER_AGENT, set_defs),
    user_id(this, &bid_request_, "baidu_user_id", USER_ID, set_defs),
    url(this, &bid_request_, "url"),
    excluded_product_category(this, &bid_request_, "excluded_product_category"),
    is_test(this, &bid_request_, "is_test"),
    app_id(this, bid_mobile_app_, "app_id"),
    app_bundle_id(this, bid_mobile_app_, "app_bundle_id"),
    slot_visibility(this, bid_adslot_, "slot_visibility", 1, set_defs),
    width(this, bid_adslot_, "width"),
    height(this, bid_adslot_, "height"),
    minimum_cpm(this, bid_adslot_, "minimum_cpm"),
    max_video_duration(this, bid_adslot_, "max_video_duration"),
    min_video_duration(this, bid_adslot_, "min_video_duration")
  { }
  
  BaiduRequest::~BaiduRequest() noexcept
  { }

  BaiduRequest::BaiduRequest(const BaiduRequest& other) :
    BaseRequest(BASE_URL, BaseRequest::RT_ENCODED),
    bid_request_(other.bid_request_),
    bid_adslot_(bid_request_.mutable_adslot(0)),
    bid_mobile_app_(bid_request_.mutable_mobile()->mutable_mobile_app()),
    content_type(this, other.content_type),
    accept_encoding(this, other.accept_encoding),
    debug_ccg(this, other.debug_ccg),
    aid(this, other.aid),
    src(this, other.src),
    debug_time(this, other.debug_time),
    debug_size(this, other.debug_size),
    id(this, &bid_request_, other.id),
    ip(this, &bid_request_, other.ip),
    user_agent(this, &bid_request_, other.user_agent),
    user_id(this, &bid_request_, other.user_id),
    url(this, &bid_request_, other.url),
    excluded_product_category(
      this, &bid_request_, other.excluded_product_category),
    is_test(this, &bid_request_, other.is_test),
    app_id(this, bid_mobile_app_, other.app_id),
    app_bundle_id(this, bid_mobile_app_, other.app_bundle_id),
    slot_visibility(this, bid_adslot_, other.slot_visibility),
    width(this, bid_adslot_, other.width),
    height(this, bid_adslot_, other.height),
    minimum_cpm(this, bid_adslot_, other.minimum_cpm),
    max_video_duration(this, bid_adslot_, other.max_video_duration),
    min_video_duration(this, bid_adslot_, other.min_video_duration)
  { }

  std::string
  BaiduRequest::body() const
  {
    std::string body;
    Baidu::BidRequest request(bid_request_);
    if (!bid_mobile_app_->ByteSize())
    {
      request.clear_mobile();
    }
    if (request.SerializeToString(&body))
    {
      return body;
    }
    throw Exception("Can't serialize Tanx::TanxRequest");
  }

  void
  BaiduRequest::set_decoder(
    ClientRequest* request) const
  {
    request->set_decoder(decoder_);
  }
}
