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

#ifndef _AUTOTEST__BROKENCHANNELTRIGGERS_
#define _AUTOTEST__BROKENCHANNELTRIGGERS_
 
#include <tests/AutoTests/Commons/Common.hpp>
 
 
class BrokenChannelTriggers: public BaseUnit
{
public:

  typedef AutoTest::AdClient AdClient;
  
  struct TestCase
  {
    const std::string description;
    const char* referer_kw;
    const char* referer;
    const char* matched;
    const char* unmatched;
  };
  
public:
 
  BrokenChannelTriggers(
      UnitStat& stat_var, 
      const char* task_name, 
      XsdParams params_var):
    BaseUnit(stat_var, task_name, params_var)
  {};
 
  virtual ~BrokenChannelTriggers() noexcept
  {};
 
private:
 
  virtual bool run_test();
  
  template<size_t Count>
  void test_group(const TestCase(&tests)[Count]);
  
  void test_case(
    AdClient& client,
    const TestCase& test);
  
};

#endif //_AUTOTEST__BROKENCHANNELTRIGGERS_
