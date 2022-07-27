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
#include "CountryTargeting.hpp"

REFLECT_UNIT(CountryTargeting) (
  "CreativeSelection",
  AUTO_TEST_FAST);

namespace
{
  typedef AutoTest::AdClient AdClient;
  typedef AutoTest::NSLookupRequest NSLookupRequest;
  typedef AutoTest::SelectedCreativesCCID SelectedCreativesCCID;

  struct TestCase
  {
    std::string description;
    const char* tid;
    const char* referer_kws;
    const char* loc_name;
    const char* exp_ccs;
    bool tag_inv;
  };

  const TestCase TEST_CASES[] =
  {
    {
      "Advertiser country = Publisher country = Request country.",
      "TAG-LU",
      "KEYWORD-DC-LU",
      "lu",
      "DC-LU",
      false
    },
    {
      "Advertiser != Publisher (Advertiser = Request).",
      "TAG-UG",
      "KEYWORD-DC-LU",
      "lu",
      0,
      false
    },
    {
      "Advertiser = Publisher != Request "
      "(Agency with Financial fields on Advertiser level).",
      "TAG-UG",
      "KEYWORD-DC-LU,KEYWORD-DC-UG1",
      "lu",
      "DC-UG1",
      false
    },
    {
      "Advertiser = Publisher != Request "
      "(Agency with Financial fields on Agency level).",
      "TAG-UG",
      "KEYWORD-DC-UG2",
      "lu",
      "DC-UG2",
      false
    },
    {
      "Text ads from account with different countries#1.",
      "TAG-LU",
      "KEYWORD-TC-LU,KEYWORD-TC-UG1,KEYWORD-TC-UG2",
      "lu",
      "TC-LU",
      false
    },
    {
      "Text ads from account with different countries#2.",
      "TAG-UG",
      "KEYWORD-TC-LU,KEYWORD-TC-UG1,KEYWORD-TC-UG2",
      "lu",
      "TC-UG2,TC-UG1",
      false
    },
    {
      "Account countries in inventory mode.",
      "TAG-UG2",
      "KEYWORD-DC-LU,KEYWORD-DC-UG1",
      "lu",
      "DC-UG1",
      true
    }
  };
  
}

bool
CountryTargeting::run_test()
{

  for (size_t i = 0; i < countof(TEST_CASES); ++i)
  {
    add_descr_phrase(TEST_CASES[i].description);
    AdClient client(AdClient::create_user(this));
    NSLookupRequest request;

    request.tid = fetch_string(TEST_CASES[i].tid);
    request.loc_name = TEST_CASES[i].loc_name;
    request.referer_kw =
      map_objects(TEST_CASES[i].referer_kws);
    if (TEST_CASES[i].tag_inv)
    {
      request.tag_inv = "1";
    }
    client.process_request(request);

    if (TEST_CASES[i].exp_ccs)
    {
      std::list<std::string> expected_ccs;
      fetch_objects(
        std::inserter(expected_ccs, expected_ccs.begin()),
        TEST_CASES[i].exp_ccs);
    
      FAIL_CONTEXT(
        AutoTest::sequence_checker(
          expected_ccs,
          SelectedCreativesCCID(client)).check(),
        TEST_CASES[i].description +
        " Check CCs");
    }
    else
    {
      FAIL_CONTEXT(
        AutoTest::predicate_checker(
          client.debug_info.selected_creatives.empty()),
        TEST_CASES[i].description +
        " Check CCs");
    }
  }
  
  return true;
}

