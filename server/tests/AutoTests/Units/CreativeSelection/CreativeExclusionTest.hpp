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
#ifndef _UNITTEST__BASICCREATIVEEXCLUSIONTEST_
#define _UNITTEST__BASICCREATIVEEXCLUSIONTEST_

#include <tests/AutoTests/Commons/Common.hpp>

namespace
{
  const unsigned short TAGS_COUNT_1 = 10;
  const unsigned short TAGS_COUNT_2 = 15;

  struct TestCaseType
  {
    const char* name_prefix;
    std::string description;
    const bool  ccid_appearances[TAGS_COUNT_2];
  };

  struct ClickUrlTestCaseD
  {
    const char* name_prefix;
    const char* referer;
  };
};

class CreativeExclusionTest: public BaseUnit
{
public:
 
  CreativeExclusionTest(
    UnitStat& stat_var, 
    const char* task_name, 
    XsdParams params_var)
    : BaseUnit(stat_var, task_name, params_var)
  {};
 
  virtual ~CreativeExclusionTest() noexcept
  {};
 
private:
  AutoTest::NSLookupRequest request;

  virtual bool run_test();

  void exclusion(
    const TestCaseType* test_cases,
    const unsigned short& cases_count,
    const unsigned short tags_count);

  void excluding_higher_weight_creative_();
  void excluding_by_creative_template_and_tag_();
  void tags_exclusion_for_text_creatives_();

  void exclusion_text_by_domain_match_within_creative_token_();
  void exclusion_by_ccg_keyword_click_url_();
};

#endif
