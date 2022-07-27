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
#include "XsltCreativeTemplateValidation.hpp"

REFLECT_UNIT(XsltCreativeTemplateValidation) (
  "CreativeInstantiation",
  AUTO_TEST_FAST
);

namespace
{
  typedef AutoTest::NSLookupRequest NSLookupRequest;
  typedef AutoTest::AdClient AdClient;
  typedef AutoTest::SelectedCreativeChecker SelectedCreativeChecker;
  
  struct TestData
  {
    const char* keyword;
    const char* tid;
    const char* ccid;
    std::string description;
    unsigned int status;
  };

  const TestData TEST_CASES[] =
  {
    {
      "Keyword/01", "Tag/01", 0, "Empty template", 204
    },
    {
      "Keyword/02", "Tag/02", 0, "Absent template file", 204
    },
    {
      "Keyword/03", "Tag/03", 0, "Invalid foros:escape-js call", 204
    },
    {
      "Keyword/04", "Tag/04", "Cid/04", "Valid foros calls", 200
    },
    {
      "Keyword/05", "Tag/05", 0, "Invalid template XML", 204
    }, 
    {
      "Keyword/06", "Tag/06", 0, "Absent namespace", 204
    },
    {
      "Keyword/07", "Tag/07", 0, "Unknow function call", 204 
    },
    {
      "Keyword/08", "Tag/08", "Cid/08", "Include", 200
    },
    {
      "Keyword/09", "Tag/09", 0, "Invalid include", 204
    }
  };
}

bool 
XsltCreativeTemplateValidation::run_test()
{
  AdClient client(AdClient::create_user(this));
  
  for(size_t i = 0; i < countof(TEST_CASES); ++i)
  {

    SelectedCreativeChecker checker(
      client,
      NSLookupRequest().
        tid(fetch_int(TEST_CASES[i].tid)).
      referer_kw(fetch_string(TEST_CASES[i].keyword)),
      TEST_CASES[i].ccid? fetch_int(TEST_CASES[i].ccid): 0);

    FAIL_CONTEXT(
      checker.check(),
      TEST_CASES[i].description +
        ". Check ccid");

    FAIL_CONTEXT(
      AutoTest::equal_checker(
        TEST_CASES[i].status,
        checker.client().req_status()).check(),
      TEST_CASES[i].description +
        ". Check status");
  }

  return true;
}
 
