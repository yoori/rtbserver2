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

#ifndef _AUTOTEST__USERPROFILESEXCHANGECOMMON_
#define _AUTOTEST__USERPROFILESEXCHANGECOMMON_

#include <tests/AutoTests/Commons/Common.hpp>

namespace AutoTest
{
  namespace UserProfilesExchange
  {

    // Alias for NSLookupRequest
    typedef AutoTest::NSLookupRequest  NSLookupRequest;

    /**
   * @class CheckWaitHistoryChannel
   * @brief History channel appearence checker
   *
   * This checker used for wait history channel appearance.
   * Also, it check response colo_id.
   */
    class CheckWaitHistoryChannel: public AutoTest::Checker
    {
      static const unsigned long SLEEP_TIME = 30; // 30 seconds between checks
    public:

      /**
       * @brief Constructor.
       *
       * @param client (user).
       * @param expected channel.
       * @param expected colo_id.
       * @param wait timeout.
       * @param checker request.
       */
      CheckWaitHistoryChannel (
          AutoTest::AdClient& client,
          unsigned long channel,
          const char* colo,
          unsigned long wait_time,
          const NSLookupRequest& request = NSLookupRequest());

      /**
       * @brief Constructor.
       *
       * @param client (user).
       * @param expected channels array.
       * @param channels array size.
       * @param expected colo_id.
       * @param wait timeout.
       * @param checker request.
       */
      CheckWaitHistoryChannel (
        AutoTest::AdClient& client,
        unsigned long channels[],
        size_t channel_size,
        const char* colo,
        unsigned long wait_time,
        const NSLookupRequest& request = NSLookupRequest());

     /**
      * @brief Destructor.
      */
      virtual ~CheckWaitHistoryChannel() noexcept;

      /**
      * @brief Check.
      * @param throw on error flag.
      */
      bool check(bool throw_error = true) /*throw(eh::Exception)*/;

    private:
      AutoTest::AdClient& client_;      // client(user)
      std::list<std::string> expected_; // expected channels list
      std::string colo_;                // expected colo
      unsigned long wait_time_;         // wait timeout
      std::string request_;             // checker request
    };
  }
}


#endif  // _AUTOTEST__USERPROFILESEXCHANGECOMMON_
