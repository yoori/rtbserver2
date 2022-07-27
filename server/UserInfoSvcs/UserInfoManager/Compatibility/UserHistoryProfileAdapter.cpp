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
#include <Commons/Algs.hpp>

#include <UserInfoSvcs/UserInfoCommons/UserChannelHistoryProfile.hpp>
#include <UserInfoSvcs/UserInfoCommons/ChannelMatcher.hpp>

#include <UserInfoSvcs/UserInfoManager/Compatibility/UserChannelHistoryProfile_v1.hpp>
#include <UserInfoSvcs/UserInfoManager/Compatibility/UserChannelHistoryProfile_v320.hpp>

#include "UserHistoryProfileAdapter.hpp"

namespace AdServer
{
  namespace UserInfoSvcs
  {
    Generics::ConstSmartMemBuf_var
    HistoryProfileAdapter::operator()(
      const Generics::ConstSmartMemBuf* mem_buf)
      /*throw(Exception)*/
    {
      static const char* FUN = "HistoryProfileAdapter::operator()";

      unsigned long version_head_size = HistoryUserProfileVersionReader::FIXED_SIZE;

      if(mem_buf->membuf().size() < version_head_size)
      {
        throw Exception("Corrupt header");
      }

      HistoryUserProfileVersionReader version_reader(
        mem_buf->membuf().data(),
        version_head_size);

      if(version_reader.major_version() != CURRENT_HISTORY_MAJOR_PROFILE_VERSION ||
         version_reader.minor_version() != CURRENT_HISTORY_MINOR_PROFILE_VERSION)
      {
        Generics::SmartMemBuf_var result_mem_buf = Algs::copy_membuf(mem_buf);
        Generics::MemBuf& membuf = result_mem_buf->membuf();

        HistoryUserProfileWriter profile_writer;
        profile_writer.major_version() = CURRENT_HISTORY_MAJOR_PROFILE_VERSION;
        profile_writer.minor_version() = CURRENT_HISTORY_MINOR_PROFILE_VERSION;

        if(version_reader.major_version() == 1 && version_reader.minor_version() == 0)
        {
          AdServer::UserInfoSvcs_v1::HistoryUserProfileReader profile_reader(
            membuf.data(), membuf.size());

          ChannelsMatcher::copy_history_section(
            profile_writer.search_channels(),
            profile_reader.search_channels());

          ChannelsMatcher::copy_history_section(
            profile_writer.page_channels(),
            profile_reader.page_channels());

          ChannelsMatcher::copy_history_section(
            profile_writer.url_channels(),
            profile_reader.url_channels());
        }
        else if(version_reader.major_version() == 2 && version_reader.minor_version() == 0)
        {
          AdServer::UserInfoSvcs_v320::HistoryUserProfileReader profile_reader(
            membuf.data(), membuf.size());

          ChannelsMatcher::copy_history_section(
            profile_writer.search_channels(),
            profile_reader.search_channels());

          ChannelsMatcher::copy_history_section(
            profile_writer.page_channels(),
            profile_reader.page_channels());

          ChannelsMatcher::copy_history_section(
            profile_writer.url_channels(),
            profile_reader.url_channels());
        }
        else
        {
          Stream::Error ostr;
          ostr << FUN << ": incorrect version: "
            "major_version = " << version_reader.major_version() <<
            "minor_version = " << version_reader.minor_version();
          throw Exception(ostr);
        }

        Generics::MemBuf mb(profile_writer.size());
        profile_writer.save(mb.data(), mb.size());
        membuf.assign(mb.data(), mb.size());

        return Generics::transfer_membuf(result_mem_buf);
      }

      return ReferenceCounting::add_ref(mem_buf);
    }
  }
}
