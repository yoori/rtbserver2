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
#ifndef __AUTOTESTS_COMMONS_CHECKERS_TAGPASSBACKCHECKER_HPP
#define __AUTOTESTS_COMMONS_CHECKERS_TAGPASSBACKCHECKER_HPP

#include <tests/AutoTests/Commons/Checkers/Checker.hpp>
#include <tests/AutoTests/Commons/AdClient.hpp>

namespace AutoTest
{
  /**
   * @class TagPassbackChecker
   * @brief Check tag passback.
   */
  class TagPassbackChecker : public Checker
  {
  public:

    /**
     * @class Tokens
     * @brief Passback tokens.
     */
    class Tokens
    {
    public:
      /**
       * @brief Default constructor.
       */
      Tokens();

      /**
       * @brief Get PASSBACK_TYPE.
       */
      const std::string& type() const;

      /**
       * @brief Get PASSBACK_URL.
       */
      const std::string& url() const;

      /**
       * @brief Get PASSBACK_PIXEL.
       */
      const std::string& pixel() const;
      
      /**
       * @brief Set PASSBACK_TYPE.
       */
      Tokens& type(const std::string& t);

      /**
       * @brief Set PASSBACK_URL.
       */
      Tokens& url(const std::string& url);

      /**
       * @brief Set PASSBACK_PIXEL.
       */
      Tokens& pixel(const std::string& pixel);

    private:
      std::string type_;  // PASSBACK_TYPE
      std::string url_; // PASSBACK_URL
      std::string pixel_; // PASSBACK_PIXEL
    };
  private:

    typedef const std::string& (Tokens::*Get)() const;
    typedef Tokens& (Tokens::*Set)(const std::string&);
    struct PassbackToken
    {
      const char* name;
      Get get;
      Set set;
    };

    static const size_t MAX_TOKEN_SIZE = 4096;
    static const size_t TOKEN_COUNT = 3;
    static const PassbackToken TOKENS[TOKEN_COUNT];

  public:

    /**
     * @brief Constructor.
     *
     * @param client.
     * @param expected PASSBACK_URL.
     */
    TagPassbackChecker(
      const AdClient& client,
      const std::string& url);

    /**
     * @brief Constructor.
     *
     * @param client.
     * @param expected.
     */
    TagPassbackChecker(
      const AdClient& client,
      const Tokens& expected);

    /**
     * @brief Destructor.
     */
    virtual ~TagPassbackChecker() noexcept;

    /**
     * @brief Get tokens.
     */
    const Tokens& tokens() const;
    
    /**
     * @brief Check.
     * @param throw on error flag.
     * @return true - success check, false - fail.
     */
    virtual
    bool
    check(bool throw_error = true)
      /*throw(eh::Exception)*/;

  private:
    AdClient client_;
    Tokens expected_;
    Tokens got_;
  };
} //namespace AutoTest

// inlines
namespace AutoTest
{
  // TagPassbackChecker::Tokens
  inline
  const std::string&
  TagPassbackChecker::Tokens::type() const
  {
    return type_;
  }

  inline
  const std::string&
  TagPassbackChecker::Tokens::url() const
  {
    return url_;
  }

  inline
  const std::string&
  TagPassbackChecker::Tokens::pixel() const
  {
    return pixel_;
  }

  inline
  TagPassbackChecker::Tokens&
  TagPassbackChecker::Tokens::type(
    const std::string& t)
  {
    type_ = t;
    return *this;
  }

  inline
  TagPassbackChecker::Tokens&
  TagPassbackChecker::Tokens::url(
    const std::string& url)
  {
    url_ = url;
    return *this;
  }

  inline
  TagPassbackChecker::Tokens&
  TagPassbackChecker::Tokens::pixel(
    const std::string& pixel)
  {
    pixel_ = pixel;
    return *this;
  }

  // TagPassbackChecker
  inline
  const TagPassbackChecker::Tokens&
  TagPassbackChecker::tokens() const
  {
    return got_;
  }
}

#endif /*AUTOTESTS_COMMONS_CHECKERS_TAGPASSBACKCHECKER_HPP*/
