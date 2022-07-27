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

#include "BannedChAdReqProfDisabling.hpp"
 
REFLECT_UNIT(BannedChAdReqProfDisabling) (
  "TriggerMatching",
  AUTO_TEST_FAST
);

namespace {
  typedef AutoTest::AdClient AdClient;
  typedef AutoTest::NSLookupRequest NSLookupRequest;
  typedef AutoTest::BaseProfileChecker BaseProfileChecker;
  typedef AutoTest::SpecialEffectsChecker SpecialEffectsChecker;
}
 
bool 
BannedChAdReqProfDisabling::run_test()
{
  
  FAIL_CONTEXT(
    AutoTest::predicate_checker(
      get_config().check_service(CTE_ALL, STE_USER_INFO_MANAGER_CONTROLLER, 1)),
    "UserInfoManagerController with special "
    "configuration need for this test");
  
  FAIL_CONTEXT(
    AutoTest::predicate_checker(
      get_config().check_service(CTE_ALL, STE_FRONTEND, 1)),
    "AdFrontend with special "
    "configuration need for this test");

  FAIL_CONTEXT(
    AutoTest::predicate_checker(
      get_config().get_service(CTE_ALL, STE_FRONTEND, 1).remote),
    "AdFrontend with special "
    "configuration need for this test");
  
  AdClient client(
    AdClient::create_user(
      this, AutoTest::UF_FRONTEND_MINOR));
  
  std::string no_track_words      = fetch_string ("no_track_words");
  std::string no_track_urls       = fetch_string ("no_track_urls");
  std::string no_adv_words        = fetch_string ("no_adv_words");
  std::string no_adv_urls         = fetch_string ("no_adv_urls");
  
  NSLookupRequest request;

  add_descr_phrase("tid request & NO ADV");
  
  request.referer = no_adv_urls + "/advertising.html";
  request.tid = fetch_string("Tag");

  FAIL_CONTEXT(
    SpecialEffectsChecker(
      client, request,
      "0",
      SpecialEffectsChecker::SE_NO_ADV |
        SpecialEffectsChecker::SE_TRACK).check(),
    "NO ADV & TRACK");

  add_descr_phrase("tid request & NO TRACK");
  request.referer = no_track_urls + "/ads";
  request.tid = fetch_string("Tag");

  FAIL_CONTEXT(
    SpecialEffectsChecker(
      client, request,
      "0",
      SpecialEffectsChecker::SE_ADV |
        SpecialEffectsChecker::SE_NO_TRACK).check(),
    "ADV & NO TRACK");

  add_descr_phrase("no tid in request & NO TRACK");
  request.referer = "http://google.com/search?hl=en&q=" +
      no_track_words + "&btnG=Search";
  request.tid.clear();

  FAIL_CONTEXT(
    SpecialEffectsChecker(
      client, request,
      "0",
      SpecialEffectsChecker::SE_ADV |
        SpecialEffectsChecker::SE_NO_TRACK).check(),
    "ADV & NO TRACK");

  std::string uid_raw;
  client.get_cookies().find_value("uid", uid_raw);
  std::string uid =
    AutoTest::prepare_uid(uid_raw,  AutoTest::UUE_ADMIN_PARAMVALUE);

  FAIL_CONTEXT(
    BaseProfileChecker(
      this, uid, false,
      AutoTest::UserInfoManagerController,
      BaseProfileChecker::Expected().
        page_ht_candidates("").
        page_history_matches("").
        page_history_visits("").
        page_session_matches("").
        search_ht_candidates("").
        search_history_matches("").
        search_history_visits("").
        search_session_matches("").
        url_ht_candidates("").
        url_history_matches("").
        url_history_visits("").
        url_session_matches("")).check(),
    "Check no visits");

  add_descr_phrase("no tid in request & NO ADV+NO TRACK");
  request.referer = no_track_urls + "/ads";
  request.referer_kw=no_adv_words;

  FAIL_CONTEXT(
    SpecialEffectsChecker(
      client, request,
      "0",
      SpecialEffectsChecker::SE_NO_ADV |
        SpecialEffectsChecker::SE_NO_TRACK).check(),
    "NO ADV & NO TRACK");

  FAIL_CONTEXT(
    BaseProfileChecker(
      this, uid, false,
      AutoTest::UserInfoManagerController,
      BaseProfileChecker::Expected().
        page_ht_candidates("").
        page_history_matches("").
        page_history_visits("").
        page_session_matches("").
        search_ht_candidates("").
        search_history_matches("").
        search_history_visits("").
        search_session_matches("").
        url_ht_candidates("").
        url_history_matches("").
        url_history_visits("").
        url_session_matches("")).check(),
    "Check no visits");

  request.referer.clear();
  request.referer_kw.clear();
  client.process_request(request);

  FAIL_CONTEXT(
    AutoTest::predicate_checker(
      !client.debug_info.history_channels.size()), 
    "history_channels must be empty");
   
  return true;
}

