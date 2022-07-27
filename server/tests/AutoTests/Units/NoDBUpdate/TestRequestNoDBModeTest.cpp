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

#include "TestRequestNoDBModeTest.hpp"

REFLECT_UNIT(TestRequestNoDBModeTest) (
  "NoDBUpdate",
  AUTO_TEST_SLOW
);

namespace
{
  typedef AutoTest::AdClient AdClient;
  typedef AutoTest::NSLookupRequest NSLookupRequest;
  typedef AutoTest::CampaignChecker CampaignChecker;
  typedef AutoTest::SelectedCreativeChecker SelectedCreativeChecker;
};

const TestRequestNoDBModeTest::TestCase
  TestRequestNoDBModeTest::CASES[] = {
    { "Creative group budget", "CCGBudget" },
    { "Campaign budget",  "CampaignBudget" },
    { "Account budget", "AccountBudget" },
  };

void
TestRequestNoDBModeTest::process_case(
  const TestRequestNoDBModeTest::TestCase& testcase)
{
  add_descr_phrase("Start '" + testcase.description + "' case.");

  unsigned long ccg = fetch_int(testcase.prefix + "/CCGID");
  unsigned long cc = fetch_int(testcase.prefix + "/CCID");

  unsigned long test_ccg = fetch_int(testcase.prefix + "/TEST_CCGID");
  unsigned long test_cc = fetch_int(testcase.prefix + "/TEST_CCID");

  std::string keyword = fetch_string(testcase.prefix + "/KEYWORD");

  unsigned long tag = fetch_int("TID");
  unsigned long test_tag = fetch_int("TEST_TID");

  add_descr_phrase("Check initial state");
  FAIL_CONTEXT(
    AutoTest::and_checker(
      CampaignChecker(this, ccg,
        CampaignChecker::Expected().eval_status("A").status("A")),
      CampaignChecker(this, test_ccg,
        CampaignChecker::Expected().eval_status("A").status("A"))).check(),
    testcase.description + " - initial state check");

  add_descr_phrase("Send requests to server");

  Generics::Time today = Generics::Time::get_time_of_day();

  NSLookupRequest request;
  request.referer_kw = keyword;
  request.debug_time = today;

  {
    AdClient client = AdClient::create_user(this);

    FAIL_CONTEXT(
      SelectedCreativeChecker(
        client,
        request.tid(test_tag).testrequest(1),
        test_cc).check(),
      "check serer returns test creative");

    FAIL_CONTEXT(
      SelectedCreativeChecker(
        client,
        request.tid(tag).testrequest(0),
        cc).check(),
      "check serer returns real creative");
  }

  add_descr_phrase("Check changed state");

  add_checker(testcase.description + " - check changed statuses",
    AutoTest::wait_checker(
      AutoTest::and_checker(
        CampaignChecker(this, ccg,
          CampaignChecker::Expected().eval_status("I")),
        CampaignChecker(this, test_ccg,
          CampaignChecker::Expected().eval_status("A").status("A")))));

  {
    AdClient client = AdClient::create_user(this);
    add_checker(testcase.description + " - check creative appearance",
      AutoTest::and_checker(
        SelectedCreativeChecker(
          client,
          request.tid(test_tag).testrequest(1),
          test_cc),
        SelectedCreativeChecker(
          client,
          request.tid(fetch_int("TID")).testrequest(0),
          "0")));
  }
}

bool 
TestRequestNoDBModeTest::run()
{
  for(size_t i = 0; i < countof(CASES); ++i)
  {
    AUTOTEST_CASE(process_case(CASES[i]), CASES[i].description);
  }
  return true;
}

void
TestRequestNoDBModeTest::tear_down()
{}
