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
#ifndef COMMONS_CORBACONFIGREADER_HPP
#define COMMONS_CORBACONFIGREADER_HPP

#include <CORBACommons/CorbaAdapters.hpp>


namespace CORBAConfigParser
{
  class CorbaConfigReader
  {
  public:
    DECLARE_EXCEPTION(Exception, eh::DescriptiveException);

    static
    void
    read_server_config(DOMNode* node, CORBACommons::CorbaConfig& corba_config,
      const char* xml_namespace) /*throw (eh::Exception, Exception)*/;

    static
    void
    read_client_config(DOMNode* node,
      CORBACommons::CorbaClientConfig& corba_config,
      const char* xml_namespace)
      /*throw (eh::Exception, Exception)*/;

    static
    void
    read_corba_ref(DOMNode* node,
      CORBACommons::CorbaObjectRef& corba_object_ref,
      std::string& object_name, const char* xml_namespace)
      /*throw (eh::Exception, Exception)*/;

    static
    void
    read_corba_connection(DOMNode* node,
      CORBACommons::CorbaObjectRef& corba_object_ref,
      std::string& object_name, const char* xml_namespace)
      /*throw (eh::Exception, Exception)*/;

  protected:
    static
    void
    read_endpoint(DOMNode* node,
      CORBACommons::EndpointConfig& endpoint_config,
      const char* xml_namespace)
      /*throw (eh::Exception, Exception)*/;

    static
    void
    read_secure_params(DOMNode* node,
      CORBACommons::SecureConnectionConfig& secure_connection_config)
      /*throw (eh::Exception, Exception)*/;
  };
}

#endif
