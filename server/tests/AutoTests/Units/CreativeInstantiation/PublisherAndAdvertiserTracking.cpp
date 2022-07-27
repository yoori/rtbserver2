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

#include "PublisherAndAdvertiserTracking.hpp"

REFLECT_UNIT(PublisherAndAdvertiserTracking) (
  "CreativeInstantiation",
  AUTO_TEST_FAST);

namespace {
  typedef AutoTest::AdClient AdClient;

  const char* TRACKPIXEL_URL = "TRACKPIXEL_URL";
  const char* DUMMY_URL = "DUMMY_URL";

  const PublisherAndAdvertiserTracking::TestRequest TestCases[] =
  {
    // 1
    {
      "unit-test",
      "TAG",
      0,
      "0",
      "CCNOIMP",
      0,
      "http://img.yandex.net/i/no_imp.gif?r=1",
      "http://img.yandex.net/i/1.gif?r=1"
    },
    // 2
    {
      "unit-test",
      "TAG",
      0,
      "1",
      "CCNOIMP",
      0,
      DUMMY_URL,
      DUMMY_URL
    },
    // 3
    {
      "unit-test",
      "TAG",
      0,
      "2",
      "CCNOIMP",
      0,
      DUMMY_URL,
      DUMMY_URL
    },
    // 4
    {
      "unit-test-imp",
      "TAG",
      0,
      "0",
      "CCIMP",
      TRACKPIXEL_URL,
      "http://img.yandex.net/i/imp.gif?r=4",
      "http://img.yandex.net/i/1.gif?r=4"
    },
    // 5
    {
      "unit-test-imp",
      "TAG",
      0,
      "1",
      "CCIMP",
      TRACKPIXEL_URL,
      DUMMY_URL,
      DUMMY_URL
    },
    // 6
    {
      "unit-test-imp",
      "TAG",
      0,
      "2",
      "CCIMP",
      TRACKPIXEL_URL,
      DUMMY_URL,
      DUMMY_URL
    },
    // 7
    {
      "unit-test-imp",
      "TAGTEST",
      0,
      "0",
      "CCIMP",
      TRACKPIXEL_URL,
      "http://img.yandex.net/i/imp.gif?r=7",
      "http://img.yandex.net/i/1.gif?r=7"
    },
    // 8
    {
      "unit-test-imp",
      "TAG",
      "COLOTEST",
      "0",
      "CCIMP",
      TRACKPIXEL_URL,
      "http://img.yandex.net/i/imp.gif?r=8",
      "http://img.yandex.net/i/1.gif?r=8"
    },
  };

}

bool
PublisherAndAdvertiserTracking::run_test()
{

  AdClient client(AdClient::create_user(this));

  for (size_t i = 0; i < countof(TestCases); ++i)
  {
    NSLookupRequest request;
    set_request_param(request.tid, TestCases[i].tid);
    set_request_param(request.colo, TestCases[i].colo);
    request.testrequest = TestCases[i].testrequest;
    request.format = TestCases[i].format;
    request.referer_kw = fetch_string("KEYWORD");
    request.random = i+1;

    client.process_request(request);
    FAIL_CONTEXT(
      AutoTest::equal_checker(
        fetch_string(TestCases[i].ccid),
        client.debug_info.ccid).check(),
      "ccid check#" + strof(i+1));

    // Test creative
    std::ostringstream exp_body;

    prepare_expected_body(
      exp_body,
      client.debug_info.track_pixel_url,
      TestCases[i]);
    
    FAIL_CONTEXT(
      AutoTest::equal_checker(
        exp_body.str(),
        client.req_response_data()).check(),
      "creative check#" + strof(i+1));
  }
  
  return true;
}


void
PublisherAndAdvertiserTracking::set_request_param(
  NSLookupParam& request_param,
  const char* param_name)
{
  if (param_name)
  {
    request_param = fetch_string(param_name);
  }
  else
  {
    request_param.clear();
  }
}

void
PublisherAndAdvertiserTracking::prepare_expected_body(
  std::ostringstream& body,
  const std::string& impression_url,
  const TestRequest& test)
{
  std::string frontend =
    get_config().check_service(CTE_ALL_REMOTE, STE_FRONTEND)?
      get_config().get_service(CTE_ALL_REMOTE, STE_FRONTEND).address:
        get_config().get_service(CTE_ALL, STE_FRONTEND).address;

  typedef const char* TestRequest::* UrlMember;
  const UrlMember urls[] =
  {
    &TestRequest::track_pixel,
    &TestRequest::cradvtrackpixel,
    &TestRequest::publ_tag_track_pixel
  };


  for (size_t i = 0; i < countof(urls); ++i)
  {
    if ( test.*(urls[i]) )
    {
      if (strcmp(test.*(urls[i]), TRACKPIXEL_URL) == 0)
      {
        FAIL_CONTEXT(
          AutoTest::predicate_checker(
            strcmp(test.track_pixel, TRACKPIXEL_URL) != 0 || !impression_url.empty()),
          "impression check");
        body << impression_url;
      }
      else if (strcmp(test.*(urls[i]), DUMMY_URL) == 0)
      {
        body << frontend << "/track.gif";
      }
      else
      {
        body << test.*(urls[i]);
      }
    }
    body << std::endl;
  }
}
