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
#include <Generics/Values.hpp>


namespace Generics
{
  namespace ValuesHelper
  {
    const Values::StoredType StoredMember<Values::SignedInt>::TYPE;
    Values::SignedInt
    Values::StoredValue::* const StoredMember<Values::SignedInt>::MEMBER =
      &Values::StoredValue::signed_int;

    const Values::StoredType StoredMember<Values::UnsignedInt>::TYPE;
    Values::UnsignedInt
    Values::StoredValue::* const StoredMember<Values::UnsignedInt>::MEMBER =
      &Values::StoredValue::unsigned_int;

    const Values::StoredType StoredMember<Values::Floating>::TYPE;
    Values::Floating
    Values::StoredValue::* const StoredMember<Values::Floating>::MEMBER =
      &Values::StoredValue::floating;

    const Values::StoredType StoredMember<Values::String>::TYPE;
    Values::String
    Values::StoredValue::* const StoredMember<Values::String>::MEMBER =
      &Values::StoredValue::string;

    const Values::StoredType StoredMember<char*>::TYPE;
    Values::String
    Values::StoredValue::* const StoredMember<char*>::MEMBER =
      &Values::StoredValue::string;

    const Values::StoredType StoredMember<const char*>::TYPE;
    Values::String
    Values::StoredValue::* const StoredMember<const char*>::MEMBER =
      &Values::StoredValue::string;
  }

  //
  // Values class
  //

  const char* const Values::STORED_TYPES_[] =
  {
    "Signed Int",
    "Unsigned Int",
    "Floating",
    "String",
  };

  Values::Values(size_t table_size) /*throw (eh::Exception)*/
    : data_(table_size)
  {
  }

  void
  Values::swap(Values& values) /*throw (eh::Exception)*/
  {
    Sync::PosixGuard guard(mutex_);
    data_.swap(values.data_);
  }

  void
  Values::swap_(Values& values) /*throw (eh::Exception)*/
  {
    data_.swap(values.data_);
  }
}
