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
#ifndef FRONTENDS_PUBPIXELFRONTEND_PUBPIXELFRONTEND_HPP
#define FRONTENDS_PUBPIXELFRONTEND_PUBPIXELFRONTEND_HPP

#include <string>

#include <eh/Exception.hpp>

#include <ReferenceCounting/AtomicImpl.hpp>
#include <Generics/ActiveObject.hpp>
#include <Logger/Logger.hpp>
#include <Logger/DistributorLogger.hpp>

#include <HTTP/Http.hpp>
#include <CORBACommons/CorbaAdapters.hpp>

#include <Frontends/FrontendCommons/HTTPUtils.hpp>
#include <Frontends/FrontendCommons/CampaignManagersPool.hpp>
#include <Frontends/FrontendCommons/HTTPExceptions.hpp>
#include <Frontends/FrontendCommons/FrontendInterface.hpp>
#include <Frontends/FrontendCommons/FrontendTaskPool.hpp>

#include "RequestInfoFiller.hpp"

namespace AdServer
{
namespace PubPixel
{
  class Frontend:
    private FrontendCommons::HTTPExceptions,
    private Logging::LoggerCallbackHolder,
    public FrontendCommons::FrontendTaskPool,
    public virtual ReferenceCounting::AtomicImpl
  {
  public:
    typedef FrontendCommons::HTTPExceptions::Exception Exception;

  public:
    Frontend(
      Configuration* frontend_config,
      Logging::Logger* logger)
      /*throw(eh::Exception)*/;

    typedef ReferenceCounting::SmartPtr<Frontend> Frontend_var;

    static Frontend_var instance;

    /** Determines whether the module is able to process the URI.
     *
     * @param uri URI provided by Apache.
     */
    virtual bool
    will_handle(
      const String::SubString& uri) noexcept;

    /** Executed if will_handle returns true; processes an HTTP request. Provides
     *  browsing context to a Channel Manager, returns list of channels in the HTTP
     *  response.
     *
     * @return HTTP status code.
     */
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

    bool
    log(const String::SubString& text,
      unsigned long severity = Logging::Logger::INFO,
      const char* aspect = 0,
      const char* error_code = 0) const
      noexcept;

    unsigned long
    log_level() noexcept;

  private:
    typedef Configuration::FeConfig::CommonFeConfiguration_type
      CommonFeConfiguration;

    typedef Configuration::FeConfig::PubPixelFeConfiguration_type
      PubPixelFeConfiguration;

    typedef std::unique_ptr<CommonFeConfiguration> CommonConfigPtr;
    typedef std::unique_ptr<PubPixelFeConfiguration> ConfigPtr;

    struct TraceLevel
    {
      enum
      {
        LOW = Logging::Logger::TRACE,
        MIDDLE,
        HIGH
      };
    };

  private:
    virtual ~Frontend() noexcept;

    void parse_config_() /*throw(Exception)*/;

    int
    handle_request_(
      const FCGI::HttpRequest& request,
      FCGI::HttpResponse& response)
      noexcept;

  private:
    // configuration
    Configuration_var frontend_config_;
    CommonConfigPtr common_config_;
    ConfigPtr config_;

    std::unique_ptr<RequestInfoFiller> request_info_filler_;
    CORBACommons::CorbaClientAdapter_var corba_client_adapter_;
    FrontendCommons::CampaignManagersPool<Exception> campaign_managers_;
  };
} // namespace PubPixel
} // namespace AdServer

//
// Inlines
//
namespace AdServer
{
namespace PubPixel
{
  inline
  Frontend::~Frontend() noexcept
  {}

  inline
  unsigned long
  Frontend::log_level() noexcept
  {
    if (!logger())
    {
      return 0;
    }

    return config_->Logger().log_level();
  }
} // namespace PubPixel
} // namespace AdServer

#endif /*FRONTENDS_PUBPIXELFRONTEND_PUBPIXELFRONTEND_HPP*/
