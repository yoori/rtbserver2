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

#ifndef _AD_SERVER_OPTOUT_FRONTEND_HPP_
#define _AD_SERVER_OPTOUT_FRONTEND_HPP_

#include <string>

#include <eh/Exception.hpp>

#include <ReferenceCounting/AtomicImpl.hpp>
#include <Generics/ActiveObject.hpp>
#include <Logger/Logger.hpp>
#include <Logger/DistributorLogger.hpp>
#include <String/StringManip.hpp>
#include <HTTP/Http.hpp>
#include <HTTP/HTTPCookie.hpp>

#include <CORBA/CORBACommons/CorbaAdapters.hpp>

#include <Commons/CorbaConfig.hpp>

#include <xsd/Frontends/FeConfig.hpp>

#include <Frontends/FrontendCommons/HTTPUtils.hpp>
#include <Frontends/FrontendCommons/CampaignManagersPool.hpp>
#include <Frontends/FrontendCommons/CookieManager.hpp>
#include <Frontends/FrontendCommons/RequestMatchers.hpp>
#include <Frontends/FrontendCommons/FrontendInterface.hpp>
#include <Frontends/FrontendCommons/FrontendTaskPool.hpp>

#include "OptoutFrontendStat.hpp"
#include "RequestInfoFiller.hpp"

namespace AdServer
{
  namespace Configuration
  {
    using namespace xsd::AdServer::Configuration;
  }

  class OptoutFrontend:
    private FrontendCommons::HTTPExceptions,
    private Logging::LoggerCallbackHolder,
    public FrontendCommons::FrontendTaskPool,
    public virtual ReferenceCounting::AtomicImpl
  {
    typedef FrontendCommons::HTTPExceptions::Exception Exception;
    DECLARE_EXCEPTION(RequestFailure, Exception);

  public:
    typedef FCGI::HttpResponse HttpResponse;

    OptoutFrontend(
      Configuration* frontend_config,
      Logging::Logger* logger,
      CommonModule* common_module)
      /*throw (eh::Exception)*/;

    virtual bool
    will_handle(const String::SubString& uri) noexcept;

    void
    handle_request_(
      FCGI::HttpRequestHolder_var request_holder,
      FCGI::HttpResponseWriter_var response_writer)
      noexcept;

    /** Performs initialization for the module child process. */
    virtual void
    init() /*throw (eh::Exception)*/;

    /** Performs shutdown for the module child process. */
    virtual void
    shutdown() noexcept;

  private:

    struct TraceLevel
    {
      enum
      {
        LOW = Logging::Logger::TRACE,
        MIDDLE,
        HIGH
      };
    };

    typedef Configuration::FeConfig::CommonFeConfiguration_type
      CommonFeConfiguration;

    typedef Configuration::FeConfig::OptOutFeConfiguration_type
      OptOutFeConfiguration;

    typedef std::list<std::string> StringList;

    typedef std::unique_ptr<CommonFeConfiguration> CommonConfigPtr;
    typedef std::unique_ptr<OptOutFeConfiguration> ConfigPtr;
    typedef std::unique_ptr<FrontendCommons::CookieManager<
      FCGI::HttpRequest, FCGI::HttpResponse> >
      CookieManagerPtr;

  private:
    virtual
    ~OptoutFrontend() noexcept;

    void
    parse_config_() /*throw(Exception)*/;

    int
    handle_request_(
      const FCGI::HttpRequest& request,
      HttpResponse& response)
      noexcept;

    void
    set_OO_cookie(
      const String::SubString& oo_value,
      HttpResponse& response,
      const FCGI::HttpRequest& request,
      const Generics::Time& cookie_expire_time)
      /*throw (eh::Exception)*/;

    unsigned long calculate_status_(
      OptOperation operation,
      OptOperation old_operation) noexcept;

    int handle_status_operation_(
      const OptOperation old_oo_type,
      const std::string& oo_status_in_redirect_url,
      const std::string& oo_status_out_redirect_url,
      const std::string& oo_status_undef_redirect_url,
      HttpResponse& response) noexcept;

  private:
    /* configuration */
    std::string config_file_;
    CommonConfigPtr common_config_;
    ConfigPtr config_;
    Configuration_var frontend_config_;

    CommonModule_var common_module_;

    CookieManagerPtr cookie_manager_;
    OptOutFrontendStat_var stats_;

    CORBACommons::CorbaClientAdapter_var corba_client_adapter_;
    FrontendCommons::CampaignManagersPool<Exception> campaign_managers_;

    std::unique_ptr<OptOut::RequestInfoFiller> request_info_filler_;
  };
}

//
// Inlines
//
namespace AdServer
{
  /**
   * AdFrontend class
   */
  inline
  OptoutFrontend::~OptoutFrontend() noexcept
  {
  }
} /* AdServer */

#endif // _AD_SERVER_OPTOUT_FRONTEND_HPP_