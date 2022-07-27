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
#ifndef _LOG_PROCESSING_EXPRESSION_MATCHER_ADMIN_APPLICATION_HPP_
#define _LOG_PROCESSING_EXPRESSION_MATCHER_ADMIN_APPLICATION_HPP_

#include <map>
#include <set>
#include <string>

#include <eh/Exception.hpp>
#include <Generics/Time.hpp>
#include <Generics/Singleton.hpp>

#include <CORBACommons/CorbaAdapters.hpp>
#include <RequestInfoSvcs/ExpressionMatcher/ExpressionMatcher.hpp>

class Application_
{
public:
  DECLARE_EXCEPTION(Exception, eh::DescriptiveException);

  Application_() noexcept;

  virtual ~Application_() noexcept;

  void main(int& argc, char** argv) noexcept;

protected:
  AdServer::RequestInfoSvcs::ExpressionMatcher*
  resolve_expression_matcher(
    const CORBACommons::CorbaClientAdapter* corba_client_adapter,
    const CORBACommons::CorbaObjectRef& corba_ref)
    /*throw (eh::Exception, Exception, CORBA::SystemException)*/;

  void print(
    AdServer::RequestInfoSvcs::ExpressionMatcher* expression_matcher,
    const char* user_id_str)
    noexcept;

  void print_estimation(
    AdServer::RequestInfoSvcs::ExpressionMatcher* expression_matcher,
    const char* user_id_str)
    noexcept;

  void print_user_trigger_match(
    AdServer::RequestInfoSvcs::ExpressionMatcher* expression_matcher,
    const char* user_id_str,
    bool temporary)
    noexcept;

  void print_request_trigger_match(
    AdServer::RequestInfoSvcs::ExpressionMatcher* expression_matcher,
    const char* user_id_str)
    noexcept;

  void
  print_household_colo_reach(
    AdServer::RequestInfoSvcs::ExpressionMatcher* expression_matcher,
    const char* user_id_str)
    noexcept;
};

typedef Generics::Singleton<Application_> Application;

#endif /*_LOG_PROCESSING_EXPRESSION_MATCHER_ADMIN_APPLICATION_HPP_*/
