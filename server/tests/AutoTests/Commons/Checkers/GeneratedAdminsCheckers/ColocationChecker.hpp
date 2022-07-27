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

#ifndef __AUTOTESTS_COMMONS_ADMINS_COLOCATIONCHECKER_HPP
#define __AUTOTESTS_COMMONS_ADMINS_COLOCATIONCHECKER_HPP

#include <tests/AutoTests/Commons/Admins/ColocationAdmin.hpp>
#include <tests/AutoTests/Commons/Checkers/AdminsChecker.hpp>
#include <tests/AutoTests/Commons/Checkers/Checker.hpp>

namespace AutoTest
{
  class ColocationChecker:
    public AutoTest::Checker
  {
    public:
      typedef ColocationAdmin::Expected Expected;

      ColocationChecker(
        BaseUnit* test,     
        unsigned long colo,
        const Expected& expected,
        AdminExistCheck exists = AEC_EXISTS) :
        test_(test),
        colo_(colo),
        expected_(expected),
        exists_(exists)
        {}

      virtual ~ColocationChecker() noexcept {}

      bool check(bool throw_error = true) /*throw (CheckFailed, eh::Exception)*/;

    private:

      BaseUnit* test_;
      unsigned long colo_;
      Expected expected_;     
      AdminExistCheck exists_;

  };
}
#endif  // __AUTOTESTS_COMMONS_ADMINS_COLOCATIONCHECKER_HPP
