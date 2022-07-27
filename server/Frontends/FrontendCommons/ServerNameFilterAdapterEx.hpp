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
#ifndef SERVER_NAME_FILTER_ADAPTER_EX_HPP_
#define SERVER_NAME_FILTER_ADAPTER_EX_HPP_

#include <list>

#include <Apache/Adapters.hpp>
#include <Generics/GnuHashTable.hpp>
#include <Commons/Algs.hpp>

namespace Apache
{
  class ServerAction : public ReferenceCounting::AtomicImpl
  {
  public:
    virtual int
    execute(
      const HttpRequest& request,
      HttpResponse& response,
      int status) const noexcept = 0;

  protected:
    virtual
    ~ServerAction() noexcept
    {}
  };

  /**
   * Extends ServerNameFilterAdapter using prev and post optional actions
   */
  template <typename ModuleType, typename HttpResponse = Apache::HttpResponse>
  class ServerNameFilterAdapterEx:
    public QuickHandlerHook<ModuleType>
  {
  public:
    typedef ReferenceCounting::SmartPtr<ServerAction> ServerAction_var;
    typedef std::list<ServerAction_var> ServerActions;

    struct ServerRec
    {
    public:
      ServerActions prev;
      ServerActions post;
    };

  public:
    ServerNameFilterAdapterEx(int where = APR_HOOK_LAST) noexcept;

    void
    add_module_server(const server_rec* server) noexcept;

    bool
    module_used() const noexcept;

    virtual int
    quick_handler(request_rec* r, int) noexcept;

    void
    add_prev(const server_rec* server, ServerAction* action) noexcept;

    void
    add_post(const server_rec* server, ServerAction* action) noexcept;

    virtual bool
    will_handle(const char* uri) noexcept = 0;

    virtual int
    handle_request(const HttpRequest& request, HttpResponse& response)
      noexcept = 0;

  protected:
    virtual
    ~ServerNameFilterAdapterEx() noexcept
    {}

    int
    handle_request_noparams_(
      const ServerRec& server,
      HttpRequest& request,
      HttpResponse& response)
      /*throw (eh::Exception)*/;

  private:
    typedef Generics::GnuHashTable<
      Algs::ConstPointerHashAdapter<server_rec>,
      ServerRec> Servers;

  private:
    Servers hosts_;
  };
}

namespace Apache
{
  template<typename ModuleType, typename HttpResponse>
  ServerNameFilterAdapterEx<ModuleType, HttpResponse>::
  ServerNameFilterAdapterEx(int where)
    noexcept
    : QuickHandlerHook<ModuleType>(where)
  {}

  template<typename ModuleType, typename HttpResponse>
  void
  ServerNameFilterAdapterEx<ModuleType, HttpResponse>::
    add_module_server(const server_rec* server)
    noexcept
  {
    hosts_.insert(std::make_pair(server, ServerRec()));
  }

  template<typename ModuleType, typename HttpResponse>
  bool
  ServerNameFilterAdapterEx<ModuleType, HttpResponse>::module_used() const
    noexcept
  {
    return !hosts_.empty();
  }

  template<typename ModuleType, typename HttpResponse>
  void
  ServerNameFilterAdapterEx<ModuleType, HttpResponse>::
    add_prev(const server_rec* server, ServerAction* action) noexcept
  {
    typename Servers::iterator ci = hosts_.find(server);

    if (ci != hosts_.end())
    {
      ci->second.prev.push_back(ReferenceCounting::add_ref(action));
    }
  }

  template<typename ModuleType, typename HttpResponse>
  void
  ServerNameFilterAdapterEx<ModuleType, HttpResponse>::
    add_post(const server_rec* server, ServerAction* action) noexcept
  {
    typename Servers::iterator ci = hosts_.find(server);

    if (ci != hosts_.end())
    {
      ci->second.post.push_back(ReferenceCounting::add_ref(action));
    }
  }

  template<typename ModuleType, typename HttpResponse>
  int
  ServerNameFilterAdapterEx<ModuleType, HttpResponse>::
    quick_handler(request_rec* r, int)
    noexcept
  {
    switch (r->method_number)
    {
    case M_GET:
    case M_POST:
    case M_PUT:
      break;

    default:
      return DECLINED;
    }

    const typename Servers::const_iterator ci = hosts_.find(r->server);

    if (ci == hosts_.end() ||
       !will_handle(r->uri))
    {
      return DECLINED;
    }

    try
    {
      HttpRequest request(r);
      HttpResponse response(r);
      return handle_request_noparams_(ci->second, request, response);
    }
    catch (const HttpRequest::Exception& e)
    {
      ap_log_error(APLOG_MARK, APLOG_WARNING, 0, r->server, e.what());

      return e.error_code();
    }
    catch (const eh::Exception& e)
    {
      ap_log_error(APLOG_MARK, APLOG_WARNING, 0, r->server, e.what());

      return HTTP_INTERNAL_SERVER_ERROR;
    }
  }

  template<typename ModuleType, typename HttpResponse>
  int
  ServerNameFilterAdapterEx<ModuleType, HttpResponse>::
    handle_request_noparams_(
      const ServerRec& server,
      HttpRequest& request,
      HttpResponse& response)
      /*throw (eh::Exception)*/
  {
    HTTP::ParamList params;

    if (request.args())
    {
      HttpRequest::parse_params(String::SubString(request.args()), params);
    }

    if (!request.body().empty())
    {
      HttpRequest::parse_params(request.body(), params);
    }

    request.set_params(std::move(params));

    for (ServerActions::const_iterator ci = server.prev.begin();
         ci != server.prev.end(); ++ci)
    {
      const int status = (*ci)->execute(request, response, OK);

      if (status != OK)
      {
        return status;
      }
    }

    const int status = handle_request(request, response);

    for (ServerActions::const_iterator ci = server.post.begin();
         ci != server.post.end(); ++ci)
    {
      (*ci)->execute(request, response, status);
    }

    return status;
  }
}

#endif /*SERVER_NAME_FILTER_ADAPTER_EX_HPP_*/
