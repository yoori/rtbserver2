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
#ifndef FRONTENDCOMMONS_FRONTENDINTERFACE_HPP_
#define FRONTENDCOMMONS_FRONTENDINTERFACE_HPP_

#include <String/SubString.hpp>
#include <ReferenceCounting/AtomicImpl.hpp>
#include <ReferenceCounting/SmartPtr.hpp>
#include <Stream/MemoryStream.hpp>

#include <xsd/Frontends/FeConfig.hpp>
#include "FCGI.hpp"

namespace FrontendCommons
{
  /**
   * @class FrontendInterface
   *
   * @brief HTTP Frontend interface.
   */
  class FrontendInterface :
    public virtual ReferenceCounting::Interface
  {
  public:
    /**
     * @class Configuration
     *
     * @brief Frontend configuration.
     */
    class Configuration: public ReferenceCounting::AtomicImpl
    {
    public:
      DECLARE_EXCEPTION(InvalidConfiguration, eh::DescriptiveException);

      typedef xsd::AdServer::Configuration::FeConfigurationType FeConfig;

      /**
       * @brief Constructor.
       * @param config path
       */
      Configuration(const char* config_path);

      /**
       * @brief Read config.
       * Parse config file
       */
      void
      read() /*throw(InvalidConfiguration)*/;

      /**
       * @brief Get config file path.
       * @return path
       */
      const std::string&
      path() const;

      /**
       * @brief Get frontend config.
       * @return frontend config
       */
      const FeConfig&
      get() const /*throw(InvalidConfiguration)*/;

    protected:
      virtual
      ~Configuration() noexcept
      {}

    private:
      const std::string config_path_;
      std::unique_ptr<FeConfig> config_;
    };

    typedef ReferenceCounting::SmartPtr<Configuration> Configuration_var;

    /**
     * @brief Handle or not URI.
     * @param uri.
     */
    virtual bool
    will_handle(const String::SubString& uri) noexcept = 0;

    /**
     * @brief Handle HTTP request.
     * @param HTTP request
     * @param[out] HTTP response
     */
    virtual void
    handle_request(
      FCGI::HttpRequestHolder_var request,
      FCGI::HttpResponseWriter_var response_writer)
      noexcept = 0;

    /**
     * @brief Handle HTTP request without params.
     * @param HTTP request
     * @param[out] HTTP response
     */
    virtual void
    handle_request_noparams(
      FCGI::HttpRequestHolder_var request_holder,
      FCGI::HttpResponseWriter_var response_writer)
      /*throw(eh::Exception)*/;

    /**
     * @brief Initialize frontend.
     */
    virtual void
    init() /*throw(eh::Exception)*/ = 0;

    /**
     * @brief Shutdown frontend.
     */
    virtual void
    shutdown() noexcept = 0;
    
  protected:
    virtual
    ~FrontendInterface() noexcept = default;

    static bool
    parse_args_(
      FCGI::HttpRequestHolder_var request_holder,
      FCGI::HttpResponseWriter_var response_writer)
      /*throw(eh::Exception)*/;
  };

  typedef ReferenceCounting::SmartPtr<FrontendInterface> Frontend_var;
}

#include "FrontendInterface.ipp"

#endif /*FRONTENDCOMMONS_FRONTENDINTERFACE_HPP_*/
