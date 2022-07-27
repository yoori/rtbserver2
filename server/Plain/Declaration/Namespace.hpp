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
#ifndef _NAMESPACE_HPP_
#define _NAMESPACE_HPP_

#include <list>
#include <map>
#include <eh/Exception.hpp>
#include <ReferenceCounting/AtomicImpl.hpp>
#include "BaseType.hpp"

namespace Declaration
{
  class NamePath: public std::list<std::string>
  {
  public:
    DECLARE_EXCEPTION(InvalidName, eh::DescriptiveException);
    
    NamePath(const char* abs_path, bool name_is_local = false)
      /*throw(InvalidName)*/;

    std::string str() const noexcept;
  };

  class Namespace;

  typedef ReferenceCounting::SmartPtr<Namespace> Namespace_var;

  class Namespace: public virtual ReferenceCounting::AtomicImpl
  {
  public:
    DECLARE_EXCEPTION(AlreadyDefined, eh::DescriptiveException);

    typedef std::map<std::string, BaseType_var>
      BaseTypeMap;

    typedef std::map<std::string,
      ReferenceCounting::SmartPtr<Namespace> >
      NamespaceMap;
    
  public:
    Namespace(
      const char* name_val = 0,
      Namespace* owner_val = 0)
      noexcept;

    const char* name() const noexcept;

    NamePath abs_name() const noexcept;

    Namespace_var owner() const noexcept;

    const BaseTypeMap& types() const noexcept;

    const NamespaceMap& namespaces() const noexcept;

    BaseType_var find_type(const NamePath& name) const noexcept;

    BaseType_var find_local_type(const char* name) const noexcept;

    ReferenceCounting::SmartPtr<Namespace>
    add_namespace(const char* name) noexcept;

    void add_type(BaseType*) /*throw(AlreadyDefined)*/;

  private:
    virtual ~Namespace() noexcept {}
    
    BaseType_var local_find_type_(const NamePath& name) const noexcept;
    
  private:
    std::string name_;
    Namespace* owner_;
    BaseTypeMap types_;
    NamespaceMap namespaces_;
  };

  typedef ReferenceCounting::SmartPtr<Namespace>
    Namespace_var;
}

#endif /*_NAMESPACE_HPP_*/
