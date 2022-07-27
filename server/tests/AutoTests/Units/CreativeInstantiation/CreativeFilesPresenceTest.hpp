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
#ifndef _UNITTEST__CREATIVEFILESPRESENCETEST_
#define _UNITTEST__CREATIVEFILESPRESENCETEST_

#include <tests/AutoTests/Commons/Common.hpp>
 
class CreativeFilesPresenceTest: public BaseUnit
{
public:
 
  CreativeFilesPresenceTest(
      UnitStat& stat_var, 
      const char* task_name, 
      XsdParams params_var):
    BaseUnit(stat_var, task_name, params_var)
  {};
 
  virtual ~CreativeFilesPresenceTest() noexcept
  {};
 
private:
 
  virtual bool run_test();
  void file_not_present_case();
  void normal_case();
  void url_not_present_case();
  void file_url_present_case();
  void template_file_not_present_case();
  void w_notblock_a_case();
  void w_notblock_a_size_format_case();
  void text_2campaign_case();
  void text_campaign_case();
  void ADSC_8367(); // 'Dynamic File' type option
};

#endif
