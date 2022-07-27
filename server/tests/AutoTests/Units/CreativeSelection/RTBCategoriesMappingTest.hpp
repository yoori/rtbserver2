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

#ifndef _AUTOTEST__RTBCATEGORIESMAPPINGTEST_
#define _AUTOTEST__RTBCATEGORIESMAPPINGTEST_
  
#include <tests/AutoTests/Commons/Common.hpp>
  

class RTBCategoriesMappingTest : public BaseUnit
{

  typedef AutoTest::AdClient AdClient;
  typedef AutoTest::OpenRTBRequest OpenRTBRequest;
  typedef AutoTest::TanxRequest TanxRequest;
  typedef AutoTest::BaiduRequest BaiduRequest;
  typedef AutoTest::OpenRTBResponseChecker OpenRTBResponseChecker;
  typedef AutoTest::TanxResponseChecker TanxResponseChecker;
  typedef AutoTest::BaiduResponseChecker BaiduResponseChecker;
  
public:
  RTBCategoriesMappingTest(
    UnitStat& stat_var,
    const char* task_name,
    XsdParams params_var) :
    BaseUnit(stat_var, task_name, params_var)
  { }

  virtual ~RTBCategoriesMappingTest() noexcept
  { }

  struct RequestBanner
  {
    const char* size;
    const char* battr;
  };

  struct ResponseBid
  {
    const char* cc_id;
    const char* visual_categories;
    const char* content_categories;
  };

  struct AllyesBid
  {
    const char* cc_id;
    unsigned long fmt;
    const char* cat;
  };

  template<size_t BannersCount = 1>
  struct RTBTestCase
  {
    const char* description;
    // Request params
    const char* source;
    RequestBanner banners[BannersCount];
    const char* bcat;
    // Response params
    ResponseBid bids[BannersCount];
  };

  struct TanxTestCase
  {
    const char* description;
    // Request params
    RequestBanner banner;
    const char* bcat;
    // Response params
    ResponseBid bid;
  };

  template<size_t BannersCount = 1>
  struct AllyesTestCase
  {
    const char* description;
    // Request params
    const char* source;
    RequestBanner banners[BannersCount];
    const char* bcat;
    // Response params
    AllyesBid bids[BannersCount];
  };

  struct BaiduTestCase
  {
    const char* description;
    // Request params
    RequestBanner banner;
    // Response params
    ResponseBid bid;
  };

private:


  template<typename Object, typename Param>
  void
  set_category(
    Object& obj,
    Param Object::* setter,
    const std::string& cat);

  template<typename Object, typename RetVal, typename T>
  void
  set_category(
    Object& obj,
    RetVal (Object::*setter)(T),
    const std::string& cat);

  template<typename Object, typename Setter>
  void set_categories(
    const char* cat_list,
    Object& obj,
    Setter setter);

  template<typename Object, typename Setter, typename Touch>
  void set_expected_categories(
    const char* cat_list,
    Object& obj,
    Setter setter,
    Touch touch);

  void
  prepare_request(
    TanxRequest& request,
    const TanxTestCase& test_case);

  void
  prepare_request(
    BaiduRequest& request,
    const BaiduTestCase& test_case);
  
  template<typename TestCase>
  void
  prepare_request(
    OpenRTBRequest& request,
    const TestCase& test_case);

  void
  prepare_checker(
    TanxResponseChecker::Expected& expected,
    const TanxTestCase& test_case);

  void
  prepare_checker(
    BaiduResponseChecker::Expected& expected,
    const BaiduTestCase& test_case);
  
  template<size_t Slots>
  void
  prepare_checker(
    OpenRTBResponseChecker::ExpectedList& expected,
    const RTBTestCase<Slots>& test_case);

  template<size_t Slots>
  void
  prepare_checker(
    OpenRTBResponseChecker::ExpectedList& expected,
    const AllyesTestCase<Slots>& test_case);
 
  template<typename Traits, typename CaseType, size_t Cases>
  void
  perform_case_(
    const CaseType (&cases)[Cases]);

  bool run_test();
};

#endif // _AUTOTEST__RTBCATEGORIESMAPPINGTEST_
