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
#ifndef _USER_INFO_SVCS_USER_INFO_CONTAINER_TEST_APPLICATION_HPP_
#define _USER_INFO_SVCS_USER_INFO_CONTAINER_TEST_APPLICATION_HPP_

#include <map>
#include <set>
#include <string>

#include <ReferenceCounting/ReferenceCounting.hpp>

#include <eh/Exception.hpp>

#include <Logger/Logger.hpp>
#include <Generics/ActiveObject.hpp>
#include <Generics/Singleton.hpp>
#include <Sync/SyncPolicy.hpp>
#include <Generics/Scheduler.hpp>
#include <Generics/TaskRunner.hpp>
#include <Generics/Time.hpp>
#include <Logger/FileLogger.hpp>
#include <Logger/StreamLogger.hpp>

#include "UserInfoContainerTest.hpp"

const unsigned long SESSION_TIMEOUT = 43200;

typedef std::map<std::string, std::string> Args;

typedef std::unique_ptr<
  xsd::AdServer::Configuration::TestConfigurationType> TestConfigPtr;
typedef std::unique_ptr<
  xsd::AdServer::Configuration::UserInfoContainerTestConfigType> UICConfigPtr;
typedef std::unique_ptr<
  xsd::AdServer::Configuration::ChannelRulesType> ChannelRulesConfigPtr;

using namespace AdServer::UserInfoSvcs;

class Application_
{
public:
  DECLARE_EXCEPTION(Exception, eh::DescriptiveException);

  Application_() noexcept;

  virtual ~Application_() noexcept;

  void main(int& argc, char** argv) noexcept;

protected:
  void parse_args(unsigned long count, char** argv, Args& args)
    /*throw(eh::Exception)*/;

  static void find_required_argument(
    const Args& args,
    const char* argument_name,
    std::string& argument_value) /*throw(eh::Exception)*/;

  Logging::Logger_var logger_;
  UICConfigPtr uic_config_;
  ChannelRulesConfigPtr channels_config_;

//  xsd::AdServer::Configuration::ChannelRulesType ch_config_;
  
  
};

typedef Generics::Singleton<Application_> Application;

#endif 
