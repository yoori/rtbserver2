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
#ifndef AUTOTESTS_BEHAVPARAMSGRANULARUPDATETEST_H
#define AUTOTESTS_BEHAVPARAMSGRANULARUPDATETEST_H

#include <tests/AutoTests/Commons/Common.hpp>


class BehavParamsGranularUpdateTest : public BaseDBUnit
{
public:
  BehavParamsGranularUpdateTest(UnitStat& stat_var,
    const char* task_name,
    XsdParams params_var)
    : BaseDBUnit(stat_var, task_name, params_var)
  {}

  virtual ~BehavParamsGranularUpdateTest() noexcept
  {}

private:

  bool run();
  void tear_down() {}

  void empty();
  void assign();
  void change();
  void remove();
  void add_list();
  void del_param();

};

#endif // AUTOTESTS_BEHAVPARAMSGRANULARUPDATETEST_H
