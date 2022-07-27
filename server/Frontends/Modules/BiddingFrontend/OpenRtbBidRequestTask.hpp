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
#ifndef OPENRTBBIDREQUESTTASK_HPP_
#define OPENRTBBIDREQUESTTASK_HPP_

#include <iostream>
#include "BidRequestTask.hpp"

namespace AdServer
{
namespace Bidding
{
  //
  // OpenRtbBidRequestTask
  //
  class OpenRtbBidRequestTask: public BidRequestTask
  {
  public:
    OpenRtbBidRequestTask(
      Frontend* bid_frontend,
      FCGI::HttpRequestHolder_var request_holder,
      FCGI::HttpResponseWriter_var response_writer,
      const Generics::Time& start_processing_time)
      /*throw (Invalid)*/;

    virtual void
    print_request(std::ostream& out) const noexcept;

    virtual bool
    read_request() noexcept;

    /*
    virtual bool
    fill_request_info(std::string& keywords)
      noexcept;
    */

    virtual bool
    write_response(
      const AdServer::CampaignSvcs::CampaignManager::RequestCreativeResult&
        campaign_match_result)
      noexcept;

    virtual void
    write_empty_response(unsigned int code)
      noexcept;

    virtual void
    clear() noexcept;

  public:
    //std::string bid_response;
    const std::string uri;

  protected:
    virtual
    ~OpenRtbBidRequestTask() noexcept = default;

    void
    fill_openrtb_response_(
      std::ostream& response_ostr,
      const RequestInfo& request_info,
      const AdServer::CampaignSvcs::CampaignManager::RequestParams& request_params,
      const JsonProcessingContext& context,
      const AdServer::CampaignSvcs::CampaignManager::RequestCreativeResult& campaign_match_result,
      bool fill_yandex_attributes)
      noexcept;

    void
    fill_yandex_response_(
      std::ostream& response_ostr,
      const RequestInfo& request_info,
      const AdServer::CampaignSvcs::CampaignManager::
        RequestParams& request_params,
      const JsonProcessingContext& context,
      const AdServer::CampaignSvcs::CampaignManager::
        RequestCreativeResult& campaign_match_result)
      noexcept;

    void
    fill_native_response_(
      AdServer::Commons::JsonObject* root_json,
      const JsonAdSlotProcessingContext::Native& native_context,
      const AdServer::CampaignSvcs::CampaignManager::AdSlotResult& ad_slot_result,
      bool need_escape,
      bool add_root_native,
      SourceTraits::NativeAdsInstantiateType instantiate_type);

    void
    add_response_notice_(
      AdServer::Commons::JsonObject& bid_object,
      const String::SubString& url,
      SourceTraits::NoticeInstantiateType notice_instantiate_type);

  private:
    std::string uri_;
    JsonProcessingContext context_;
  };
}
}

#endif /*OPENRTBBIDREQUESTTASK_HPP_*/
