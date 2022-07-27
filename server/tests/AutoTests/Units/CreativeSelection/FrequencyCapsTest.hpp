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

#ifndef _UNITTEST__FREQUENCYCAPSTEST_
#define _UNITTEST__FREQUENCYCAPSTEST_

#include <tests/AutoTests/Commons/Common.hpp>

typedef AutoTest::AdClient AdClient;
typedef AutoTest::NSLookupRequest NSLookupRequest;
typedef std::vector<std::string> StrVector;

class FrequencyCapsTest: public BaseUnit
{
public: 
  FrequencyCapsTest(
    UnitStat& stat_var,
    const char* task_name,
    XsdParams params_var)
    : BaseUnit(stat_var, task_name, params_var),
      time_()
  {};
 
  virtual ~FrequencyCapsTest() noexcept
  {};

private:
  enum FreqCapConfirmStrategy
  {
    FCC_DONT_CONFIRM = 0,
    FCC_CONFIRM_PREVIOUS_AFTER_NEW,
    FCC_CONFIRM_ALL_AFTER
  };

private:
  virtual bool run_test();

  void process_campaign_combined_limits_case_();

  void process_creative_window_limit_with_competitive_creative_case_();

  // standard window limit test helpers
  // one ad expected as result for non full freq caps
  // no ad for full freq caps
  void
  process_window_limit_display_ad_case_(
    const char* case_name,
    const char* entities_name, // unique part of entities names
    bool track_pixel = false);

  // first 3 creatives expected as result for non full freq caps
  // second 3 for full freq caps or
  //   no ads if noads_if_fc_full is true
  void
  process_window_limit_text_ads_case_(
    const char* case_name,
    const char* entities_name,
    bool noads_if_fc_full = false,
    bool track_pixel = false);

  void
  process_window_limit_case_(
    const char* case_name,
    AdClient& test_client,
    NSLookupRequest& request,
    const StrVector& nofc_ccids,
      // ccid's that must be returned when freq cap isn't fullfil
    const StrVector& fullfil_fc_ccids = StrVector(),
      // ccid's that must be returned when freq cap is fullfil
    bool track_pixel = false);

  void
  process_window_limit_and_competitive_selection_case_(
    AdClient& test_client,
    NSLookupRequest& request);

  void
  process_window_limit_simple_case_(
    AdClient& test_client,
    NSLookupRequest& request,
    const StrVector& nofc_ccids,
    const StrVector& fullfil_fc_ccids,
    bool expected_track_pixel,
    FreqCapConfirmStrategy confirm_imps_strategy = FCC_DONT_CONFIRM);

  void
  process_window_limit_confirm_timeout_case_(
    AdClient& test_client,
    NSLookupRequest& request,
    const StrVector& cc_id);

  // standard life limit case helpers
  // one ad expected as result for non full freq caps
  // no ad for full freq caps
  void
  process_life_count_display_ad_case_(
    const char* case_name,
    const char* entities_name, // unique part of entities names
    bool track_pixel = false);

  // first 3 creatives expected as result for non full freq caps
  // second 3 for full freq caps or
  //   no ads if noads_if_fc_full is true
  void
  process_life_count_text_ads_case_(
    const char* case_name,
    const char* entities_name,
    bool noads_if_fc_full = false,
    bool track_pixel = false);

  void
  process_life_count_case_(
    AdClient& test_client,
    NSLookupRequest& request,
    const StrVector& nofc_ccids,
    const StrVector& fullfil_fc_ccids = StrVector(),
    bool track_pixel = false);

  // period freq caps helpers
  void
  process_period_display_ad_case_(
    const char* case_name,
    const char* entities_name);

  void
  process_period_text_ads_case_(
    const char* case_name,
    const char* entities_name,
    bool no_creatives_if_fc_full);

  void
  process_period_case_(
    AdClient &test_client,
    NSLookupRequest& request,
    const StrVector& nofc_ccids,
    const StrVector& fullfil_fc_ccids = StrVector());

  void
  process_combined_limits_case_(
    AdClient &test_client,
    NSLookupRequest& request,
    const StrVector& cc_id);

  // Util methods for frequency cap scenario check
  void print_fcap_ui_(AdClient &test_client);

private:
  AutoTest::Time time_;
  unsigned int min_request_period;
};

#endif // _UNITTEST__FREQUENCYCAPSTEST_

