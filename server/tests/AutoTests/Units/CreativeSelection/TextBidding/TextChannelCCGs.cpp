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

#include "TextChannelCCGs.hpp"

REFLECT_UNIT(TextChannelCCGs) (
  "CreativeSelection",
  AUTO_TEST_FAST);

namespace
{
  typedef AutoTest::NSLookupRequest NSLookupRequest;
  typedef AutoTest::AdClient AdClient;
  typedef AutoTest::SelectedCreativesCCID SelectedCreativesCCID;
  typedef AutoTest::SelectedCreativesActualCPC SelectedCreativesActualCPC;
  typedef AutoTest::SelectedCreativesImpRevenue SelectedCreativesImpRevenue;
  typedef AutoTest::DebugInfo::SelectedCreativesList SelectedCreativesList;
  typedef AutoTest::precisely_number precisely_number;
}


bool
TextChannelCCGs::run_test()
{
  NOSTOP_FAIL_CONTEXT(scenario1());
  NOSTOP_FAIL_CONTEXT(scenario2());
  NOSTOP_FAIL_CONTEXT(scenario3());
  NOSTOP_FAIL_CONTEXT(scenario4());
  NOSTOP_FAIL_CONTEXT(scenario5());
  return true;
}

void TextChannelCCGs::scenario1()
{
  add_descr_phrase("One text creative served.");
  AdClient client(AdClient::create_user(this));

  NSLookupRequest request;
  request.tid         = fetch_string("TAGSIMPLE");
  request.referer_kw = fetch_string("CHANNELKEYWORD1");
  client.process_request(request);

  std::string exp_ccids[] = {
    fetch_string("CHANNELCC1")
  };

  precisely_number exp_imp_revenues[] = {
      precisely_number(fetch_float("IMPREV1_1"), 0.001),
  };
  
  FAIL_CONTEXT(
    AutoTest::sequence_checker(
      exp_ccids,
      SelectedCreativesCCID(client)).check(),
    "ccids check");

  FAIL_CONTEXT(
    AutoTest::sequence_checker(
      exp_imp_revenues,
      SelectedCreativesImpRevenue(client)).check(),
    "imp revenue check");
}

void TextChannelCCGs::scenario2()
{
  add_descr_phrase("Channel targeted CCG on "
                   "tag with CPM=0 and margin=0.");

  AdClient client(AdClient::create_user(this));

  NSLookupRequest request;
  request.tid         = fetch_string("TAGNOMARGIN");
  request.colo        = fetch_string("COLONOMARGIN");
  request.referer_kw = fetch_string("CHANNELKEYWORD1");
  
  client.process_request(request);

  std::string exp_ccids[] = {
    fetch_string("CHANNELCC1")
  };

  precisely_number exp_imp_revenues[] = {
    precisely_number(fetch_float("IMPREV1_1"), 0.001),
  };
  
  FAIL_CONTEXT(
    AutoTest::sequence_checker(
      exp_ccids,
      SelectedCreativesCCID(client)).check(),
    "ccids check");

  FAIL_CONTEXT(
    AutoTest::sequence_checker(
      exp_imp_revenues,
      SelectedCreativesImpRevenue(client)).check(),
    "imp revenue check");
}

void TextChannelCCGs::scenario3()
{
  add_descr_phrase("Three text creatives "
                   "served (four available).");

  AdClient client(AdClient::create_user(this));

  NSLookupRequest request;
  request.tid         = fetch_string("TAGSIMPLE");
  request.referer_kw =
    fetch_string("CHANNELKEYWORD1")  + "," +
    fetch_string("CHANNELKEYWORD2")  + "," +
    fetch_string("CHANNELKEYWORD3")  + "," +
    fetch_string("CHANNELKEYWORD4");
  client.process_request(request);

  std::string exp_ccids[] = {
    fetch_string("CHANNELCC1"),
    fetch_string("CHANNELCC2"),
    fetch_string("CHANNELCC3")
  };

  precisely_number exp_imp_revenues[] = {
    precisely_number(fetch_float("IMPREV3_1"), 0.001),
    precisely_number(fetch_float("IMPREV3_2"), 0.001),
    precisely_number(fetch_float("IMPREV3_3"), 0.001)
  };
  
  FAIL_CONTEXT(
    AutoTest::sequence_checker(
      exp_ccids,
      SelectedCreativesCCID(client)).check(),
    "ccids check");

  FAIL_CONTEXT(
    AutoTest::sequence_checker(
      exp_imp_revenues,
      SelectedCreativesImpRevenue(client)).check(),
    "imp revenue check");
}

void TextChannelCCGs::scenario4()
{
  add_descr_phrase("Three text creatives "
                   "served (three available).");


  AdClient client(AdClient::create_user(this));

  NSLookupRequest request;
  request.tid         = fetch_string("TAGSIMPLE");
  request.referer_kw =
    fetch_string("CHANNELKEYWORD1")  + "," +
    fetch_string("CHANNELKEYWORD2")  + "," +
    fetch_string("CHANNELKEYWORD4");
  client.process_request(request);

  std::string exp_ccids[] = {
    fetch_string("CHANNELCC1"),
    fetch_string("CHANNELCC2"),
    fetch_string("CHANNELCC4")
  };

  precisely_number exp_imp_revenues[] = {
    precisely_number(fetch_float("IMPREV3_1"), 0.001),
    precisely_number(fetch_float("IMPREV3_2"), 0.001),
    precisely_number(fetch_float("IMPREV3_4"), 0.001)
  };
  
  FAIL_CONTEXT(
    AutoTest::sequence_checker(
      exp_ccids,
      SelectedCreativesCCID(client)).check(),
    "ccids check");

  FAIL_CONTEXT(
    AutoTest::sequence_checker(
      exp_imp_revenues,
      SelectedCreativesImpRevenue(client)).check(),
    "imp revenue check");
}

void TextChannelCCGs::scenario5()
{
  add_descr_phrase("Keyword and Channel Text CCGs "
                   "from the same account.");

  AdClient client(AdClient::create_user(this));

  NSLookupRequest request;
  request.tid         = fetch_string("TAGSIMPLE");
  request.referer_kw =
    fetch_string("CHANNELKEYWORD5")  + "," +
    fetch_string("CHANNELKEYWORD6")  + "," +
    fetch_string("KWDKEYWORD1")  + "," +
    fetch_string("KWDKEYWORD2");
  client.process_request(request);
  client.repeat_request();

  std::string exp_ccids[] = {
    fetch_string("KWDCC2"),
    fetch_string("CHANNELCC5")
  };

  precisely_number exp_imp_revenues[] = {
    precisely_number(fetch_float("IMPREV5_1"), 0.001),
    precisely_number(fetch_float("IMPREV5_2"), 0.00001),
  };

  precisely_number exp_click_revenues[] = {
    precisely_number(fetch_float("CLICKREV5_1"), 0.001),
    precisely_number(fetch_float("CLICKREV5_2"), 0.001),
  };

  FAIL_CONTEXT(
    AutoTest::sequence_checker(
      exp_ccids,
      SelectedCreativesCCID(client)).check(),
    "ccids check");

  FAIL_CONTEXT(
    AutoTest::sequence_checker(
      exp_imp_revenues,
      SelectedCreativesImpRevenue(client)).check(),
    "imp revenue check");

  FAIL_CONTEXT(
    AutoTest::sequence_checker(
      exp_click_revenues,
      SelectedCreativesActualCPC(client)).check(),
    "click revenue check");

}

