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
/**
 * @author Pavel Gubin <pgubin@ipmce.ru>
 */
#ifndef APACHE_SLOWDOWN_FILTER_HPP
#define APACHE_SLOWDOWN_FILTER_HPP

#include <time.h>

#include <ReferenceCounting/ReferenceCounting.hpp>

#include <Apache/Module.hpp>


class SlowdownFilterModule :
  public Apache::ConfigParser,
  public Apache::InsertFilterHook<SlowdownFilterModule>,
  public ReferenceCounting::AtomicImpl
{
public:
  typedef ReferenceCounting::QualPtr<SlowdownFilterModule>
    SlowdownFilterModule_var;
  static SlowdownFilterModule_var instance;

  class SlowdownFilter : public Apache::RequestOutputFilter
  {
  public:
    SlowdownFilter(request_rec* r, timespec& delay) throw ();
    virtual apr_status_t
    filter(ap_filter_t* f, apr_bucket_brigade* bb) throw ();

  private:
    timespec delay_;
  };

public:
  SlowdownFilterModule() throw ();

  virtual const char*
  handle_command(const ConfigArgs& args) throw ();
  virtual void
  insert_filter(request_rec* r) throw ();

protected:
  virtual
  ~SlowdownFilterModule() throw ();

private:
  timespec delay_;
};

#endif
