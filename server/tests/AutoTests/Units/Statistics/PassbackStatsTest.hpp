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


#ifndef _AUTOTEST__PASSBACKSTATSTEST_
#define _AUTOTEST__PASSBACKSTATSTEST_
 
#include <tests/AutoTests/Commons/Common.hpp>


namespace DB = AutoTest::DBC;
namespace ORM = AutoTest::ORM;

       
/**
 * @class PassbackStatsTest
 * @brief PassbackStats logging test
 */
 
class PassbackStatsTest: public BaseUnit
{
  typedef AutoTest::AdClient AdClient;
  typedef AutoTest::NSLookupRequest NSLookupRequest;
  typedef AutoTest::ORM::PassbackStats PassbackStats;
  
public:
 
  PassbackStatsTest(
      UnitStat& stat_var, 
      const char* task_name, 
      XsdParams params_var):
    BaseUnit(stat_var, task_name, params_var),
    conn_(open_pq()),
    today(Generics::Time::get_time_of_day())
  { }
 
  virtual ~PassbackStatsTest() noexcept
  { }
 
private:
  DB::Conn  conn_;
  NSLookupRequest request;
  Generics::Time today;
  unsigned long default_colo;

  void
  process_and_check_passback(
    AdClient &client,
    std::string passback_request = std::string(),
    size_t request_count = 1);

  virtual bool run_test();

  void
  log_pb_profile(
    std::string request_id);

  void scenario1(
    bool same_id,
    int tag,
    const char* part);
  void scenario2();
  void scenario3();
  void scenario4();
  void scenario5();
  void scenario6();
  void scenario7();
  void scenario8();
 
  ORM::StatsList<PassbackStats> stats_;
  std::list<PassbackStats::Diffs> diffs_;
  std::list<std::string> requests_;
};
 
#endif //_AUTOTEST__PASSBACKSTATSTEST_
