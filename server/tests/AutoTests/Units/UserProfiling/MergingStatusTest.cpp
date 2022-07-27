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
#include "MergingStatusTest.hpp"

#include <Generics/Uuid.hpp>

REFLECT_UNIT(MergingStatusTest) (
  "UserProfiling",
  AUTO_TEST_FAST
);

namespace
{
  const char X_MERGE_FAILED[] = "source profile - unknown user";
}


bool 
MergingStatusTest::run_test()
{
  set_up();

  NOSTOP_FAIL_CONTEXT(double_merging());
  NOSTOP_FAIL_CONTEXT(unknown_tuid());

  // Repeat valid case to ensure X-Merging-Failed absent
  NOSTOP_FAIL_CONTEXT(double_merging());
  return true;
}


void MergingStatusTest::set_up()
{
  add_descr_phrase("setUp");
  client.process_request(
    NSLookupRequest().
    tid(fetch_string("TID#1")),
    "get real uid");

  FAIL_CONTEXT(
    AutoTest::predicate_checker(
      client.get_cookies().find_value("uid", uid)),
    "Server should set uid for client");
}

void MergingStatusTest::double_merging()
{
  add_descr_phrase("Double merging (second merging - failed)");

  std::string merge_header, uid2;
  client.set_uid(uid);
  uid2 = create_temporary_profile();
  
  client.process_request(
    NSLookupRequest().
    tid(fetch_string("TID#1")).
    rm_tuid(1).
    tuid(uid2),
    "valid merging");

  FAIL_CONTEXT(
    AutoTest::predicate_checker(
      !client.find_header_value(
        "X-Merge-Failed", merge_header)),
    "Unexpected X-Merging-Failed header");

  // Second request with same uid - merging failed
  client.process_request(
    NSLookupRequest().
    tid(fetch_string("TID#1")).
    tuid(uid2),
    "repeat merging failed");
  
  FAIL_CONTEXT(
    AutoTest::predicate_checker(
      client.find_header_value("X-Merge-Failed", merge_header)),
      "Unexpected X-Merging-Failed header");

  FAIL_CONTEXT(
    AutoTest::equal_checker(
      X_MERGE_FAILED,
      merge_header).check(), 
    "Unexpected X-Merging-Failed value");
}

void MergingStatusTest::unknown_tuid()
{
  add_descr_phrase("Merging with unknown user - failed");

  std::string merge_header;

  client.process_request(
    NSLookupRequest().
    tid(fetch_string("TID#1")).
    tuid(AutoTest::generate_uid()),
    "invalid tuid");
  
  FAIL_CONTEXT(
    AutoTest::predicate_checker(
      client.find_header_value("X-Merge-Failed", merge_header)),
    "Expected X-Merging-Failed header absent");

  FAIL_CONTEXT(
    AutoTest::equal_checker(
      X_MERGE_FAILED,
      merge_header).check(), 
    "Unexpected X-Merging-Failed value");
}

std::string MergingStatusTest::create_temporary_profile()
{
  TemporaryAdClient tclient(
    TemporaryAdClient::create_user(this));
 
  tclient.process_request(
    NSLookupRequest().
    tid(fetch_string("TID#1")),
    "create temporary profile");

  return tclient.get_tuid();
}
