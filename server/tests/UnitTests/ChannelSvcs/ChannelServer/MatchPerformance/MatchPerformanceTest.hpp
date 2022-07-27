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
#ifndef MATCH_PERFORMANCE_TEST_DEF
#define MATCH_PERFORMANCE_TEST_DEF

#include <ChannelSvcs/ChannelServer/ChannelContainer.hpp>

namespace AdServer
{
  namespace UnitTests
  {

    class MatchPerformanceTest: public TestTemplate
    {
    public:
      MatchPerformanceTest() noexcept;
      int run(int argc, char* argv[]) noexcept;
    private:

      void prepare_data_(
        ChannelSvcs::UpdateContainer& cont,
        ChannelSvcs::ChannelIdToMatchInfo* info
        ) /*throw(eh::Exception)*/;

      int execute_() /*throw(eh::Exception)*/;

      void generate_word(std::string& word) /*throw(eh::Exception)*/;

      void generate_url_(std::string& word) /*throw(eh::Exception)*/;

      void prepare_match_data_(
        unsigned long first_id,
        unsigned long count,
        ChannelSvcs::ChannelContainerBase::ChannelMap& buffer)
        /*throw(eh::Exception)*/;

    };

  }
}

#endif

