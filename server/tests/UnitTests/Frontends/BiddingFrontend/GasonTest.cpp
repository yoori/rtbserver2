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

#include <string>

#include <Generics/SimpleDecimal.hpp>

#include "../../TestHelpers.hpp"

#include <Commons/Gason.hpp>

typedef Generics::SimpleDecimal<uint64_t, 18, 8> Revenue;

TEST(parse_number)
{
  JsonValue root_value;
  JsonAllocator json_allocator;
  std::string json_for_parse =
    "{\n"
      "\"imp\" : [\n"
      "{\n"
      "  \"banner\" : {"
      "  \"w\" : 120,\n"
      "  \"h\" : 240,\n"
      "  \"battr\" : [ 13 ],\n"
      "  \"expdir\" : [],\n"
      "  \"id\" : \"2130706433~29860016~1386690345~482~15777580135710372407\"\n"
      "  \"long_fraction\" : 9.350009999999999,"
      "  \"long_fraction\" : -9.350009999999999"
      "},\n"
      "\"bidfloor\" : 999999,\n"
      "\"id\" : \"imp-test1\"\n"
      "},\n"
      "0.23e+2],\n"
    "\"test_arg\" : -12.001E-5}";

  char* parse_end = 0;
  JsonParseStatus status = json_parse(
      &json_for_parse[0],
      &parse_end,
      &root_value,
      json_allocator);

  ASSERT_TRUE (status == JSON_PARSE_OK);

  {
    JsonIterator it = begin(root_value);
    ++it;
    ASSERT_EQUALS (it->key, std::string("test_arg"));
    const double test_arg = it->value.toNumber();
    ASSERT_EQUALS (test_arg, -0.00012001);

    const Revenue res = it->value.toDecimal<Revenue>();
    ASSERT_EQUALS (res, Revenue(-0.00012001));
  }

  {
    JsonIterator it = begin(root_value);
    ASSERT_EQUALS (it->key, std::string("imp"));
    ASSERT_EQUALS (it->value.getTag(), JSON_TAG_ARRAY);

    JsonIterator it_2 = begin(it->value);
    ASSERT_EQUALS (it_2->value.getTag(), JSON_TAG_OBJECT);

    JsonIterator it_3 = begin(it_2->value);
    ASSERT_EQUALS (it_3->value.getTag(), JSON_TAG_OBJECT);
    ASSERT_EQUALS (it_3->key, std::string("banner"));

    JsonIterator it_4 = begin(it_3->value);
    ASSERT_EQUALS (it_4->key, std::string("w"));
    ASSERT_EQUALS (it_4->value.toNumber(), 120);
    ASSERT_EQUALS (it_4->value.toDecimal<Revenue>(), Revenue(120));

    ++it_4;
    ASSERT_EQUALS (it_4->key, std::string("h"));
    ASSERT_EQUALS (it_4->value.toNumber(), 240);
    ASSERT_EQUALS (it_4->value.toDecimal<Revenue>(), Revenue(240));

    ++it_4;
    ASSERT_EQUALS (it_4->key, std::string("battr"));
    ASSERT_EQUALS (it_4->value.getTag(), JSON_TAG_ARRAY);
    const JsonIterator it_5 = begin(it_4->value);
    ASSERT_EQUALS (it_5->value.toNumber(), 13);
    ASSERT_EQUALS (it_5->value.toDecimal<Revenue>(), Revenue(13));

    ++it_4;
    ASSERT_EQUALS (it_4->key, std::string("expdir"));
    ASSERT_EQUALS (it_4->value.getTag(), JSON_TAG_ARRAY);
    ASSERT_FALSE(begin(it_4->value) != end(it_4->value));

    ++it_4;
    ASSERT_EQUALS (it_4->key, std::string("id"));
    ASSERT_EQUALS (it_4->value.toString(),
      std::string("2130706433~29860016~1386690345~482~15777580135710372407"));

    ++it_4;
    ASSERT_EQUALS (it_4->key, std::string("long_fraction"));
    ASSERT_EQUALS (it_4->value.toDecimal<Revenue>(), Revenue(9.35001));
    ASSERT_EQUALS (it_4->value.toDecimal<Revenue>(Generics::DMR_FLOOR), Revenue(9.35000999));
    ASSERT_EQUALS (it_4->value.toDecimal<Revenue>(Generics::DMR_CEIL), Revenue(9.35001));

    ++it_4;
    ASSERT_EQUALS (it_4->key, std::string("long_fraction"));
    ASSERT_EQUALS (it_4->value.toDecimal<Revenue>(), Revenue(-9.35001));
    ASSERT_EQUALS (it_4->value.toDecimal<Revenue>(Generics::DMR_FLOOR), Revenue(-9.35001));
    ASSERT_EQUALS (it_4->value.toDecimal<Revenue>(Generics::DMR_CEIL), Revenue(-9.35000999));

    ++it_3;
    ASSERT_EQUALS (it_3->key, std::string("bidfloor"));
    ASSERT_EQUALS (it_3->value.toNumber(), 999999);
    ASSERT_EQUALS (it_3->value.toDecimal<Revenue>(), Revenue(999999));

    ++it_3;
    ASSERT_EQUALS (it_3->key, std::string("id"));
    ASSERT_EQUALS (it_3->value.toString(), std::string("imp-test1"));

    ++it_2;
    ASSERT_EQUALS (it_2->value.toNumber(), 23);
    ASSERT_EQUALS (it_2->value.toDecimal<Revenue>(), Revenue(23));
  }
}

RUN_TESTS
