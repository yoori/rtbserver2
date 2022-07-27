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
#include "UidWithPlusTest.hpp"

REFLECT_UNIT(UidWithPlusTest) (
  "Frontend",
  AUTO_TEST_FAST
);

typedef AutoTest::NSLookupRequest  NSLookupRequest;
typedef AutoTest::AdClient AdClient;

bool 
UidWithPlusTest::run_test()
{  
  add_descr_phrase("Starting <No ADSC, see description>");
  
  add_descr_phrase("Initializing common XML data");
  
  const unsigned long iters_count = fetch_int("RequestsCount");

  NSLookupRequest request;
  request.referer_kw(fetch_string("KEYWORD"));
  request.colo(fetch_string("UidWithPlusTest/Colo"));
  request.tid(fetch_string("Tag Id/01"));
  request.format("unit-test-imp");

  add_descr_phrase("Sending requests");
  
  unsigned long count = iters_count;
    
  bool next = true;
  while (next && count != 0)
  {
    AdClient client(AdClient::create_user(this));
  
    client.process_request(request);

    std::string uid1;
    if (!client.get_cookies().find_value("uid", uid1))
    { 
      Stream::Error error;
      error << "Server didn't return uid on request: "
            << request.url ();
      throw Exception(error);
    }
    if (uid1.find('_') != std::string::npos)
    {
      next = false;
    }

    AutoTest::DebugInfo::DebugInfo debug_info = client.debug_info;
    FAIL_CONTEXT(
      AutoTest::predicate_checker(
        !debug_info.track_pixel_url.empty()),
      "must has track_pixel_url");
    FAIL_CONTEXT(
      AutoTest::predicate_checker(
        !debug_info.click_url.empty()),
      "must has click_url");
    FAIL_CONTEXT(
      AutoTest::predicate_checker(
        !debug_info.selected_creatives.empty()),
      "must has selected creatives");
    FAIL_CONTEXT(
      AutoTest::predicate_checker(
        !debug_info.selected_creatives.first().action_adv_url.empty()),
      "must has action_adv_url");

    client.process_request(debug_info.track_pixel_url);
    client.process_request(debug_info.click_url);
    client.process_request(debug_info.selected_creatives.first().action_adv_url);
      
    --count;
  }
  
  return true;
}

