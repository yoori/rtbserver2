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

#ifndef _AD_SERVER_LOG_PROCESSING_SYNCLOGS_MAIN_HPP_
#define _AD_SERVER_LOG_PROCESSING_SYNCLOGS_MAIN_HPP_

#include <vector>

#include <eh/Exception.hpp>

#include <Generics/Singleton.hpp>

#include <Commons/ProcessControlVarsImpl.hpp>
#include <Commons/CorbaConfig.hpp>
#include <LogProcessing/SyncLogsConfig.hpp>

#include "SyncLogsImpl.hpp"

/**
 * Parses command line parameters, loads configuration file,
 * runs orb, creates corba objects, etc.
 * Responsible for general configuration, logging and error handling.
 */
class SyncLogsApp_:
  public AdServer::Commons::ProcessControlVarsLoggerImpl
{
public:
  DECLARE_EXCEPTION(Exception, eh::DescriptiveException);

  SyncLogsApp_() /*throw(eh::Exception)*/;

  /**
   * Parses command line, opens config file,
   * creates corba objects, initialize.
   */
  void main(int &argc, char **argv) noexcept;

  //
  // IDL:CORBACommons/IProcessControl/shutdown:1.0
  //
  virtual void shutdown(CORBA::Boolean wait_for_completion)
    noexcept;

  //
  // IDL:CORBACommons/IProcessControl/is_alive:1.0
  //
  virtual CORBACommons::IProcessControl::ALIVE_STATUS
  is_alive() noexcept;

private:
  virtual ~SyncLogsApp_() noexcept {}
  struct LoggerConfig
  {
    std::string filename;
    Logging::File::Policies::PolicyList policies;
    unsigned int log_level;
  };

private:

  // Reads configuration from config XML tree.
  void read_config(const char *filename, const char* argv0)
    /*throw(Exception, eh::Exception)*/;

  void init_corba() /*throw(Exception)*/;

  AdServer::LogProcessing::SyncLogsImpl::ConfigurationPtr configuration_;
  CORBACommons::CorbaServerAdapter_var corba_server_adapter_;
  CORBACommons::CorbaConfig corba_config_;

  AdServer::LogProcessing::SyncLogsImpl_var sync_logs_impl_;

  typedef Sync::Policy::PosixThread SyncPolicy;
  typedef SyncPolicy::Mutex ShutdownMutex;
  typedef SyncPolicy::WriteGuard ShutdownGuard;

  ShutdownMutex shutdown_lock_;
};

typedef ReferenceCounting::QualPtr<SyncLogsApp_> SyncLogsApp_var;

typedef Generics::Singleton<SyncLogsApp_, SyncLogsApp_var> SyncLogsApp;

#endif // _AD_SERVER_LOG_PROCESSING_SYNCLOGS_MAIN_HPP_

