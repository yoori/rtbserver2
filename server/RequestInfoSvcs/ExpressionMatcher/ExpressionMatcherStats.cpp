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
/// @file ExpressionMatcherStats.cpp
#include "ExpressionMatcherStats.hpp"

namespace AdServer
{
  namespace RequestInfoSvcs
  {
    namespace
    {
      const ExpressionMatcherStatsImpl::Key OPTIN_USER(
        "processedMatches-OptInUser-Count");
      const ExpressionMatcherStatsImpl::Key TEMPORARY_USER(
        "processedMatches-temporaryUser-Count");
      const ExpressionMatcherStatsImpl::Key NOT_OPTIN_USER(
        "processedMatches-nonOptInUser-Count");
      const ExpressionMatcherStatsImpl::Key LAST_PROCESSED_TIMESTAMP(
        "processedRequestBasicChannelsTimestamp");
    }

    void
    ExpressionMatcherStatsImpl::fill_values(const Stats& stats)
      /*throw (eh::Exception)*/
    {
      Sync::PosixGuard guard(mutex_);
      set_<UnsignedInt>(OPTIN_USER, stats.processed_matches_optin_user);
      set_<UnsignedInt>(TEMPORARY_USER, stats.processed_matches_temporary_user);
      set_<UnsignedInt>(NOT_OPTIN_USER, stats.processed_matches_non_optin_user);
      set_(LAST_PROCESSED_TIMESTAMP, stats.last_processed_file_timestamp.as_double());
   }

  }
}
