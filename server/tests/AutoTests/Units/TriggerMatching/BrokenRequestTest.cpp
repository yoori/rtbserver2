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

#include "BrokenRequestTest.hpp"
 
REFLECT_UNIT(BrokenRequestTest) (
  "TriggerMatching",
  AUTO_TEST_FAST
);

namespace
{
  typedef AutoTest::ChannelsCheck ChannelsCheck;
}

void
BrokenRequestTest::test_case(
  const std::string& description,
  AdClient& client,
  const NSLookupRequest& request,
  const char* expected,
  const char* unexpected)
{
  add_descr_phrase(description);

  client.process_request(request);

  FAIL_CONTEXT(
    ChannelsCheck(
      this,
      expected,
      client.debug_info.trigger_channels).check(),
    description +
        ". Expected trigger_channels check");

  if (unexpected)
  {
    FAIL_CONTEXT(
      ChannelsCheck(
        this,
        unexpected,
        client.debug_info.trigger_channels,
        AutoTest::SCE_NOT_ENTRY).check(),
      description +
        ". Expected trigger_channels check");
  }
}
 
bool 
BrokenRequestTest::run_test()
{
  AdClient client(AdClient::create_user(this));

  NOSTOP_FAIL_CONTEXT(
    test_case(
      "Broken referrer keywords",
      client,
      NSLookupRequest().
        referer_kw(fetch_string("KWD1")).
        referer(fetch_string("REF1")),
      "Channel1,Channel2"));
  
  NOSTOP_FAIL_CONTEXT(
    test_case(
      "Broken referrer",
      client,
      NSLookupRequest().
        referer_kw(fetch_string("KWD2")).
        referer(fetch_string("REF2")),
      "Channel1",
      "Channel2"));

  NOSTOP_FAIL_CONTEXT(
    test_case(
      "Broken referrer and referrer keywords",
      client,
      NSLookupRequest().
        referer_kw(fetch_string("KWD1")).
        referer(fetch_string("REF2")),
      "Channel1",
      "Channel2"));

  NOSTOP_FAIL_CONTEXT(
    test_case(
      "Broken encoding in referrer",
      client,
      NSLookupRequest().
        search(fetch_string("SEARCH3")),
      "Channel3_1,Channel3_2"));

  return true;
}

