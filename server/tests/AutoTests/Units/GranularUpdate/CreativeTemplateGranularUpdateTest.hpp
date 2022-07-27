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
#ifndef _UNITTEST__CREATIVETEMPLATEGRANULARUPDATETEST_
#define _UNITTEST__CREATIVETEMPLATEGRANULARUPDATETEST_

#include <tests/AutoTests/Commons/Common.hpp>

namespace ORM = ::AutoTest::ORM;


/**
* @class CreativeTemplateGranularUpdateTest
* @brief Test for template+files granular update
*/ 
class CreativeTemplateGranularUpdateTest:
  public BaseDBUnit
{
public:
 
  CreativeTemplateGranularUpdateTest(
      UnitStat& stat_var, 
      const char* task_name, 
      XsdParams params_var):
    BaseDBUnit(stat_var, task_name, params_var)
  {};
 
  virtual ~CreativeTemplateGranularUpdateTest() noexcept
  {};
 
private:

  std::string file1_;
  std::string file2_;
  std::string file3_;
  int app_format_id_;
  std::string format_name_;
  int size_300x250_id_;
  std::string size_300x250_name_;
  int size_468x60_id_;
  std::string size_468x60_name_;

  void set_up    ();
  void tear_down ();
  bool run();

  void testcase_add_template();
  void testcase_change_template();
  void testcase_delete_template();
  void testcase_del_status_template();
};

#endif
