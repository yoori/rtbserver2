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
#ifndef AD_SERVER_LOG_PROCESSING_WEBWISE_DISCOVER_TAG_STAT_HPP
#define AD_SERVER_LOG_PROCESSING_WEBWISE_DISCOVER_TAG_STAT_HPP

#include <iosfwd>
#include <sstream>
#include <Generics/Time.hpp>
#include <ReferenceCounting/SmartPtr.hpp>
#include "LogCommons.hpp"
#include "StatCollector.hpp"


namespace AdServer {
namespace LogProcessing {

// WebwiseDiscoverTagStat v1.1 - AdServer v1.12-2.2

class WebwiseDiscoverTagStatInnerData_V_1_1
{
public:
  WebwiseDiscoverTagStatInnerData_V_1_1()
  :
    imps_()
  {
  }

  explicit
  WebwiseDiscoverTagStatInnerData_V_1_1(
    unsigned long imps
  )
  :
    imps_(imps)
  {
  }

  bool operator==(const WebwiseDiscoverTagStatInnerData_V_1_1 &rhs) const
  {
    if (&rhs == this)
    {
      return true;
    }
    return imps_ == rhs.imps_;
  }

  WebwiseDiscoverTagStatInnerData_V_1_1&
  operator+=(const WebwiseDiscoverTagStatInnerData_V_1_1 &rhs)
  {
    imps_ += rhs.imps_;
    return *this;
  }

  unsigned long imps() const
  {
    return imps_;
  }

  friend std::istream& operator>>(std::istream &is,
    WebwiseDiscoverTagStatInnerData_V_1_1 &data) /*throw(eh::Exception)*/;
  friend std::ostream& operator<<(std::ostream &os,
    const WebwiseDiscoverTagStatInnerData_V_1_1 &data) /*throw(eh::Exception)*/;

private:
  unsigned long imps_;
};

class WebwiseDiscoverTagStatInnerKey
{
public:
  WebwiseDiscoverTagStatInnerKey()
  :
    wdtag_id_(),
    opted_in_(),
    test_(),
    hash_()
  {
  }

  WebwiseDiscoverTagStatInnerKey(
    unsigned long wdtag_id,
    bool opted_in,
    bool test
  )
  :
    wdtag_id_(wdtag_id),
    opted_in_(opted_in),
    test_(test),
    hash_()
  {
    calc_hash();
  }

  bool operator==(const WebwiseDiscoverTagStatInnerKey &rhs) const
  {
    if (&rhs == this)
    {
      return true;
    }
    return wdtag_id_ == rhs.wdtag_id_ &&
      opted_in_ == rhs.opted_in_ &&
      test_ == rhs.test_;
  }

  unsigned long wdtag_id() const
  {
    return wdtag_id_;
  }

  bool opted_in() const
  {
    return opted_in_;
  }

  bool test() const
  {
    return test_;
  }

  size_t hash() const
  {
    return hash_;
  }

  friend std::istream& operator>>(std::istream &is,
    WebwiseDiscoverTagStatInnerKey &key) /*throw(eh::Exception)*/;
  friend std::ostream& operator<<(std::ostream &os,
    const WebwiseDiscoverTagStatInnerKey &key) /*throw(eh::Exception)*/;

private:
  void calc_hash()
  {
    Generics::Murmur64Hash hasher(hash_);
    hash_add(hasher, wdtag_id_);
    hash_add(hasher, opted_in_);
    hash_add(hasher, test_);
  }

  unsigned long wdtag_id_;
  bool opted_in_;
  bool test_;
  size_t hash_;
};

class WebwiseDiscoverTagStatInnerData
{
public:
  WebwiseDiscoverTagStatInnerData()
  :
    imps_(),
    clicks_()
  {
  }

  WebwiseDiscoverTagStatInnerData(
    unsigned long imps,
    unsigned long clicks
  )
  :
    imps_(imps),
    clicks_(clicks)
  {
  }

  WebwiseDiscoverTagStatInnerData(
    const WebwiseDiscoverTagStatInnerData_V_1_1 &data
  )
  :
    imps_(data.imps()),
    clicks_()
  {
  }

