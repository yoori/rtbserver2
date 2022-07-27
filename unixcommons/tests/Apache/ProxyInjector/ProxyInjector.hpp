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
#ifndef APACHE_PROXY_INJECTOR_HPP
#define APACHE_PROXY_INJECTOR_HPP

#include <ReferenceCounting/ReferenceCounting.hpp>

#include <Apache/Module.hpp>


class ProxyInjectorModule :
  public Apache::InsertFilterHook<ProxyInjectorModule>,
  public ReferenceCounting::AtomicImpl
{
public:
  typedef ReferenceCounting::QualPtr<ProxyInjectorModule>
    ProxyInjectorModule_var;
  static ProxyInjectorModule_var instance;

  class InjectorFilter : public Apache::RequestOutputFilter
  {
  public:
    InjectorFilter(request_rec* r) throw ();
    virtual apr_status_t
    filter(ap_filter_t* f, apr_bucket_brigade* bb) throw ();

  private:
    apr_bucket_brigade* bb_;
  };

public:
  ProxyInjectorModule() /*throw (eh::Exception)*/;

  virtual void
  insert_filter(request_rec* r) throw ();

protected:
  virtual
  ~ProxyInjectorModule() throw ();

private:
  int test_;
};

#endif // _PROXY_INJECTOR_HPP_
