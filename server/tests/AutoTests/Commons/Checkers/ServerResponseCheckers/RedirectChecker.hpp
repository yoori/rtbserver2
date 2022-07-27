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
#ifndef __AUTOTESTS_COMMONS_CHECKERS_REDIRECTCHECKER_HPP
#define __AUTOTESTS_COMMONS_CHECKERS_REDIRECTCHECKER_HPP

#include <tests/AutoTests/Commons/Checkers/Checker.hpp>
#include <tests/AutoTests/Commons/AdClient.hpp>
#include <String/RegEx.hpp>

namespace AutoTest
{
  /**
   * @class RedirectChecker
   * @brief Check client redirection.
   */
  class RedirectChecker: public AutoTest::Checker
  {
  public:
    /**
     * @brief Constructor.
     *
     * @param client (user).
     * @param expected location.
     */
    RedirectChecker(
      AdClient& client,
      const std::string& location);

    /**
     * @brief Constructor.
     *
     * @param client (user).
     * @param regex to check location.
     */
    RedirectChecker(
      AdClient& client,
      const String::RegEx& regex);

    /**
     * @brief Destructor.
     */
    virtual ~RedirectChecker() noexcept;

    /**
     * @brief Get location.
     */
    const std::string&
    location() const;

    /**
     * @brief Check.
     * @param throw on error flag.
     */
    bool
    check(
      bool throw_error = true)
      /*throw(eh::Exception)*/;

  private:
    AdClient client_; // client(user)
    String::RegEx regex_; // regex to check location
    std::string location_; // location
  };
} //namespace AutoTest

// inlines
namespace AutoTest
{
  inline
  const std::string&
  RedirectChecker::location() const
  {
    return location_;
  }
}

#endif /*AUTOTESTS_COMMONS_CHECKERS_REDIRECTCHECKER_HPP*/
