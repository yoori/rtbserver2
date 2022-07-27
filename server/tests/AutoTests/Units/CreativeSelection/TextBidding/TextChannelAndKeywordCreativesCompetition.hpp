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
#ifndef _AUTOTEST__TEXTCHANNELANDKEYWORDCREATIVESCOMPETITION_
#define _AUTOTEST__TEXTCHANNELANDKEYWORDCREATIVESCOMPETITION_
  
#include <tests/AutoTests/Commons/Common.hpp>
  

class TextChannelAndKeywordCreativesCompetition : public BaseUnit
{
public:
  TextChannelAndKeywordCreativesCompetition(
    UnitStat& stat_var,
    const char* task_name,
    XsdParams params_var) :
    BaseUnit(stat_var, task_name, params_var)
  {};

  virtual ~TextChannelAndKeywordCreativesCompetition() noexcept
  {};

private:

  virtual bool run_test();

  void scenario1();
  void scenario2();
  void scenario3();
  void scenario4();
  void scenario5();
  void scenario6();
};

#endif // _AUTOTEST__TEXTCHANNELANDKEYWORDCREATIVESCOMPETITION_