  bool operator==(const WebwiseDiscoverTagStatInnerData &rhs) const
  {
    if (&rhs == this)
    {
      return true;
    }
    return imps_ == rhs.imps_ && clicks_ == rhs.clicks_;
  }

  WebwiseDiscoverTagStatInnerData&
  operator+=(const WebwiseDiscoverTagStatInnerData &rhs)
  {
    imps_ += rhs.imps_;
    clicks_ += rhs.clicks_;
    return *this;
  }

  unsigned long imps() const
  {
    return imps_;
  }

  unsigned long clicks() const
  {
    return clicks_;
  }

  friend std::istream& operator>>(std::istream &is,
    WebwiseDiscoverTagStatInnerData &data) /*throw(eh::Exception)*/;
  friend std::ostream& operator<<(std::ostream &os,
    const WebwiseDiscoverTagStatInnerData &data) /*throw(eh::Exception)*/;

private:
  unsigned long imps_;
  unsigned long clicks_;
};

struct WebwiseDiscoverTagStatKey
{
  WebwiseDiscoverTagStatKey(): sdate_(), colo_id_(), hash_() {}

  WebwiseDiscoverTagStatKey(
    const DayHourTimestamp &sdate,
    unsigned long colo_id
  )
  :
    sdate_(sdate),
    colo_id_(colo_id),
    hash_()
  {
    calc_hash();
  }

  bool operator==(const WebwiseDiscoverTagStatKey &rhs) const
  {
    if (&rhs == this)
    {
      return true;
    }
    return sdate_ == rhs.sdate_ && colo_id_ == rhs.colo_id_;
  }

public:
  const DayHourTimestamp& sdate() const
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

  friend std::istream& operator>>(std::istream &is,
    WebwiseDiscoverTagStatKey &key);
  friend std::ostream& operator<<(std::ostream &os,
    const WebwiseDiscoverTagStatKey &key) /*throw(eh::Exception)*/;

private:
  void calc_hash()
  {
    Generics::Murmur64Hash hasher(hash_);
    sdate_.hash_add(hasher);
    hash_add(hasher, colo_id_);
  }

  DayHourTimestamp sdate_;
  unsigned long colo_id_;
  size_t hash_;
};


typedef WebwiseDiscoverTagStatInnerKey WebwiseDiscoverTagStatInnerKey_V_1_1;

typedef StatCollector<
          WebwiseDiscoverTagStatInnerKey_V_1_1,
          WebwiseDiscoverTagStatInnerData_V_1_1
        > WebwiseDiscoverTagStatInnerCollector_V_1_1;

typedef WebwiseDiscoverTagStatInnerCollector_V_1_1
  WebwiseDiscoverTagStatData_V_1_1;

typedef WebwiseDiscoverTagStatKey WebwiseDiscoverTagStatKey_V_1_1;

typedef StatCollector<
          WebwiseDiscoverTagStatKey_V_1_1,
          WebwiseDiscoverTagStatData_V_1_1
        > WebwiseDiscoverTagStatCollector_V_1_1;

typedef StatCollector<
          WebwiseDiscoverTagStatInnerKey,
          WebwiseDiscoverTagStatInnerData
        > WebwiseDiscoverTagStatInnerCollector;

typedef WebwiseDiscoverTagStatInnerCollector WebwiseDiscoverTagStatData;

typedef StatCollector<WebwiseDiscoverTagStatKey, WebwiseDiscoverTagStatData>
  WebwiseDiscoverTagStatCollector;


struct WebwiseDiscoverTagStatTraits : LogDefaultTraits<WebwiseDiscoverTagStatCollector>
{
  template <typename Functor>
  static void
  for_each_old(Functor& f) /*throw (eh::Exception)*/
  {
    f.template operator ()<WebwiseDiscoverTagStatCollector_V_1_1>("1.1");
  }
};


} // namespace LogProcessing
} // namespace AdServer

#endif /* AD_SERVER_LOG_PROCESSING_WEBWISE_DISCOVER_TAG_STAT_HPP */

