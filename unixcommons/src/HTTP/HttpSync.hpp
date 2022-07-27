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
#ifndef HTTP_HTTPSYNC_HPP
#define HTTP_HTTPSYNC_HPP

#include <vector>

#include <HTTP/HttpAsync.hpp>


namespace HTTP
{
  typedef std::list<std::string> ExpectedHeaders;
  typedef std::vector<char> ResponseBody;

  /**
   * Function performs synchronous get request using
   * asynchronous http interface.
   * Result of request is returned either by assigns to passed references
   * or by exception
   * @param response_code response code
   * @param response_headers response headers listed in expected_headers
   * (if exist)
   * @param response_body response body
   * @param response_error received error (if any)
   * @param http reference to http interface to use for the request
   * @param http_request request URI
   * @param peer http server address
   * @param headers list of additional headers for request
   */
  void
  syncronous_get_request(
    int& response_code,
    HeaderList& response_headers,
    ResponseBody& response_body,
    std::string& response_error,

    HttpInterface& http,
    const char* http_request,
    const HttpServer& peer = HttpServer(),
    const HeaderList& headers = HeaderList())
    /*throw (eh::Exception, eh::DescriptiveException)*/;

  /**
   * Function performs synchronous post request using
   * asynchronous http interface.
   * Result of request is returned either by assigns to passed references
   * or by exception
   * @param response_code response code
   * @param response_headers response headers listed in expected_headers
   * (if exist)
   * @param response_body response body
   * @param response_error received error (if any)
   * @param http reference to http interface to use for the request
   * @param http_request request URI
   * @param body request data to post
   * @param peer http server address
   * @param headers list of additional headers for request
   */
  void
  syncronous_post_request(
    int& response_code,
    HeaderList& response_headers,
    ResponseBody& response_body,
    std::string& response_error,

    HttpInterface& http,
    const char* http_request,
    const String::SubString& body = String::SubString(),
    const HttpServer& peer = HttpServer(),
    const HeaderList& headers = HeaderList())
    /*throw (eh::Exception, eh::DescriptiveException)*/;
}

#endif
