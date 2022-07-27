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
#ifndef _AD_SERVER_CHANNEL_SEARCH_SVCS_CHANNEL_SEARCH_ADMIN_APPLICATION_HPP_
#define _AD_SERVER_CHANNEL_SEARCH_SVCS_CHANNEL_SEARCH_ADMIN_APPLICATION_HPP_

#include <eh/Exception.hpp>

#include <Generics/Singleton.hpp>

#include <ChannelSearchSvcs/ChannelSearchService/ChannelSearchService.hpp>

/**
 * \class Application
 * Performs request to the channel search service and outputs result into std output.
 */
class Application
{
public:

  /**
   * Macros defining Application base exception class.
   */
  DECLARE_EXCEPTION(Exception, eh::DescriptiveException);

  /**
   * Macros defining InvalidArgument exception class.
   */
  DECLARE_EXCEPTION(InvalidArgument, Exception);

public:

  /**
   * Construct Application object.
   */
  Application() /*throw(Exception, eh::Exception)*/;

  /**
   * Destructs Application object.
   */
  virtual ~Application() noexcept;

/**
 * Parses arguments and issues corresponding request to ChannelSearchService.
 * @param argc Number of arguments passed to utility process
 * @param argv Arguments passed to utility process
 */
  int run(int& argc, char** argv)
    /*throw(InvalidArgument, Exception, eh::Exception, CORBA::Exception)*/;

/**
 * Returns pointer to singleton object.
 */
  static Application* instance() /*throw(eh::Exception)*/;

  typedef
    AdServer::ChannelSearchSvcs::ChannelSearchResultSeq_var
      ResultSeq_var;

  typedef
    AdServer::ChannelSearchSvcs::ChannelSearchResultSeq
      ResultSeq;

  int help()
    /*throw(InvalidArgument, Exception, eh::Exception, CORBA::Exception)*/;

  ResultSeq *search(const char *phrase)
    /*throw(InvalidArgument, Exception, eh::Exception, CORBA::Exception)*/;

  void print_result(const ResultSeq &result)
    /*throw(InvalidArgument, Exception, eh::Exception, CORBA::Exception)*/;

  void print_match_result(
    const AdServer::ChannelSearchSvcs::MatchInfo& result)
    /*throw(Exception, eh::Exception, CORBA::Exception)*/;

private:
  CORBA::ORB_var orb_;
  AdServer::ChannelSearchSvcs::ChannelSearch_var channel_search_;
};

/**
 * Defines singleton class.
 */
typedef Generics::Singleton<Application> AppSingleton;

///////////////////////////////////////////////////////////////////////////////
// Inlines
///////////////////////////////////////////////////////////////////////////////

//
// Application class
//
inline
Application*
Application::instance() /*throw(eh::Exception)*/
{
  return &AppSingleton::instance();
}

#endif // _AD_SERVER_CHANNEL_SEARCH_SVCS_CHANNEL_SEARCH_ADMIN_APPLICATION_HPP_

