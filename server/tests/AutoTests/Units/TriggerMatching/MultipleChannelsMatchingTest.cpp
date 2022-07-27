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
#include "MultipleChannelsMatchingTest.hpp"
#include <String/InterConvertion.hpp>

REFLECT_UNIT(MultipleChannelsMatchingTest) (
  "TriggerMatching",
  AUTO_TEST_FAST
);

typedef AutoTest::NSLookupRequest  NSLookupRequest;
typedef AutoTest::AdClient AdClient;

#define TEST_APPEARENCES2(channel1, channel2, list, message) \
  FAIL_CONTEXT(                                              \
    AutoTest::entry_checker(                                 \
      channel1,                                              \
      list).check(),                                         \
    "must have first  channel for " #message);               \
  FAIL_CONTEXT(                                              \
    AutoTest::entry_checker(                                 \
      channel2,                                              \
      list).check(),                                         \
    "must have second channel for " #message);

 
bool 
MultipleChannelsMatchingTest::run_test()
{
  std::string required_channel1 = fetch_string("MultipleChannelsMatchingTest/01");
  std::string required_channel2 = fetch_string("MultipleChannelsMatchingTest/02");
  std::string required_channel3 = fetch_string("MultipleChannelsMatchingTest/03");
  std::string required_channel4 = fetch_string("MultipleChannelsMatchingTest/04");
  std::string required_channel5 = fetch_string("MultipleChannelsMatchingTest/05");
  std::string required_channel8 = fetch_string("MultipleChannelsMatchingTest/08");
  std::string required_channel9 = fetch_string("MultipleChannelsMatchingTest/09");

  NSLookupRequest request;
  request.tid = tid;

  //Request for probe uid
  AdClient client(AdClient::create_user(this));
  
  /////
  client.process_request(request.referer_kw("Test11 Test10"));
  TEST_APPEARENCES2(required_channel1, required_channel2, 
                    (client.debug_info.trigger_channels
                     + client.debug_info.trigger_channels),
                    "first part 1");

  client.process_request(request.referer_kw("Test10 Test45 Test11"));
  TEST_APPEARENCES2(required_channel1, required_channel2, 
                    (client.debug_info.trigger_channels
                     + client.debug_info.trigger_channels),
                    "first part 2");

  client.process_request(request.referer_kw("Test12").referer("Test12"));
  TEST_APPEARENCES2(required_channel3, required_channel4, 
                    (client.debug_info.trigger_channels
                     + client.debug_info.trigger_channels),
                    "second part");
  
  client.process_request(request.referer_kw("Test13"));

  FAIL_CONTEXT(
    AutoTest::entry_checker(
      required_channel5,
      client.debug_info.trigger_channels +
        client.debug_info.trigger_channels).check(),
    "forth part");
  
  std::string required_channels[] = {
    required_channel8,
    required_channel9
  };
  client.process_request(request.referer_kw("Test14"));

  FAIL_CONTEXT(
    AutoTest::sequence_checker(
      required_channels,
      client.debug_info.trigger_channels,
      AutoTest::SCE_ENTRY).check(),
    "fifth part");
  
  return true;
}
 
