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
#include "CampaignTypes.hpp"

namespace AdServer
{
  namespace CampaignSvcs
  {
    const char*
    to_str(UserStatus status) noexcept
    {
      switch (status)
      {
      case US_UNDEFINED:
        return "UNDEFINED";

      case US_OPTIN:
        return "OPTIN";

      case US_OPTOUT:
        return "OPTOUT";

      case US_PROBE:
        return "PROBE";

      case US_TEMPORARY:
        return "TEMPORARY";

      case US_NONE:
        return "NONE";

      case US_NOEXTERNALID:
        return "NOEXTERNALID";

      case US_EXTERNALPROBE:
        return "EXTERNALPROBE";

      case US_FOREIGN:
        return "FOREIGN";

      case US_BLACKLISTED:
        return "BLACKLISTED";
      }

      return "";
    }

    const char*
    to_str(CampaignMode mode) noexcept
    {
      switch (mode)
      {
      case CM_RANDOM:
        return "RANDOM";

      case CM_NON_RANDOM:
        return "NON-RANDOM";
      }

      return "";
    }

    const char*
    to_str(AuctionType type) noexcept
    {
      switch (type)
      {
      case AT_RANDOM:
        return "RANDOM";

      case AT_MAX_ECPM:
        return "MAX ECPM";

      case AT_PROPORTIONAL_PROBABILITY:
        return "PROPORTIONAL PROBABILITY";
      }

      return "";
    }
  }
}
