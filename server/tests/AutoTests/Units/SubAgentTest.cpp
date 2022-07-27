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
#include "SubAgentTest.hpp"

REFLECT_UNIT(SubAgentTest) (
  "Meta",
  AUTO_TEST_FAST);

typedef AutoTest::AdClient AdClient;
typedef AutoTest::NSLookupRequest NSLookupRequest;

void
SubAgentTest::exec_cmd(const char* function)
{
  std::string tag = fetch_string("TAG");

  AutoTest::ShellCmd cmd;
  cmd.add_cmd_i("SubAgent-Shell-AdServer.functions.test");
  cmd.add_cmd_i("--index");
  cmd.add_cmd_i("0");//
  cmd.add_cmd_i("--host_name");
  std::string host =
    get_config().check_service(CTE_ALL_REMOTE, STE_FRONTEND)?
      get_config().get_service(CTE_ALL_REMOTE, STE_FRONTEND).address:
        get_config().get_service(CTE_ALL, STE_FRONTEND).address;
  size_t pos = host.find("http://");
  if (pos != std::string::npos)
  {
    host.replace(pos, 7, "");
  }
  cmd.add_cmd_i(host);
  cmd.add_cmd_i("--tag_id");
  cmd.add_cmd_i(tag);
  cmd.add_cmd_i("--country");
  cmd.add_cmd_i("gn");
  cmd.add_cmd_i("--function");
  cmd.add_cmd_i(function);
  cmd.add_cmd_i("--debug");
  cmd.log(AutoTest::Logger::thlog(), Logging::Logger::DEBUG, true);
}

bool
SubAgentTest::run_test()
{
  AdClient client(AdClient::create_user(this));
  NSLookupRequest request;
  request.tid = fetch_string("TAG");
  request.referer_kw = fetch_string("KEYWORD");
  request.referer = fetch_string("URL");
  request.format.clear();
 
  client.process_request(request);
 
  std::string cc = fetch_string("CC");
  FAIL_CONTEXT(
    AutoTest::equal_checker(
      cc,
      client.debug_info.ccid).check(),
    "must select expected creative");

  request.referer.clear();
  client.process_request(request);
  
  FAIL_CONTEXT(
    AutoTest::predicate_checker(
      client.debug_info.selected_creatives.empty()),
    "must not select expected creative");

  exec_cmd("adServerMonitoringProfilingRequestMIB");
  exec_cmd("adServerMonitoringAdRequestMIB");

  return true;
}

