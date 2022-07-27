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
#ifndef __AUTOTESTS_COMMONS_ORMLOGIC_HPP
#define __AUTOTESTS_COMMONS_ORMLOGIC_HPP

#include <Generics/Time.hpp>
#include <iostream>

#include <tests/AutoTests/Commons/ORM/PQORMObjects.hpp>
#include <tests/AutoTests/Commons/Connection.hpp>

namespace AutoTest
{
  namespace ORM
  {
    namespace DB = ::AutoTest::DBC;

    const unsigned long DEFAULT_TIME_TO = 3*60*60; // 3 hours

    /**
     * @class ExpressionChannel
     * @brief Alias for adserver expression channel.
     */
    class ExpressionChannel: public PQ::Channel
    {
    public:

      ExpressionChannel (DB::IConn& connection);
      
      ExpressionChannel (
        DB::IConn& connection,
        int account_id,
        const std::string& name);
      
      ExpressionChannel (
        DB::IConn& connection,
        const ORMInt::value_type& id);
    };

    /**
     * @class CategoryChannel
     * @brief Alias for adserver channels category.
     */
    class CategoryChannel: public PQ::Channel
    {
    public:
      CategoryChannel (DB::IConn& connection);

      CategoryChannel (
        DB::IConn& connection,
        int account_id,
        const std::string& name);

      CategoryChannel (
        DB::IConn& connection,
        const ORMInt::value_type& id);
    };

    /**
     * @class TriggerChannel
     * @brief Alias for adserver ChannelTrigger.
     */
    class TriggerChannel: public PQ::Channeltrigger
    {
    public:
      TriggerChannel(DB::IConn& connection);
      
      TriggerChannel(
        DB::IConn& connection,
        const ORMInt::value_type& id);

      TriggerChannel(
        const TriggerChannel& from);
      
      TriggerChannel&
      operator=(
        const TriggerChannel& from);

      bool select();
      bool select (const ORMInt::value_type& id);
      bool update(bool set_defaults = true);
      bool insert (bool set_defaults = true);
      bool del ();
      bool del (const ORMInt::value_type& id);
      bool delet ();
      bool delet (const ORMInt::value_type& id);

    private:
      PQ::Channel channel_;
    };
        
    /**
     * @class BehavioralChannel
     * @brief Alias for adserver behavioral channel.
     */
    class BehavioralChannel: public PQ::Channel
    {
    public:
      PQ::BehavioralParameters params;

      BehavioralChannel (DB::IConn& connection);
      
      BehavioralChannel (DB::IConn& connection, const ORMInt::value_type& id);

      BehavioralChannel (const BehavioralChannel& from);

      BehavioralChannel& operator= (const BehavioralChannel& from);

      std::string id_with_suffix ();

      bool select ();
      
      bool select (const ORMInt::value_type& id);

      bool update (bool set_defaults = true);

      bool update (
        const ORMInt::value_type& id,
        bool set_defaults = true);
      
      bool insert (bool set_defaults = true);
      
      bool delet ();
      
      bool del ();
      
      bool delet (const ORMInt::value_type& id);
      
      bool del (const ORMInt::value_type& id);
      
      bool has_name (const ORMString::value_type& name);
      
      bool select_name (const ORMString::value_type& name);
      
      bool insert_name (
        const std::string& name,
        bool set_defaults = true);
      
    };

    /**
     * @class DiscoverChannel
     * @brief Alias for adserver discover channel.
     */
    class DiscoverChannel:
      public BehavioralChannel
    {
    public:
      DiscoverChannel (DB::IConn& connection);
      
      DiscoverChannel (
        DB::IConn& connection,
        const ORMInt::value_type& id);

      bool delet ();

      bool delet (const ORMInt::value_type& id);

    private:
      void delet_stats_();
    };


    /**
     * @class SearchChannel
     * @brief Alias for adserver search channel
     * (include "search" behavioral parameter).
     */
    class SearchChannel:
      public BehavioralChannel
    {
    public:
      SearchChannel (DB::IConn& connection);
      
      SearchChannel (
        DB::IConn& connection,
        int account_id,
        const std::string& _name,
        int minimum_visits,
        int time_from,
        int tme_to);
      
     
      SearchChannel (
        DB::IConn& connection,
        const ORMInt::value_type& id);
    };

    // class PageChannel
    /**
     * @class SearchChannel
     * @brief Alias for adserver search channel
     * (include "page" behavioral parameter).
     */
    class PageChannel:
      public BehavioralChannel
    {
    public:
      PageChannel (DB::IConn& connection);
      
      PageChannel (
        DB::IConn& connection,
        int account_id,
        const std::string& _name,
        int minimum_visits,
        int time_from,
        int tme_to);
      
      PageChannel (
        DB::IConn& connection,
        const ORMInt::value_type& id);
    };

    /**
     * @class RatedTagPricing
     * @brief Composite entity that represents pair TagPricing and SiteRate.
     */
    class RatedTagPricing:
      public PQ::TagPricing
    {
    public:
      PQ::SiteRate rate;

      /**
       * @brief Constructors
       */
      RatedTagPricing(DB::IConn& connection);
      RatedTagPricing(const RatedTagPricing& from);
      RatedTagPricing& operator=(const RatedTagPricing& from);
      RatedTagPricing(DB::IConn& connection,const ORMInt::value_type& id);

      bool select (); //!< get exists
      bool update (bool set_defaults = true); //!< update exists
      bool insert (bool set_defaults = true); //!< create new
      bool delet  (); //!< delete exists
      void log_in  (Logger&, unsigned long severity = Logging::Logger::INFO); //!< log record
    };

    /**
     * @class RatedColocation
     * @brief Composite entity that represents pair Colocation and ColocationRate.
     */
    class RatedColocation:
      public PQ::Colocation
    {
    public:
      PQ::ColocationRate rate;

      /**
       * @brief Constructors
       */
      RatedColocation(DB::IConn& connection);
      RatedColocation(const RatedColocation& from);
      RatedColocation& operator=(const RatedColocation& from);
      RatedColocation(
        DB::IConn& connection,
        const ORMInt::value_type& id);

      bool select (); //!< get exists
      bool update (bool set_defaults = true); //!< update exists
      bool insert (bool set_defaults = true); //!< create new
      bool insert_rate(bool set_defaults  = true); //!< create new rate
      bool delet  (); //!< delete exists
    };

    /**
     * @class RatedCampaignCreativeGroup
     * @brief Composite entity that represents pair CampaignCreativeGroup and CCGRate.
     */
    class RatedCampaignCreativeGroup:
      public PQ::CampaignCreativeGroup
    {
    public:
      PQ::CCGRate rate;

      /**
       * @brief Constructors
       */
      RatedCampaignCreativeGroup(DB::IConn& connection);
      RatedCampaignCreativeGroup(const RatedCampaignCreativeGroup& from);
      RatedCampaignCreativeGroup& operator=(const RatedCampaignCreativeGroup& from);
      RatedCampaignCreativeGroup(DB::IConn& connection,const ORMInt::value_type& id);

      bool select (); //!< get exists
      bool update (bool set_defaults = true); //!< update exists
      bool insert (bool set_defaults = true); //!< create new
      bool delet  (); //!< delete exists
      void log_in  (Logger&, unsigned long severity = Logging::Logger::INFO); //!< log record
    };
  }//namespace ORM
}//namespace AutoTest

#endif //__AUTOTESTS_COMMONS_ORMLOGIC_HPP
