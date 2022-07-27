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
#ifndef AD_SERVER_LOG_PROCESSING_SEARCH_ENGINE_STAT_HPP
#define AD_SERVER_LOG_PROCESSING_SEARCH_ENGINE_STAT_HPP

#include <iosfwd>
#include <Generics/Time.hpp>
#include "LogCommons.hpp"
#include "StatCollector.hpp"

namespace AdServer {
namespace LogProcessing {

class SearchEngineStatInnerKey
{
  typedef Aux_::StringIoWrapper String_;

public:
  SearchEngineStatInnerKey()
  :
    search_engine_id_(),
    host_name_(),
    hash_()
  {
  }

  SearchEngineStatInnerKey(
    unsigned long search_engine_id,
    const std::string& host_name
  )
  :
    search_engine_id_(search_engine_id),
    host_name_(host_name),
    hash_()
  {
    calc_hash_();
  }

  bool operator==(const SearchEngineStatInnerKey& rhs) const
  {
    if (&rhs == this)
    {
      return true;
    }
    return search_engine_id_ == rhs.search_engine_id_ &&
      host_name_ == rhs.host_name_;
  }

  unsigned long search_engine_id() const
  {
    return search_engine_id_;
  }

  const std::string& host_name() const
  {
    return host_name_;
  }

  size_t hash() const
  {
    return hash_;
  }

  friend
  FixedBufStream<TabCategory>&
  operator>>(FixedBufStream<TabCategory>& is, SearchEngineStatInnerKey& key)
    /*throw(eh::Exception)*/;

  friend
  std::ostream&
  operator<<(std::ostream& os, const SearchEngineStatInnerKey& key)
    /*throw(eh::Exception)*/;

private:
  void calc_hash_()
  {
    Generics::Murmur64Hash hasher(hash_);
    hash_add(hasher, search_engine_id_);
    hash_add(hasher, host_name_);
  }

  void invariant_() const /*throw(eh::Exception)*/
  {
    if (host_name_.empty())
    {
      throw ConstraintViolation("SearchEngineStatInnerKey::"
        "invariant_(): host_name_ must be non-empty");
    }
  }

  unsigned long search_engine_id_;
  String_ host_name_;
  size_t hash_;
};

class SearchEngineStatInnerData
{
public:
  SearchEngineStatInnerData()
  :
    hits_(),
    hits_empty_page_()
  {
  }

  SearchEngineStatInnerData(
    unsigned long hits,
    unsigned long hits_empty_page
  )
  :
    hits_(hits),
    hits_empty_page_(hits_empty_page)
  {
  }

  bool operator==(const SearchEngineStatInnerData& rhs) const
  {
    if (&rhs == this)
    {
      return true;
    }
    return hits_ == rhs.hits_ && hits_empty_page_ == rhs.hits_empty_page_;
  }

  SearchEngineStatInnerData&
  operator+=(const SearchEngineStatInnerData& rhs)
  {
    hits_ += rhs.hits_;
    hits_empty_page_ += rhs.hits_empty_page_;
    return *this;
  }

  unsigned long hits() const
  {
    return hits_;
  }

  unsigned long hits_empty_page() const
  {
    return hits_empty_page_;
  }

  friend
  FixedBufStream<TabCategory>&
  operator>>(FixedBufStream<TabCategory>& is, SearchEngineStatInnerData& data)
    /*throw(eh::Exception)*/;

  friend
  std::ostream&
  operator<<(std::ostream& os, const SearchEngineStatInnerData& data)
    /*throw(eh::Exception)*/;

private:
  unsigned long hits_;
  unsigned long hits_empty_page_;
};

struct SearchEngineStatKey
{
  SearchEngineStatKey(): sdate_(), colo_id_(), hash_() {}

  SearchEngineStatKey(
    const DayTimestamp& sdate,
    unsigned long colo_id
  )
  :
    sdate_(sdate),
    colo_id_(colo_id),
    hash_()
  {
    calc_hash_();
  }

  bool operator==(const SearchEngineStatKey& rhs) const
  {
    if (&rhs == this)
    {
      return true;
    }
    return sdate_ == rhs.sdate_ && colo_id_ == rhs.colo_id_;
  }

  const DayTimestamp& sdate() const
  {
    return sdate_;
  }

  unsigned long colo_id() const
  {
    return colo_id_;
  }

  size_t hash() const
  {
    return hash_;
  }

  friend
  std::istream&
  operator>>(std::istream& is, SearchEngineStatKey& key)
    /*throw(eh::Exception)*/;

  friend
  std::ostream&
  operator<<(std::ostream& os, const SearchEngineStatKey& key)
    /*throw(eh::Exception)*/;

private:
  void calc_hash_()
  {
    Generics::Murmur64Hash hasher(hash_);
    hash_add(hasher, colo_id_);
    sdate_.hash_add(hasher);
  }

  DayTimestamp sdate_;
  unsigned long colo_id_;
  size_t hash_;
};

typedef StatCollector<
          SearchEngineStatInnerKey,
          SearchEngineStatInnerData,
          false,
          true
        > SearchEngineStatInnerCollector;

typedef SearchEngineStatInnerCollector SearchEngineStatData;

typedef StatCollector<SearchEngineStatKey, SearchEngineStatData>
  SearchEngineStatCollector;

typedef LogDefaultTraits<SearchEngineStatCollector> SearchEngineStatTraits;

} // namespace LogProcessing
} // namespace AdServer

#endif /* AD_SERVER_LOG_PROCESSING_SEARCH_ENGINE_STAT_HPP */

