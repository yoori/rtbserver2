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
#include <iostream>

#include "SlowdownFilter.hpp"

namespace
{
  const char DELAY_PARAM[] = "SlowdownFilter_Delay";
}

SlowdownFilterModule::SlowdownFilterModule() throw ()
  : Apache::InsertFilterHook<SlowdownFilterModule>(APR_HOOK_MIDDLE)
{
  delay_.tv_sec = 0;
  delay_.tv_nsec = 0;
  add_directive(DELAY_PARAM, OR_OPTIONS, TAKE1, DELAY_PARAM);
}

SlowdownFilterModule::~SlowdownFilterModule() throw ()
{
}

void
SlowdownFilterModule::insert_filter(request_rec* r) throw ()
{
  try
  {
    new SlowdownFilter(r, delay_);
  }
  catch (...)
  {
  }
}

//
// class InjectorFilter
//

SlowdownFilterModule::SlowdownFilter::SlowdownFilter(
  request_rec* r, timespec& delay) throw ()
  : RequestOutputFilter(AP_FTYPE_RESOURCE, r, r->connection),
    delay_(delay)
{
}

const char*
SlowdownFilterModule::handle_command(const ConfigArgs& args) throw ()
{
  if (!strcmp(args.name(), DELAY_PARAM))
  {
    long long delay = atoll(args.str1());
    delay_.tv_nsec = (delay % 1000000) * 1000;
    delay_.tv_sec = delay / 1000000;
  }

  return 0;
}

apr_status_t
SlowdownFilterModule::SlowdownFilter::filter(
  ap_filter_t*, apr_bucket_brigade* bb) throw ()
{
  nanosleep(&delay_, 0);
  remove();
  return pass_brigade(bb);
}

SlowdownFilterModule::SlowdownFilterModule_var SlowdownFilterModule::instance(
  new SlowdownFilterModule);

Apache::ModuleDef<SlowdownFilterModule> slowdown_filter_module;
