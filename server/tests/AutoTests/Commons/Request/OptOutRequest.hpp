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
#ifndef __AUTOTESTS_COMMONS_REQUEST_OPTOUTREQUEST_HPP
#define __AUTOTESTS_COMMONS_REQUEST_OPTOUTREQUEST_HPP

#include "BaseRequest.hpp"

namespace AutoTest
{
  /**
   * @class OptOutRequest
   * @brief Presentation of optout AdServer request.
   *
   * Allows users to become OpIn/OptOut under http request.
   */

  class OptOutRequest : public BaseRequest
  {
    typedef RequestParam <OptOutRequest> OptOutParam;

    /// Base url for OptOut AdServer request.
    static const char*      BASE_URL;

  public:

    /**
     * @brief Constuctor.
     *
     * Create the optout request and sets default values for params.
     */
    explicit OptOutRequest(bool set_defs = true);

    /**
     * @brief Copy constructor.
     *
     * @param other request
     */
    OptOutRequest(const OptOutRequest& other);

    //request params

    /**
     * @brief Represents 'op' param.
     *
     * Opt-Out operation. Can be one of: in, out, status.
     */
    OptOutParam op;

    /**
     * @brief Represents 'debug-time' param.
     *
     * Determines time of OptOut request.
     * Parameter is for debugging/testing purposes only. 
     */
    RequestParam <OptOutRequest, TimeParam> debug_time;

    /**
     * @brief Represents 'opted_in_url' param.
     *
     * Used only for op=status : specifies URL request should be redirected
     * if user isn't opted out and has uid.
     */
    OptOutParam opted_in_url;

    /**
     * @brief Represents 'opted_out_url' param.
     *
     * Used only for op=status : specifies URL request should be redirected
     * if user is opted out. 
     */
    OptOutParam opted_out_url;

    /**
     * @brief Represents 'opt_undef_url' param.
     *
     * Used only for op=status : specifies URL request should be redirected
     * if user isn't opted out and hasn't uid. 
     */
    OptOutParam opt_undef_url;

    /**
     * @brief Represents 'already_url' param.
     *
     * Specifies URL request should be redirected
     * if user is already opted out of types specified.
     */
    OptOutParam already_url;

    /**
     * @brief Represents 'success_url' param.
     *
     * Specifies URL request should be redirected
     * on successfull setting opt out of type specified. 
     */
    OptOutParam success_url;

    /**
     * @brief Represents 'testrequest' param.
     *
     */
    OptOutParam testrequest;

    /**
     * @brief Represents 'colo' param.
     *
     */
    OptOutParam colo;

    /**
     * @brief Represents 'ct' param.
     *
     */
    OptOutParam ct;

    /**
     * @brief Represents 'ce' param.
     * Used only for op=out: specifies OPTED_OUT cookie expire time.
     * Next formats available:
     *   100m - time in minutes,
     *   100 or 100d - time in days
     *
     */
    OptOutParam ce;

    /**
     * @brief Represents 'fail_url' param.
     *
     * Specifies URL request should be redirected on any failure.
     */
    OptOutParam fail_url;
    
    /**
     * @brief Represents 'User-Agent' HTTP header.
     */
    HeaderParam<OptOutRequest> user_agent;

  };

}//namespace AutoTest

#endif  // __AUTOTESTS_COMMONS_REQUEST_OPTOUTREQUEST_HPP
