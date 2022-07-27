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
#ifndef AUTOTESTS_UNITS_TAGUPDATETEST_HPP
#define AUTOTESTS_UNITS_TAGUPDATETEST_HPP

#include <tests/AutoTests/Commons/Common.hpp>

/**
 * @class TagUpdateTest
 * @brief Test for tag updates
 */ 
class TagUpdateTest: public BaseDBUnit
{
public:
  TagUpdateTest(
    UnitStat& stat_var, 
    const char* task_name, 
    XsdParams params_var)
    : BaseDBUnit(stat_var, task_name, params_var)
  {};
 
  virtual ~TagUpdateTest() noexcept
  {};
 
private:

  unsigned long other_size_type_;
  unsigned int site_id_;
  unsigned int size_468x60_id_;
  std::string size_468x60_name_;
  unsigned int default_template_;

  void set_up();
  void tear_down();
  bool run();

  void tag_create_case();
  void tag_update_creative_category_exclusion_case();
  void tag_update_size_case();
  void tag_remove_case();
};

#endif /*AUTOTESTS_UNITS_TAGUPDATETEST_HPP*/
