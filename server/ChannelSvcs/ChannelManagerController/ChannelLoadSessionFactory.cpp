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
#include <list>
#include <vector>
#include <set>
#include <iterator>
#include <time.h>

#include <String/StringManip.hpp>
#include <Generics/Statistics.hpp>
#include <Generics/TaskRunner.hpp>
#include <Logger/Logger.hpp>
#include <Logger/StreamLogger.hpp>
#include <ReferenceCounting/ReferenceCounting.hpp>
#include <ReferenceCounting/DefaultImpl.hpp>
#include <ReferenceCounting/SmartPtr.hpp>
#include <CORBACommons/CorbaAdapters.hpp>
#include <CORBACommons/ServantImpl.hpp>
#include <Commons/CorbaAlgs.hpp>
#include <ChannelSvcs/ChannelServer/ChannelLoadSessionImpl.hpp>

#include "ChannelLoadSessionFactory.hpp"
#include "ChannelSessionFactory.hpp"
#include "ThreadHandlerTemplate.hpp"

const char* ChannelLoadSessionFactoryImpl::ASPECT =
  "ChannelLoadSessionFactoryImpl";

/**
 * ChannelLoadSessionFactoryImpl
 */

ChannelLoadSessionFactoryImpl::ChannelLoadSessionFactoryImpl(
    unsigned long count_threads,
    Generics::ActiveObjectCallback* callback) noexcept
  : callback_(ReferenceCounting::add_ref(callback)),
    task_runner_(new Generics::TaskRunner(callback_, count_threads))
{
  try
  {
    add_child_object(task_runner_);
    activate_object();
  }
  catch(const eh::Exception& e)
  {
    if(callback_)
    {
      Stream::Error ostr;
      ostr << __func__ << ": eh::Exception: " << e.what();
      callback_->critical(ostr.str(), "ADS-IMPL-600");
    }
  }
}

ChannelLoadSessionFactoryImpl::~ChannelLoadSessionFactoryImpl() noexcept
{
}

CORBA::ValueBase* ChannelLoadSessionFactoryImpl::create_for_unmarshal()
{
  try
  {
    return new ::AdServer::ChannelSvcs::ChannelLoadSessionImpl(
      callback_, task_runner_.in());
  }
  catch(const eh::Exception& e)
  {
    if(callback_)
    {
      Stream::Error ostr;
      ostr << __func__ << ": eh::Exception: " << e.what();
      callback_->critical(ostr.str(), "ADS-IMPL-601");
    }
    throw;
  }
}

void ChannelLoadSessionFactoryImpl::report_error(
    Generics::ActiveObjectCallback::Severity severity,
    const char* description,
    const char* error_code) 
    noexcept
{
  if(callback_)
  {
    Stream::Error ostr;
    ostr << __func__ << ": " << description;
    callback_->report_error(severity, ostr.str(), error_code);
  } 
}

