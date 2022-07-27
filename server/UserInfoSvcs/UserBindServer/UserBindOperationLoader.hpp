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
#ifndef USERBINDSERVER_USERBINDOPERATIONLOADER_HPP
#define USERBINDSERVER_USERBINDOPERATIONLOADER_HPP

#include <eh/Exception.hpp>

#include <ReferenceCounting/ReferenceCounting.hpp>
#include <ReferenceCounting/AtomicImpl.hpp>
#include <Logger/Logger.hpp>

#include <Generics/CompositeActiveObject.hpp>

#include "UserBindOperationSaver.hpp"

namespace AdServer
{
namespace UserInfoSvcs
{
  // UserBindOperationLoader
  class UserBindOperationLoader:
    public virtual ReferenceCounting::AtomicImpl,
    public virtual Generics::CompositeActiveObject
  {
  public:
    DECLARE_EXCEPTION(Exception, eh::DescriptiveException);

    typedef std::set<unsigned long> ChunkIdSet;

    UserBindOperationLoader(
      Generics::ActiveObjectCallback* callback,
      UserBindProcessor* user_bind_processor,
      const char* folder,
      const char* unprocessed_folder,
      const char* file_prefix,
      const Generics::Time& check_period,
      std::size_t threads_count,
      const ChunkIdSet& chunk_ids)
      noexcept;

  protected:
    virtual
    ~UserBindOperationLoader() noexcept;
  };

  typedef ReferenceCounting::SmartPtr<UserBindOperationLoader>
    UserBindOperationLoader_var;
}
}

#endif /*USERBINDSERVER_USERBINDOPERATIONLOADER_HPP*/
