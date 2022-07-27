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
#ifndef _UTILS_PROFILEDUMP_HPP_
#define _UTILS_PROFILEDUMP_HPP_

#include <map>
#include <set>
#include <string>

#include <ReferenceCounting/ReferenceCounting.hpp>

#include <eh/Exception.hpp>

#include <Generics/Singleton.hpp>
#include <Generics/Time.hpp>
#include <ProfilingCommons/ProfileMap/ProfileMapFactory.hpp>

using namespace AdServer::UserInfoSvcs;

class Application_
{
public:
  DECLARE_EXCEPTION(Exception, eh::DescriptiveException);

  Application_() noexcept;

  virtual ~Application_() noexcept;

  void main(int& argc, char** argv) /*throw(eh::Exception)*/;

protected:
  typedef std::list<std::string> FileNameList;

  enum ProfileType
  {
    PT_BASE,
    PT_ADD,
    PT_HISTORY,
    PT_ACTION,
    PT_CAMPAIGNREACH,
    PT_INVENTORY,
    PT_REQUEST
  };

protected:
  static void
  print_profile_(
    ProfileType type,
    const char* user_id,
    const FileNameList& files)
    /*throw (eh::Exception)*/;

  static void
  print_plain_(
    std::ostream& ostr,
    const void* buf,
    unsigned long size,
    const char* prefix)
    noexcept;

  static void
  print_profile_from_file_(
    ProfileType type,
    const char* user_id,
    const char* filename)
    /*throw (eh::Exception)*/;

  static void
  print_profile_from_block_(
    ProfileType type,
    const char* user_id,
    const Generics::MemBuf& buf)
    noexcept;

  static void
  dump_request_profiles_(const FileNameList& files) noexcept;
};

typedef Generics::Singleton<Application_> Application;

#endif /*_UTILS_PROFILEDUMP_HPP_*/
