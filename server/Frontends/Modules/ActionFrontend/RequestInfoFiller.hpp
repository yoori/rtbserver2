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
#ifndef ACTIONFRONTEND_REQUESTINFOFILLER_HPP
#define ACTIONFRONTEND_REQUESTINFOFILLER_HPP

#include <string>
#include <set>

#include <GeoIP/IPMap.hpp>
#include <Logger/Logger.hpp>
#include <Generics/Time.hpp>

#include <Commons/UserInfoManip.hpp>
#include <CampaignSvcs/CampaignCommons/CampaignTypes.hpp>
#include <Frontends/FrontendCommons/HTTPUtils.hpp>
#include <Frontends/FrontendCommons/FCGI.hpp>
#include <Frontends/FrontendCommons/RequestMatchers.hpp>
#include <Frontends/FrontendCommons/RequestParamProcessor.hpp>
#include <Frontends/FrontendCommons/FCGI.hpp>
#include <Frontends/CommonModule/CommonModule.hpp>
#include <Commons/LogReferrerUtils.hpp>

namespace AdServer
{
namespace Action
{
  struct RequestInfo
  {
    RequestInfo()
      : value(AdServer::CampaignSvcs::RevenueDecimal::ZERO),
        user_status(AdServer::CampaignSvcs::US_UNDEFINED),
        test_request(false),
        log_as_test(false),
        secure(false),
        redirect(true)
    {}

    Generics::Time time;
    AdServer::Commons::UserId user_id;
    AdServer::Commons::UserId utm_resolved_user_id;
    AdServer::Commons::UserId utm_cookie_user_id;
    std::string signed_client_id;
    GeoIPMapping::IPMapCity2::CityLocation location;
    std::string req_country;

    AdServer::Commons::Optional<unsigned long> campaign_id;
    AdServer::Commons::Optional<unsigned long> action_id;
    std::string order_id;
    AdServer::Commons::Optional<AdServer::CampaignSvcs::RevenueDecimal> value;
    AdServer::CampaignSvcs::UserStatus user_status;
    std::string referer;
    bool test_request;
    bool log_as_test;
    std::string peer_ip;
    std::set<unsigned long> platform_ids;
    std::string platform;
    std::string full_platform;
    std::string user_agent;

    std::string external_user_id;
    std::string source_id;
    std::string short_external_id;

    bool secure;
    bool redirect;

    std::string ifa;
  };

  typedef FrontendCommons::RequestParamProcessor<RequestInfo>
    RequestInfoParamProcessor;

  typedef ReferenceCounting::SmartPtr<RequestInfoParamProcessor>
    RequestInfoParamProcessor_var;

  class RequestInfoFiller: public FrontendCommons::HTTPExceptions
  {
  public:
    RequestInfoFiller(
      Logging::Logger* logger,
      CommonModule* common_module,
      const char* geo_ip_path,
      Commons::LogReferrer::Setting use_referer,
      bool set_uid)
      /*throw(eh::Exception)*/;

    void
    fill(RequestInfo& request_info,
      const FCGI::HttpRequest& request,
      const String::SubString& service_prefix) const
      /*throw(InvalidParamException, ForbiddenException, Exception)*/;

    const Logging::Logger_var&
    logger() const noexcept;

    void
    adapt_client_id_(
      const String::SubString& in,
      RequestInfo& request_info,
      bool allow_rewrite)
      const
      /*throw(InvalidParamException)*/;

  private:
    typedef std::unique_ptr<GeoIPMapping::IPMapCity2> IPMapPtr;

    typedef Generics::GnuHashTable<
      Generics::SubStringHashAdapter, RequestInfoParamProcessor_var>
      ParamProcessorMap;

  private:
    void
    add_processor_(
      bool headers,
      bool parameters,
      const String::SubString& name,
      RequestInfoParamProcessor* processor)
      noexcept;

    static bool
    parse_utm_term_(
      RequestInfo& request_info,
      const String::SubString& utm_term)
      noexcept;

  private:
    Logging::Logger_var logger_;

    CommonModule_var common_module_;
    IPMapPtr ip_map_;
    const Commons::LogReferrer::Setting use_referrer_;
    const bool set_uid_;

    ParamProcessorMap header_processors_;
    ParamProcessorMap param_processors_;
    ParamProcessorMap cookie_processors_;
  };
} // Action
} // AdServer

namespace AdServer
{
namespace Action
{
  inline
  const Logging::Logger_var&
  RequestInfoFiller::logger() const noexcept
  {
    return logger_;
  }
}
}

#endif /*ACTIONFRONTEND_REQUESTINFOFILLER_HPP*/
