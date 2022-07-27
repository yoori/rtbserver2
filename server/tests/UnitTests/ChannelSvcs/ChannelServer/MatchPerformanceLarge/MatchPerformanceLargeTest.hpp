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
#ifndef MATCH_PERFORMANCE_LAST__TEST_HPP
#define MATCH_PERFORMANCE__LAST_TEST_HPP

#include <ChannelSvcs/ChannelServer/ChannelContainer.hpp>

namespace AdServer
{
  namespace UnitTests
  {

    class MatchPerformanceLargeTest: public TestTemplate
    {
    public:
      MatchPerformanceLargeTest() noexcept;
      int run(int argc, char* argv[]) noexcept;
      int help() noexcept;
    private:

      void fill_matched_words_(
        std::vector<std::string>& matched_words,
        size_t count_hard,
        size_t count_soft) noexcept;

      void prepare_data_(
        ChannelSvcs::UpdateContainer& cont,
        ChannelSvcs::ChannelIdToMatchInfo* info
        ) /*throw(eh::Exception)*/;

      int execute_() /*throw(eh::Exception)*/;

      void generate_url_(std::string& word) /*throw(eh::Exception)*/;

      void prepare_match_data_(
        unsigned long first_id,
        unsigned long count,
        ChannelSvcs::ChannelContainerBase::ChannelMap& buffer)
        /*throw(eh::Exception)*/;

      ChannelSvcs::MergeAtom& new_atom_(
        unsigned long id,
        size_t type,
        std::map<unsigned long, ChannelSvcs::MergeAtom>& atoms,
        ChannelSvcs::ChannelIdToMatchInfo* info)
        /*throw(eh::Exception)*/;

      void parse_keywords_(ChannelSvcs::MatchWords& out) noexcept;

    };

  }
}

#endif

