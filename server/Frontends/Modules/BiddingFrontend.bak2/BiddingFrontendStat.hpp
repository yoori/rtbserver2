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
/// @file BiddingFrontend/BiddingFrontendStat.hpp
#ifndef BIDDINGFRONTENDSTAT_HPP
#define BIDDINGFRONTENDSTAT_HPP

#include <eh/Exception.hpp>
#include <Generics/CompositeActiveObject.hpp>
#include <Controlling/StatsDumper/StatsDumper.hpp>
#include <CORBACommons/CorbaAdapters.hpp>
#include <Frontends/FrontendCommons/CampaignManagersPool.hpp>


namespace AdServer
{
  class BiddingStatInfo;

  class StatHolder : public ReferenceCounting::AtomicImpl
  {
  public:
    struct StatData
    {
      StatData();
      StatData(
        unsigned long request_google_,
        unsigned long request_google_bid_,
        unsigned long request_openrtb_,
        unsigned long request_openrtb_bid_,
        unsigned long request_other_,
        unsigned long request_other_bid_,
        const Generics::Time& processing_time);
      
      unsigned long request_google;
      unsigned long request_google_bid;
      unsigned long request_openrtb;
      unsigned long request_openrtb_bid;
      unsigned long request_other;
      unsigned long request_other_bid;
      unsigned long skipped;
      Generics::Time processing_time;
      typedef std::map<Generics::Time, std::size_t> TimeoutsMap;
      TimeoutsMap timeout_counters;
    
      StatData&
      operator +=(const StatData& rhs) noexcept;
    };

    void
    flush(
      const CampaignSvcs::CampaignManager::RequestParams&,
      CampaignSvcs::CampaignManager::RequestCreativeResult*,
      const Generics::Time& processing_time)
      noexcept;
    
    void
    add_skipped() noexcept;

    void
    add_timeout(const Generics::Time& timeout) noexcept;

    virtual Generics::Values_var
    dump_stats();

  protected:
    virtual
    ~StatHolder() noexcept = default;

  private:
    StatData stat_data_;
    Sync::PosixMutex mutex_;
  };

  typedef ReferenceCounting::SmartPtr<StatHolder>
    StatHolder_var;
  
  class BiddingFrontendStatsImpl:
    public CORBACommons::ReferenceCounting::ServantImpl<
      POA_CORBACommons::ProcessStatsControl>,
      public Generics::CompositeActiveObject
  {
  public:
    BiddingFrontendStatsImpl(
      StatHolder* stat_holder)
      noexcept;
      
    virtual CORBACommons::StatsValueSeq*
    get_stats() throw(
      CORBA::Exception,
      CORBACommons::ProcessStatsControl::ImplementationException);

  private:
    StatHolder_var stat_holder_;
  };

  typedef ReferenceCounting::SmartPtr<BiddingFrontendStatsImpl>
  BiddingFrontendStatsImpl_var;
}

#endif // BIDDINGFRONTENDSTAT_HPP
