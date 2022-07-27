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
#ifndef BIDDINGFRONTEND_ADXMLREQUESTINFOFILLER_HPP_
#define BIDDINGFRONTEND_ADXMLREQUESTINFOFILLER_HPP_

#include <string>

#include <CampaignSvcs/CampaignManager/CampaignManager.hpp>
#include <CampaignSvcs/CampaignCommons/CampaignTypes.hpp>
#include <CampaignSvcs/CampaignCommons/CampaignSvcsVersionAdapter.hpp>
#include <Frontends/FrontendCommons/FCGI.hpp>
#include <Frontends/FrontendCommons/RequestParamProcessor.hpp>

namespace AdServer
{
namespace Bidding
{
  struct RequestInfo;
  class RequestInfoFiller;

  class AdXmlRequestInfoFiller
  {
  public:
    AdXmlRequestInfoFiller(RequestInfoFiller* request_info_filler);

    virtual
    ~AdXmlRequestInfoFiller() = default;

    void
    fill_by_request(
      ::AdServer::CampaignSvcs::CampaignManager::RequestParams& request_params,
      RequestInfo& request_info,
      std::string& keywords,
      const FCGI::HttpRequest& request,
      bool require_icon,
      const String::SubString& client,
      const String::SubString& size);

  protected:
    struct Context;

    typedef FrontendCommons::RequestParamProcessor<Context>
      RequestParamProcessor;
    typedef ReferenceCounting::SmartPtr<RequestParamProcessor>
      RequestParamProcessor_var;
    typedef Generics::GnuHashTable<
      Generics::SubStringHashAdapter, RequestParamProcessor_var>
      ParamProcessorMap;

  protected:
    void
    add_param_processor_(
      const String::SubString& name,
      RequestParamProcessor* processor)
      noexcept;

  protected:
    RequestInfoFiller* request_info_filler_;
    ParamProcessorMap param_processors_;
  };
}
}

#endif /*BIDDINGFRONTEND_ADXMLREQUESTINFOFILLER_HPP_*/
