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
#ifndef EXPRESSIONMATCHER_USERCOLOREACHCONTAINER_HPP
#define EXPRESSIONMATCHER_USERCOLOREACHCONTAINER_HPP

#include <eh/Exception.hpp>
#include <ReferenceCounting/ReferenceCounting.hpp>

#include <Logger/Logger.hpp>
#include <Generics/Time.hpp>
#include <Generics/MemBuf.hpp>

#include <Commons/Algs.hpp>
#include <ProfilingCommons/ProfileMap/ProfileMapFactory.hpp>
#include <ProfilingCommons/PlainStorageAdapters.hpp>

#include "ColoReachProcessor.hpp"

namespace AdServer
{
  namespace RequestInfoSvcs
  {
    class UserColoReachContainer:
      public Generics::CompositeActiveObject,
      public ReferenceCounting::AtomicImpl
    {
    public:
      DECLARE_EXCEPTION(Exception, eh::DescriptiveException);

    public:
      struct RequestInfo
      {
        AdServer::Commons::UserId user_id;
        Generics::Time time;
        Generics::Time isp_time;
        unsigned long colo_id;
      };

      UserColoReachContainer(
        Logging::Logger* logger,
        ColoReachProcessor* colo_reach_processor,
        bool household,
        unsigned long common_chunks_number,
        const AdServer::ProfilingCommons::ProfileMapFactory::ChunkPathMap& chunk_folders,
        const char* file_prefix,
        ProfilingCommons::ProfileMapFactory::Cache* cache,
        const AdServer::ProfilingCommons::LevelMapTraits& user_level_map_traits)
        /*throw(Exception)*/;

      Generics::ConstSmartMemBuf_var
      get_profile(const AdServer::Commons::UserId& user_id)
        /*throw(Exception)*/;

      virtual void
      process_request(const RequestInfo& request_info)
        /*throw(Exception)*/;

      void clear_expired() /*throw(Exception)*/;

    protected:
      typedef std::list<ColoReachProcessor::ColoReachInfo>
        ColoReachInfoList;

    protected:
      virtual ~UserColoReachContainer() noexcept
      {}

      void
      process_request_trans_(
        ColoReachInfoList& gmt_colo_reach_info_list,
        ColoReachInfoList& isp_colo_reach_info_list,
        const RequestInfo& request_info)
        /*throw(Exception)*/;

    private:
      typedef AdServer::ProfilingCommons::ChunkedProfileMap<
        AdServer::Commons::UserId,
        AdServer::ProfilingCommons::TransactionProfileMap<AdServer::Commons::UserId>,
        unsigned long (*)(const Generics::Uuid& uuid) >
      UserInfoMap;

      typedef ReferenceCounting::SmartPtr<UserInfoMap>
        UserInfoMap_var;

    private:
      Logging::Logger_var logger_;
      ColoReachProcessor_var colo_reach_processor_;
      const bool HOUSEHOLD_;

      Generics::Time expire_time_;
      UserInfoMap_var user_map_;      
    };

    typedef ReferenceCounting::SmartPtr<UserColoReachContainer>
      UserColoReachContainer_var;
  }
}

#endif /*EXPRESSIONMATCHER_USERCOLOREACHCONTAINER_HPP*/
