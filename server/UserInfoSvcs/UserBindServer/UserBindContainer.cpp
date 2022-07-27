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
#include <Generics/Time.hpp>
#include <PrivacyFilter/Filter.hpp>
#include <Generics/DirSelector.hpp>
#include <Generics/Rand.hpp>
#include <String/RegEx.hpp>

#include <Commons/Algs.hpp>
#include <LogCommons/LogCommons.hpp>
#include <LogCommons/LogCommons.ipp>

#include "UserBindContainer.hpp"

namespace Aspect
{
  const char USER_BIND_CONTAINER[] = "UserBindContainer";
}

namespace AdServer
{
namespace UserInfoSvcs
{
  // UserBindContainer
  UserBindContainer::UserBindContainer(
    Logging::Logger* logger,
    unsigned long common_chunks_number,
    const ChunkPathMap& chunk_folders,
    const char* file_prefix,
    const char* bound_file_prefix,
    const Generics::Time& extend_time_period,
    const Generics::Time& bound_extend_time_period,
    const Generics::Time& min_age,
    bool bind_at_min_age,
    unsigned long max_bad_event,
    unsigned long portions_number,
    bool load_slave,
    unsigned long partition_index, // instance partition number (first or second part of cluster)
    unsigned long partitions_number)
    /*throw(Exception)*/
    : logger_(ReferenceCounting::add_ref(logger)),
      common_chunks_number_(common_chunks_number)
  {
    chunks_.resize(common_chunks_number);

    // load chunks
    // TODO : concurrent loading - local taskrunner with destroy
    for(ChunkPathMap::const_iterator chunk_it = chunk_folders.begin();
        chunk_it != chunk_folders.end(); ++chunk_it)
    {
      chunks_[chunk_it->first] = new UserBindChunk(
        logger,
        chunk_it->second.c_str(),
        file_prefix,
        bound_file_prefix,
        extend_time_period,
        bound_extend_time_period,
        min_age,
        bind_at_min_age,
        max_bad_event,
        portions_number,
        load_slave,
        partition_index,
        partitions_number,
        chunk_folders.size());
    }
  }

  UserBindContainer::~UserBindContainer() noexcept
  {}

  UserBindContainer::UserInfo
  UserBindContainer::get_user_id(
    const String::SubString& external_id,
    const Commons::UserId& current_user_id,
    const Generics::Time& now,
    bool silent,
    const Generics::Time& create_time,
    bool for_set_cookie)
    /*throw(ChunkNotFound, Exception)*/
  {
    return get_chunk_(external_id)->get_user_id(
      external_id,
      current_user_id,
      now,
      silent,
      create_time,
      for_set_cookie);
  }

  UserBindContainer::UserInfo
  UserBindContainer::add_user_id(
    const String::SubString& external_id,
    const Commons::UserId& user_id,
    const Generics::Time& now,
    bool resave_if_exists,
    bool ignore_bad_event)
    /*throw(ChunkNotFound, Exception)*/
  {
    return get_chunk_(external_id)->add_user_id(
      external_id,
      user_id,
      now,
      resave_if_exists,
      ignore_bad_event);
  }

  void
  UserBindContainer::clear_expired(
    const Generics::Time& unbound_expire_time,
    const Generics::Time& bound_expire_time)
    /*throw(Exception)*/
  {
    for(UserBindChunkArray::iterator chunk_it = chunks_.begin();
        chunk_it != chunks_.end(); ++chunk_it)
    {
      if(*chunk_it)
      {
        (*chunk_it)->clear_expired(unbound_expire_time, bound_expire_time);
      }
    }
  }

  void
  UserBindContainer::dump() /*throw(Exception)*/
  {
    for(UserBindChunkArray::iterator chunk_it = chunks_.begin();
        chunk_it != chunks_.end(); ++chunk_it)
    {
      if(*chunk_it)
      {
        (*chunk_it)->dump();
      }
    }
  }

  UserBindChunk_var
  UserBindContainer::get_chunk_(
    const String::SubString& external_id) const
    /*throw(ChunkNotFound)*/
  {
    UserBindChunk_var res = chunks_[
      AdServer::Commons::external_id_distribution_hash(
        external_id) % common_chunks_number_];

    if(!res)
    {
      throw ChunkNotFound("");
    }

    return res;
  }
} /* namespace UserInfoSvcs */
} /* namespace AdServer */
