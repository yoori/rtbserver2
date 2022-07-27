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
#ifndef _UNITTEST__KEYWORDCLICKURLTEST_
#define _UNITTEST__KEYWORDCLICKURLTEST_

#include <tests/AutoTests/Commons/Common.hpp>
 
/**
 * @class KeywordClickUrlTest
 * @brief Test for keyword click_url vs creative click_url behaviour
 */
class KeywordClickUrlTest: public BaseUnit
{
public:
 
  KeywordClickUrlTest(
      UnitStat& stat_var, 
      const char* task_name, 
      XsdParams params_var):
    BaseUnit(stat_var, task_name, params_var)
  {};
 
  virtual ~KeywordClickUrlTest() noexcept
  {};
 
private:

  std::string tid;
 
  virtual bool run_test();
  void part1 ();
  void part2 ();
  void part3 ();
  void part4 ();
};

#endif
