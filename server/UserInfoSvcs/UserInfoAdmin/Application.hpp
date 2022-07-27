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
#ifndef _USER_INFO_SVCS_USER_INFO_ADMIN_APPLICATION_HPP_
#define _USER_INFO_SVCS_USER_INFO_ADMIN_APPLICATION_HPP_

#include <map>
#include <set>
#include <string>

#include <ReferenceCounting/ReferenceCounting.hpp>

#include <eh/Exception.hpp>

#include <Generics/Singleton.hpp>
#include <Generics/Time.hpp>

#include <UserInfoSvcs/UserInfoCommons/ChannelMatcher.hpp>

using namespace AdServer::UserInfoSvcs;

class Application_
{
public:
  DECLARE_EXCEPTION(Exception, eh::DescriptiveException);

  Application_() noexcept;

  virtual ~Application_() noexcept;

  void main(int& argc, char** argv) /*throw(eh::Exception)*/;

protected:
  static void print_plain_(
    std::ostream& ostr,
    const void* buf,
    unsigned long size,
    const char* prefix)
    noexcept;

  static
  void
  tokenize_channels(
    std::set<unsigned long>& matched_channel_ids,
    const String::SubString& matched_channels)
    /*throw (eh::Exception)*/;

  static
  void
  tokenize_channels(
    std::set<ChannelMatch>& matched_channel_ids,
    const String::SubString& matched_channels)
    /*throw (eh::Exception)*/;

  void get_profile_(
    AdServer::UserInfoSvcs::UserInfoMatcher* user_info_matcher,
    const AdServer::Commons::UserId& user_id,
    const AdServer::Commons::UserId& temp_user_id,
    bool print_plain,
    bool print_expand,
    bool print_align,
    unsigned long print_kind)
    noexcept;

  void print_freq_cap_profile_(
    AdServer::UserInfoSvcs::UserInfoMatcher* user_info_matcher,
    const AdServer::Commons::UserId& user_id,
    bool print_plain)
    noexcept;

  void
  match_(
    AdServer::UserInfoSvcs::UserInfoMatcher* user_info_matcher,
    const AdServer::Commons::UserId& user_id,
    const AdServer::Commons::UserId& temp_user_id,
    const String::SubString& opt_time,
    const String::SubString& matched_page_channels,
    const String::SubString& matched_search_channels,
    const String::SubString& matched_url_channels,
    const String::SubString& matched_persistent_channels)
    noexcept;

  void
  remove_user_profile_(
    AdServer::UserInfoSvcs::UserInfoMatcher* user_info_matcher,
    const AdServer::Commons::UserId& user_id)
    noexcept;

  void delete_old_profiles_(
    AdServer::UserInfoSvcs::UserInfoMatcher* user_info_matcher,
    bool sync,
    const Generics::Time& cleanup_time,
    long portion)
    noexcept;
};

typedef Generics::Singleton<Application_> Application;

#endif /*_USER_INFO_SVCS_USER_INFO_ADMIN_APPLICATION_HPP_*/
