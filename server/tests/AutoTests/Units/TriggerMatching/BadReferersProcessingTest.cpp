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
#include "BadReferersProcessingTest.hpp"

REFLECT_UNIT(BadReferersProcessingTest) (
  "TriggerMatching",
  AUTO_TEST_FAST
);

bool 
BadReferersProcessingTest::run_test()
{
  add_descr_phrase("Starting https://jira.corp.foros.com/browse/ADSC-359");

  add_descr_phrase("Initializing xml data");

  const std::string tid  = fetch_string("Tags/Default");
  const std::string p_ch = fetch_string("Channel/P/01");
  const std::string u_ch = fetch_string("Channel/U/01");

  const std::string first[] = {
    p_ch
  };
  const std::string both[] = {
    p_ch, 
    u_ch
  };

  AutoTest::AdClient client(AutoTest::AdClient::create_user(this));
  AutoTest::NSLookupRequest request;
  request.tid(tid).referer_kw("P_01");

  add_descr_phrase("Sending request with right referer and right referer-kw");
  request.referer("http://U01");
  client.process_request(request);

  FAIL_CONTEXT(
    AutoTest::sequence_checker(
      both,
      client.debug_info.trigger_channels,
      AutoTest::SCE_ENTRY).check(),
    "both channels");
  
#if 0 // The following tests do not pass in permissive mode.
  add_descr_phrase("Sending request with wrong referer (invalid port) and"
                   " right referer-kw");
  request.referer("http://U01:4x8z");
  client.process_request(request);

  FAIL_CONTEXT(
    AutoTest::sequence_checker(
      first,
      client.debug_info.trigger_channels,
      AutoTest::SCE_ENTRY).check(),
    "first channel");

  add_descr_phrase("Sending request with wrong referer (too big port num) and"
                   " right referer-kw");
  request.referer("http://U01:65536");
  client.process_request(request);

  FAIL_CONTEXT(
    AutoTest::sequence_checker(
      first,
      client.debug_info.trigger_channels,
      AutoTest::SCE_ENTRY).check(),
    "first channel");
#endif

  add_descr_phrase("Sending request with wrong referer (one slash is missed)"
                   " and right referer-kw");
  request.referer("http:/U01:80");
  client.process_request(request);
  
  FAIL_CONTEXT(
    AutoTest::sequence_checker(
      first,
      client.debug_info.trigger_channels,
      AutoTest::SCE_ENTRY).check(),
    "first channel");

  add_descr_phrase("Sending request with wrong referer (colon is missing)"
                   " and right referer-kw");
  request.referer("http//U01:80");
  client.process_request(request);

  FAIL_CONTEXT(
    AutoTest::sequence_checker(
      first,
      client.debug_info.trigger_channels,
      AutoTest::SCE_ENTRY).check(),
    "first channel");

  add_descr_phrase("Sending request with wrong referer (one letter is missing"
                   " (htp)) and right referer-kw");
  request.referer("htp://U01:80");
  client.process_request(request);

  FAIL_CONTEXT(
    AutoTest::sequence_checker(
      first,
      client.debug_info.trigger_channels,
      AutoTest::SCE_ENTRY).check(),
    "first channel");

  return true;
}
 
