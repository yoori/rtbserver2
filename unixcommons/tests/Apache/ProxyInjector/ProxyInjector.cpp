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

#include "ProxyInjector.hpp"

namespace
{
  const char TEXT_TO_INSERT[] = "<!-- Hey, I'm the text inserted into page -->";
}

ProxyInjectorModule::ProxyInjectorModule() /*throw (eh::Exception)*/
  : Apache::InsertFilterHook<ProxyInjectorModule>(APR_HOOK_MIDDLE)
{
  std::cerr << "In ProxyInjectorModule::ProxyInjectorModule().\n";
}

ProxyInjectorModule::~ProxyInjectorModule() throw ()
{
}

void
ProxyInjectorModule::insert_filter(request_rec* r) throw ()
{
  try
  {
    new InjectorFilter(r);
  }
  catch (...)
  {
  }
}

//
// class InjectorFilter
//

ProxyInjectorModule::InjectorFilter::InjectorFilter(request_rec* r) throw ()
  : RequestOutputFilter(AP_FTYPE_RESOURCE, r, r->connection),
    bb_(0)
{
}

apr_status_t
ProxyInjectorModule::InjectorFilter::filter(
  ap_filter_t* f, apr_bucket_brigade* bb) throw ()
{
  request_rec* r = f->r;

  if (!bb_)
  {
    bb_ = apr_brigade_create(r->pool, f->c->bucket_alloc);

    // update ContentLength
    apr_table_unset(r->headers_out, "Content-Length");
  }

  apr_bucket* e;
  for (e = APR_BRIGADE_FIRST(bb); e != APR_BRIGADE_SENTINEL(bb); e = APR_BUCKET_NEXT(e))
  {
    if (APR_BUCKET_IS_EOS(e))
    {
      // insert bucket with text
      char* buf = apr_pstrdup(r->pool, TEXT_TO_INSERT);

      apr_bucket* text_bucket =
        apr_bucket_pool_create(buf, strlen(TEXT_TO_INSERT),
                               r->pool, f->c->bucket_alloc);
      APR_BRIGADE_INSERT_TAIL(bb_, text_bucket);

      APR_BUCKET_REMOVE(e);
      APR_BRIGADE_INSERT_TAIL(bb_, e);

      return pass_brigade(bb_);
    }

    if (APR_BUCKET_IS_FLUSH(e))
    {
      APR_BUCKET_REMOVE(e);
      APR_BRIGADE_INSERT_TAIL(bb_, e);
      pass_brigade(bb_);
      continue;
    }

    apr_bucket* cpy;
    apr_bucket_copy(e, &cpy);
    APR_BRIGADE_INSERT_TAIL(bb_, cpy);
  }

  return APR_SUCCESS;
}

ProxyInjectorModule::ProxyInjectorModule_var ProxyInjectorModule::instance(
  new ProxyInjectorModule);

Apache::ModuleDef<ProxyInjectorModule> proxy_injector_module;
