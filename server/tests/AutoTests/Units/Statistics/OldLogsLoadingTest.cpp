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
#include "OldLogsLoadingTest.hpp"
 
REFLECT_UNIT(OldLogsLoadingTest) (
  "Statistics",
  AUTO_TEST_SLOW
);

namespace
{
  typedef AutoTest::ORM::HourlyStats HourlyStats;
  namespace ORM = ::AutoTest::ORM;
}

bool 
OldLogsLoadingTest::run_test()
{
  FAIL_CONTEXT(
    AutoTest::predicate_checker(
      get_global_params().LogGeneralizerIn()),
    "need LogGeneralizerIn item of type PathType in config file");

  std::string login = get_global_params().LogGeneralizerIn()->path();

  add_descr_phrase("Initializing DB connection");
  AutoTest::DBC::Conn conn(open_pq());

  add_descr_phrase("CreativeStat v 3.0");
  case_CreativeStat(conn, login, 1);

  return true;
}

void
OldLogsLoadingTest::case_CreativeStat(
  AutoTest::DBC::Conn& conn, 
  const std::string& login,
  int num)
{
  std::string n = strof(num);
  std::string dst = login + "CreativeStat/";
  
  std::string file = fetch_string("CreativeStatFile" + n);
  std::string commit_file = fetch_string("CreativeStatCommitFile" + n);
  std::string date = fetch_string("CreativeStatDate" + n);
  const unsigned long cc_id = fetch_int("CreativeStatCC" + n);
  const unsigned long numshown = fetch_int("CreativeStatNumShown" + n);
  const unsigned long imps = fetch_int("CreativeStatImps" + n);
  
  HourlyStats stats;
  stats.key().cc_id(cc_id).num_shown(numshown).stimestamp(date);
  stats.select(conn);
  AutoTest::CopyCmd(file, dst).exec();
  AutoTest::CopyCmd(commit_file, dst).exec();

  HourlyStats::Diffs diff;
  diff.imps(imps);
  FAIL_CONTEXT(
    AutoTest::wait_checker(
      AutoTest::stats_diff_checker(
        conn, diff, stats)).check(),
    "must got expected values for case_CreativeStat");
}

