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
#ifndef TRIGGEER_FILTERING_APP_HPP
#define TRIGGEER_FILTERING_APP_HPP

#include<string>
#include<map>
#include<set>
#include<istream>
#include<fstream>
#include<ChannelSvcs/ChannelCommons/CommonTypes.hpp>
#include<ChannelSvcs/ChannelServer/ChannelContainer.hpp>

namespace AdServer
{
  class Application
  {
  public:
    DECLARE_EXCEPTION(Exception, eh::DescriptiveException);
    DECLARE_EXCEPTION(BadParams, Exception);

    int run(int argc, char* argv[]) /*throw(BadParams)*/;

  private:

    void load_dictionary_(const char* file_name) /*throw(BadParams)*/;

    void read_triggers_(std::istream& is) /*throw(eh::Exception)*/;

    void write_result_(std::ostream& os) noexcept;

    void filter_() /*throw(Exception)*/;

    void usage_(const char* program_name) noexcept;

    static
    int compary_triggers_(
      const Language::Trigger::Trigger& trigger_view,
      const Language::Trigger::Trigger& trigger_view2)
      noexcept;

  private:
    typedef std::map<unsigned long, std::string> Triggers;

    Triggers triggers_;
    AdServer::ChannelSvcs::ChannelContainer container_;
    ChannelSvcs::StringSet dict_;
  };
}

#endif
