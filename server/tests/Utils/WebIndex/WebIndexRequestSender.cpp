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
#include <map>

#include <iostream>
#include <Generics/AppUtils.hpp>
#include <Generics/Uuid.hpp>
#include <Generics/Rand.hpp>
#include <Logger/StreamLogger.hpp>
#include <Logger/ActiveObjectCallback.hpp>

#include <RequestInfoSvcs/RequestInfoManager/TagRequestProfiler.hpp>

using namespace AdServer::RequestInfoSvcs;
using AdServer::Commons::UserId;
using AdServer::Commons::RequestId;

namespace
{
  const char USAGE[] =
    "WebIndexRequestSender [ADDRESS] [OPTIONS]\n"
    "OPTIONS:\n"
    "  -pk, --private-key : path to key for uid sign.\n"
    "  -u, --uid, --user-id : unsigned user id.\n"
    "  -l, --url : url.\n"
    "  -h, --help : show this message.\n";
}

int
main(int argc, char* argv[]) noexcept
{
  try
  {
    using namespace Generics::AppUtils;

    CheckOption opt_help;
    StringOption opt_private_key;
    StringOption opt_user_id;
    StringOption opt_url;
    OptionsSet<TagRequestProfiler::AddressList> opt_addresses;

    Args args;
    args.add(equal_name("private-key") || short_name("pk"), opt_private_key);
    args.add(equal_name("uid") || equal_name("user-id") || short_name("u"), opt_user_id);
    args.add(equal_name("url") || short_name("l"), opt_url);
    args.add(equal_name("help") || short_name("h"), opt_help);
    args.add(equal_name("ref") || short_name("r"), opt_addresses);

    args.parse(argc - 1, argv + 1);

    if (opt_help.enabled())
    {
      std::cerr << USAGE << std::endl;
      return 0;
    }

    if(!opt_private_key.installed())
    {
      std::cerr << "private key must be defined" << std::endl;
      return 1;
    }

    if(!opt_addresses.installed())
    {
      std::cerr << "one address must be defined" << std::endl;
      return 1;
    }

    if(!opt_url.installed())
    {
      std::cerr << "URL must be defined" << std::endl;
      return 1;
    }

    // prepare
    TagRequestInfo tag_request_info;
    tag_request_info.time = Generics::Time::get_time_of_day();
    tag_request_info.colo_id = 1;
    tag_request_info.tag_id = 2;
    tag_request_info.user_status = 'I';
    tag_request_info.referer = *opt_url;
    tag_request_info.isp_time = tag_request_info.time;
    tag_request_info.site_id = 1;
    tag_request_info.user_id =
      opt_user_id.installed() ? AdServer::Commons::UserId(opt_user_id->c_str()) :
      AdServer::Commons::UserId::create_random_based();
    tag_request_info.ad_shown = false;
    tag_request_info.profile_referer = true;
    tag_request_info.request_id =
      AdServer::Commons::RequestId::create_random_based();

    // send webindex request
    Logging::Logger_var logger = new Logging::OStream::Logger(
      Logging::OStream::Config(std::cerr));

    Logging::ActiveObjectCallbackImpl_var callback(
      new Logging::ActiveObjectCallbackImpl(
        logger,
        "WebIndexRequestSender::main()",
        "WebIndexRequestSender",
        ""));

    /*
    TagRequestProfiler_var sender = new TagRequestProfiler(
      callback,
      1,
      Generics::Time::ONE_SECOND,
      0,
      opt_private_key->c_str(),
      *opt_addresses);

    sender->activate_object();

    sender->process_tag_request(tag_request_info);

    sleep(1); // wait zm

    sender->deactivate_object();
    sender->wait_object();
    */

    TagRequestProfiler_var sender = new TagRequestProfiler(
      logger,
      callback,
      1,
      Generics::Time::ONE_MINUTE,
      30000,
      opt_private_key->c_str(),
      *opt_addresses,
      Generics::Time::ZERO);

    sender->activate_object();
    std::cerr << Generics::Time::get_time_of_day().get_gm_time().format("%F %T") <<
      ": start" << std::endl;

    /*
    sleep(60);

    for(int i = 0; i < 6; ++i)
    {
      for(int i = 0; i < 100; ++i)
      {
        sender->process_tag_request(tag_request_info);
      }

      sleep(10);
    }
    */

    for(int i = 0; i < 10000; ++i)
    {
      sender->process_tag_request(tag_request_info);
    }

    sleep(30);

    for(int i = 0; i < 10000; ++i)
    {
      sender->process_tag_request(tag_request_info);
    }

    sleep(160); // wait zm

    sender->deactivate_object();
    sender->wait_object();

    return 0;
  }
  catch (const eh::Exception& ex)
  {
    std::cerr << ex.what() << std::endl;
  }

  return -1;
}
