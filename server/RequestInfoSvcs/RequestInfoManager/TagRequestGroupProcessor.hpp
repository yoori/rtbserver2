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
#ifndef REQUESTINFOSVCS_REQUESTINFOMANAGER_TAGREQUESTGROUPPROCESSOR_HPP
#define REQUESTINFOSVCS_REQUESTINFOMANAGER_TAGREQUESTGROUPPROCESSOR_HPP

#include <string>
#include <set>

#include <eh/Exception.hpp>
#include <ReferenceCounting/Interface.hpp>
#include <ReferenceCounting/AtomicImpl.hpp>
#include <Generics/Time.hpp>
#include <Commons/Algs.hpp>

namespace AdServer
{
namespace RequestInfoSvcs
{
  struct TagRequestGroupProcessor: public virtual ReferenceCounting::Interface
  {
    DECLARE_EXCEPTION(Exception, eh::DescriptiveException);

    static const Generics::Time DEFAULT_EXPIRE_TIME; // 1 day

    struct TagRequestGroupInfo
    {
      typedef std::multiset<unsigned long> TagIdSet;

      // verified passback info
      TagRequestGroupInfo(): colo_id(0), site_id(0) {}

      TagRequestGroupInfo(
        const Generics::Time& time_val,
        unsigned long colo_id_val,
        unsigned long site_id_val,
        const char* country_val,
        const TagIdSet& tags_val,
        bool ad_shown_val,
        bool rollback_val)
        : time(time_val),
          colo_id(colo_id_val),
          site_id(site_id_val),
          country(country_val),
          tags(tags_val),
          ad_shown(ad_shown_val),
          rollback(rollback_val)
      {}

      bool operator==(const TagRequestGroupInfo& right) const
      {
        return time == right.time &&
          colo_id == right.colo_id &&
          site_id == right.site_id &&
          country == right.country &&
          ad_shown == right.ad_shown &&
          rollback == right.rollback &&
          tags.size() == right.tags.size() &&
          std::equal(tags.begin(), tags.end(), right.tags.begin());
      }

      std::ostream& print(std::ostream& ostr, const char* prefix) const
      {
        ostr << prefix << "time = " << time.get_gm_time() << std::endl <<
          prefix << "country = " << country << std::endl <<
          prefix << "colo_id = " << colo_id << std::endl <<
          prefix << "site_id = " << site_id << std::endl <<
          prefix << "ad_shown = " << ad_shown << std::endl <<
          prefix << "rollback = " << rollback << std::endl <<
          prefix << "tags = ";
        Algs::print(ostr, tags.begin(), tags.end());
        ostr << std::endl;
        return ostr;
      }

      Generics::Time time;
      unsigned long colo_id;
      unsigned long site_id;
      std::string country;
      TagIdSet tags;
      bool ad_shown;
      bool rollback;
    };

    typedef std::list<TagRequestGroupProcessor::TagRequestGroupInfo>
      TagRequestGroupInfoList;

    virtual void
    process_tag_request_group(const TagRequestGroupInfo& tag_request_group_info)
      /*throw (Exception)*/ = 0;

  protected:
    virtual ~TagRequestGroupProcessor() noexcept {}
  };

  typedef ReferenceCounting::SmartPtr<TagRequestGroupProcessor>
    TagRequestGroupProcessor_var;
}
}

#endif /*REQUESTINFOSVCS_REQUESTINFOMANAGER_TAGREQUESTGROUPPROCESSOR_HPP*/
