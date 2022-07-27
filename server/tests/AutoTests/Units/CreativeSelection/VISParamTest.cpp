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
#include "VISParamTest.hpp"

REFLECT_UNIT(VISParamTest) (
  "CreativeSelection",
  AUTO_TEST_FAST);

typedef AutoTest::AdClient AdClient;
typedef AutoTest::NSLookupRequest NSLookupRequest;
typedef AutoTest::SelectedCreativesCCID SelectedCreativesCCID;

bool
VISParamTest::run_test()
{
  NOSTOP_FAIL_CONTEXT(case01_vis_param_tests());
  NOSTOP_FAIL_CONTEXT(case02_ad_selection_based_on_visibility_filter());
  NOSTOP_FAIL_CONTEXT(case03_publisher_inventory_mode());

  return true;
}

void
VISParamTest::case01_vis_param_tests()
{
  add_descr_phrase("case01");

  std::string cc = fetch_string("CC01");

  AdClient client(AdClient::create_user(this));
  NSLookupRequest request;
  request.tid = fetch_string("TAG01");
  request.referer_kw = fetch_string("KEYWORD01");
  request.loc_name = fetch_string("COUNTRY01");

  client.process_request(request);
  FAIL_CONTEXT(
    AutoTest::equal_checker(
      cc,
      client.debug_info.ccid).check(),
    "must select expected creative case01 vis is absent");

  request.vis = "-1";
  client.process_request(request);
  FAIL_CONTEXT(
    AutoTest::equal_checker(
      cc,
      client.debug_info.ccid).check(),
    "must select expected creative case01 vis = -1");

  request.vis = "0";
  client.process_request(request);
  FAIL_CONTEXT(
    AutoTest::predicate_checker(
      client.debug_info.selected_creatives.empty()),
    "must select no creative case01 vis = 0");

  request.vis = "100";
  client.process_request(request);
  FAIL_CONTEXT(
    AutoTest::equal_checker(
      cc,
      client.debug_info.ccid).check(),
    "must select expected creative case01 vis = 100");

  request.vis = "101";
  client.process_request(request);
  FAIL_CONTEXT(
    AutoTest::equal_checker(
      cc,
      client.debug_info.ccid).check(),
    "must select expected creative case01 vis = 101");

  request.vis = "01";
  client.process_request(request);
  FAIL_CONTEXT(
      AutoTest::predicate_checker(
        client.debug_info.selected_creatives.empty()),
    "must select no creative case01 vis = 01");

}

void
VISParamTest::case02_ad_selection_based_on_visibility_filter()
{
  add_descr_phrase("case02");

  std::string cc1 = fetch_string("CC02_1");
  std::string cc2 = fetch_string("CC02_2");
  std::string cc3 = fetch_string("CC02_3");

  std::string tag1 = fetch_string("TAG02_1");
  std::string tag2 = fetch_string("TAG02_2");
  std::string tag3 = fetch_string("TAG02_3");
  std::string tag4 = fetch_string("TAG02_4");
  
  std::string keyword1 = fetch_string("KEYWORD02_1");
  std::string keyword2 = fetch_string("KEYWORD02_2");
  std::string keyword3 = fetch_string("KEYWORD02_3");
  
  std::string country1 = fetch_string("COUNTRY02_1");
  std::string country2 = fetch_string("COUNTRY02_2");
  std::string country3 = fetch_string("COUNTRY02_3");

  AdClient client(AdClient::create_user(this));
  NSLookupRequest request;

  request.tid = tag1;
  request.referer_kw = keyword1;
  request.loc_name = country1;
  request.vis = "0";
  client.process_request(request);
  FAIL_CONTEXT(
    AutoTest::equal_checker(
      cc1,
      client.debug_info.ccid).check(),
    "must select expected creative case02 vis = 0");

  request.tid = tag2;
  request.referer_kw = keyword2;
  request.loc_name = country2;

  request.vis = "40";
  client.process_request(request);
  FAIL_CONTEXT(
    AutoTest::predicate_checker(
      client.debug_info.selected_creatives.empty()),
    "must select no creative case02 vis = 40");

  request.vis = "60";
  client.process_request(request);
  FAIL_CONTEXT(
    AutoTest::equal_checker(
      cc2,
      client.debug_info.ccid).check(),
    "must select expected creative case02 vis = 60");

  request.tid = tag4;
  request.referer_kw = keyword3;
  request.loc_name = country3;
  request.vis = "100";
  client.process_request(request);
  FAIL_CONTEXT(
    AutoTest::equal_checker(
      cc3,
      client.debug_info.ccid).check(),
    "must select expected creative case02 vis = 100");

  request.tid = tag3;
  request.referer_kw = keyword2;
  request.loc_name = country2;

  request.vis = "49";
  client.process_request(request);
  FAIL_CONTEXT(
    AutoTest::equal_checker(
      cc2,
      client.debug_info.ccid).check(),
    "must select expected creative case02 vis = 49");
  request.vis = "50";
  client.process_request(request);
  FAIL_CONTEXT(
    AutoTest::equal_checker(
      cc2,
      client.debug_info.ccid).check(),
    "must select expected creative case02 vis = 50");

}

void
VISParamTest::case03_publisher_inventory_mode()
{
  add_descr_phrase("case03");

  std::string cc = fetch_string("CC03");
  std::string keyword = fetch_string("KEYWORD03");  
  std::string country = fetch_string("COUNTRY03");

  std::string tag1 = fetch_string("TAG03_1");
  std::string tag2 = fetch_string("TAG03_2");

  AdClient client(AdClient::create_user(this));
  NSLookupRequest request;

  request.tid = tag1;
  request.referer_kw = keyword;
  request.loc_name = country;
  request.tag_inv = "1";

  request.vis = "0";
  client.process_request(request);
  FAIL_CONTEXT(
    AutoTest::predicate_checker(
      client.debug_info.selected_creatives.empty()),
    "must select expected creative case03 vis = 0");

  request.vis = "50";
  client.process_request(request);
  FAIL_CONTEXT(
    AutoTest::equal_checker(
      cc,
      client.debug_info.ccid).check(),
    "must select expected creative case03 vis = 50");

  request.vis = "100";
  client.process_request(request);
  FAIL_CONTEXT(
    AutoTest::equal_checker(
      cc,
      client.debug_info.ccid).check(),
    "must select expected creative case03 vis = 100");

  request.tid = tag2;
  request.vis = "0";
  client.process_request(request);
  FAIL_CONTEXT(
    AutoTest::equal_checker(
      cc,
      client.debug_info.ccid).check(),
    "must select expected creative case03 vis = 0 ");

}

