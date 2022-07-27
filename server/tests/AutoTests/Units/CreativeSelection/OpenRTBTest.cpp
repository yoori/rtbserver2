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

#include "OpenRTBTest.hpp"

REFLECT_UNIT(OpenRTBTest) (
  "CreativeSelection",
  AUTO_TEST_FAST | AUTO_TEST_SLOW );

namespace
{
  typedef AutoTest::AdClient AdClient;
  typedef AutoTest::NSLookupRequest NSLookupRequest;
  typedef AutoTest::OpenRTBRequest OpenRTBRequest;
  typedef AutoTest::UserBindRequest UserBindRequest;
  typedef AutoTest::OpenRTBCid OpenRTBCid;
  typedef AutoTest::OpenRTBResponseChecker OpenRTBResponseChecker;
}

bool
OpenRTBTest::run()
{
  AUTOTEST_CASE(
    simple_case(),
    "Simple case");
  
  AUTOTEST_CASE(
    auctions_lost(),
    "Auctions lost");
 
  return true;
}

void OpenRTBTest::simple_case()
{
  AdClient client(AdClient::create_user(this));

  client.process_request(
    NSLookupRequest().
      referer_kw(fetch_string("SIMPLE/KWD")));

  client.process_request(
    UserBindRequest().
      ssp_user_id(client.get_uid()));
  
  client.process_post(
    OpenRTBRequest().
      aid(fetch_int("OPENRTB/ACCOUNT")).
      debug_ccg(fetch_int("SIMPLE/CCG")).
      debug_size(fetch_string("SIZE")).
      external_user_id(client.get_uid()).
      min_cpm_price(0).
      min_cpm_price_currency_code(
        fetch_string("CURRENCY")));

  FAIL_CONTEXT(
    OpenRTBResponseChecker(
      client,
      OpenRTBResponseChecker::Expected().
        adomain("www.autotest.com").
        price(fetch_float("SIMPLE/CPM") * fetch_float("RATE")).
        cid(fetch_int("SIMPLE/CAMPAIGN")).
        adid(fetch_int("SIMPLE/CREATIVE"))).check(),
    "OpenRTB bid check");
}

// ADSC-8023
void OpenRTBTest::auctions_lost()
{

  AutoTest::ORM::StatsList<CcgStats> stats;
  std::list<CcgStatsDiff> diffs;
  
  if (stat_.db_active())
  {
    const CCGStatsExpected EXPECTED[] = 
    {
      {"AUCTIONSLOST/CCG1", 1},
      {"AUCTIONSLOST/CCG2", 1}
    };

    for (size_t i = 0; i < countof(EXPECTED); ++i)
    {
      CcgStats stat;
      stat.key().
        ccg_id(fetch_int(EXPECTED[i].ccg));
      stat.description("#" + strof(i+1));
      stats.push_back(stat);
      diffs.push_back(
        CcgStatsDiff().
          auctions_lost(EXPECTED[i].auctions_lost));
    }

    stats.select(pq_conn_);
  }

  AdClient client(AdClient::create_user(this));

  client.process_request(
    NSLookupRequest().
      referer_kw(fetch_string("AUCTIONSLOST/KWD")));

  client.process_request(
    UserBindRequest().
      ssp_user_id(client.get_uid()));

  client.process_post(
    OpenRTBRequest().
      aid(fetch_int("OPENRTB/ACCOUNT")).
      debug_ccg(fetch_int("AUCTIONSLOST/CCG2")).
      debug_size(fetch_string("SIZE")).
      external_user_id(client.get_uid()).
      min_cpm_price(200).
      min_cpm_price_currency_code(
        fetch_string("CURRENCY")));

  FAIL_CONTEXT(
    AutoTest::equal_checker(
      204,
      client.req_status()).check(),
    "No content check");

  ADD_WAIT_CHECKER(
    "CcgStatsDaily check",
    AutoTest::stats_diff_checker(
      pq_conn_, diffs, stats));
}

void
OpenRTBTest::tear_down()
{ }
