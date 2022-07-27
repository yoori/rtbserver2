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
#ifndef AD_SERVER_LOG_PROCESSING_LOG_PROCESSOR_IMPL_HPP
#define AD_SERVER_LOG_PROCESSING_LOG_PROCESSOR_IMPL_HPP


#include "LogTypeExtTraits.hpp"
#include "GenericLogProcImpl.hpp"
#include "CustomLogProcImpl.hpp"

namespace AdServer {
namespace LogProcessing {

typedef GenericLogProcessorImpl<ChannelImpInventoryExtTraits>
  ChannelImpInventoryProcessor;

typedef GenericLogProcessorImpl<CreativeStatExtTraits> CreativeStatProcessor;

typedef GenericLogProcessorImpl<ColoUserStatExtTraits>
  ColoUserStatProcessor;

typedef GenericLogProcessorImpl<GlobalColoUserStatExtTraits>
  GlobalColoUserStatProcessor;

typedef GenericLogProcessorImpl<ColoUsersExtTraits>
  ColoUsersProcessor;

typedef GenericLogProcessorImpl<CampaignUserStatExtTraits>
  CampaignUserStatProcessor;

typedef GenericLogProcessorImpl<CcgKeywordStatExtTraits>
  CcgKeywordStatProcessor;

typedef GenericLogProcessorImpl<CcgSelectionFailureStatExtTraits>
  CcgSelectionFailureStatProcessor;

// Outputs log data in the CSV format
typedef GenericLogProcessorImpl<
          CcgSelectionFailureStatExtTraits,
          LogVersionManager3<CcgSelectionFailureStatExtTraits>
        > CcgSelectionFailureStatProcessor2;

typedef GenericLogProcessorImpl<CcgStatExtTraits>
  CcgStatProcessor;

typedef GenericLogProcessorImpl<CcgUserStatExtTraits>
  CcgUserStatProcessor;

typedef GenericLogProcessorImpl<CcStatExtTraits>
  CcStatProcessor;

typedef GenericLogProcessorImpl<CcUserStatExtTraits>
  CcUserStatProcessor;

typedef GenericLogProcessorImpl<AdvertiserUserStatExtTraits>
  AdvertiserUserStatProcessor;

typedef GenericLogProcessorImpl<ChannelHitStatExtTraits>
  ChannelHitStatProcessor;

// Outputs log data in the CSV format
typedef GenericLogProcessorImpl<ChannelHitStatExtTraits,
  LogVersionManager3<ChannelHitStatExtTraits> >
  ChannelHitStatProcessor2;

typedef GenericLogProcessorImpl<SiteReferrerStatExtTraits>
  SiteReferrerStatProcessor;

typedef GenericLogProcessorImpl<PassbackStatExtTraits>
  PassbackStatProcessor;

// Outputs log data in the CSV format
typedef GenericLogProcessorImpl<CmpStatExtTraits>
  CmpStatProcessor;

typedef GenericLogProcessorImpl<SiteUserStatExtTraits>
  SiteUserStatProcessor;

typedef GenericLogProcessorImpl<TagAuctionStatExtTraits>
  TagAuctionStatProcessor;

typedef GenericLogProcessorImpl<PageLoadsDailyStatExtTraits>
  PageLoadsDailyStatProcessor;

typedef GenericLogProcessorImpl<ChannelCountStatExtTraits>
  ChannelCountStatProcessor;

// Outputs log data in the CSV format
typedef GenericLogProcessorImpl<ChannelCountStatExtTraits,
  LogVersionManager3<ChannelCountStatExtTraits> >
  ChannelCountStatProcessor2;

typedef GenericLogProcessorImpl<ChannelOverlapUserStatExtTraits>
  ChannelOverlapUserStatProcessor;

// Outputs log data in the CSV format
typedef GenericLogProcessorImpl<ChannelOverlapUserStatExtTraits,
  LogVersionManager3<ChannelOverlapUserStatExtTraits> >
  ChannelOverlapUserStatProcessor2;

typedef GenericLogProcessorImpl<ChannelTriggerImpStatExtTraits>
  ChannelTriggerImpStatProcessor;

// Outputs log data in the CSV format
typedef GenericLogProcessorImpl<ChannelTriggerImpStatExtTraits,
  LogVersionManager3<ChannelTriggerImpStatExtTraits> >
  ChannelTriggerImpStatProcessor2;

typedef GenericLogProcessorImpl<ChannelTriggerStatExtTraits>
  ChannelTriggerStatProcessor;

// Outputs log data in the CSV format
typedef GenericLogProcessorImpl<ChannelTriggerStatExtTraits,
  LogVersionManager3<ChannelTriggerStatExtTraits> >
  ChannelTriggerStatProcessor2;

typedef GenericLogProcessorImpl<DeviceChannelCountStatExtTraits>
  DeviceChannelCountStatProcessor;

// Outputs log data in the CSV format
typedef GenericLogProcessorImpl<DeviceChannelCountStatExtTraits,
  LogVersionManager3<DeviceChannelCountStatExtTraits> >
  DeviceChannelCountStatProcessor2;

typedef GenericLogProcessorImpl<SearchEngineStatExtTraits>
  SearchEngineStatProcessor;

// Outputs log data in the CSV format
typedef GenericLogProcessorImpl<SearchEngineStatExtTraits,
  LogVersionManager3<SearchEngineStatExtTraits> >
  SearchEngineStatProcessor2;

// Uses hits filtering
typedef GenericLogProcessorImpl<SearchTermStatExtTraits,
  LogVersionManager7<SearchTermStatExtTraits> >
  SearchTermStatProcessor;

// Outputs log data in the CSV format (with hits filtering)
typedef GenericLogProcessorImpl<SearchTermStatExtTraits,
  LogVersionManager8<SearchTermStatExtTraits> >
  SearchTermStatProcessor2;

typedef GenericLogProcessorImpl<TagPositionStatExtTraits>
  TagPositionStatProcessor;

// Outputs log data in the CSV format
typedef GenericLogProcessorImpl<TagPositionStatExtTraits,
  LogVersionManager3<TagPositionStatExtTraits> >
  TagPositionStatProcessor2;

typedef GenericLogProcessorImpl<UserAgentStatExtTraits>
  UserAgentStatProcessor;

// Outputs log data in the CSV format
typedef GenericLogProcessorImpl<UserAgentStatExtTraits,
  LogVersionManager3<UserAgentStatExtTraits> >
  UserAgentStatProcessor2;

typedef GenericLogProcessorImpl<WebStatExtTraits>
  WebStatProcessor;

// Outputs log data in the CSV format
typedef GenericLogProcessorImpl<WebStatExtTraits,
  LogVersionManager3<WebStatExtTraits> >
  WebStatProcessor2;

typedef GenericLogProcessorImpl<ActionStatExtTraits>
  ActionStatProcessor;

typedef GenericLogProcessorImpl<ChannelPerformanceExtTraits>
  ChannelPerformanceProcessor;

// Outputs log data in the CSV format
typedef GenericLogProcessorImpl<ChannelPerformanceExtTraits,
  LogVersionManager3<ChannelPerformanceExtTraits> >
  ChannelPerformanceProcessor2;

typedef GenericLogProcessorImpl<ExpressionPerformanceExtTraits>
  ExpressionPerformanceProcessor;

// Outputs log data in the CSV format
typedef GenericLogProcessorImpl<ExpressionPerformanceExtTraits,
  LogVersionManager3<ExpressionPerformanceExtTraits> >
  ExpressionPerformanceProcessor2;

typedef GenericLogProcessorImpl<ActionRequestExtTraits>
  ActionRequestProcessor;

// Outputs log data in the CSV format
typedef GenericLogProcessorImpl<ActionRequestExtTraits,
  LogVersionManager3<ActionRequestExtTraits> >
  ActionRequestProcessor2;

typedef GenericLogProcessorImpl<ChannelImpInventoryExtTraits>
  ChannelImpInventoryProcessor;

// Outputs log data in the CSV format
typedef GenericLogProcessorImpl<ChannelImpInventoryExtTraits,
  LogVersionManager3<ChannelImpInventoryExtTraits> >
  ChannelImpInventoryProcessor2;

typedef GenericLogProcessorImpl<ChannelInventoryExtTraits>
  ChannelInventoryProcessor;

// Outputs log data in the CSV format
typedef GenericLogProcessorImpl<ChannelInventoryExtTraits,
  LogVersionManager3<ChannelInventoryExtTraits> >
  ChannelInventoryProcessor2;

typedef GenericLogProcessorImpl<ChannelInventoryEstimationStatExtTraits>
  ChannelInventoryEstimationStatProcessor;

// Outputs log data in the CSV format
typedef GenericLogProcessorImpl<ChannelInventoryEstimationStatExtTraits,
  LogVersionManager3<ChannelInventoryEstimationStatExtTraits> >
  ChannelInventoryEstimationStatProcessor2;

typedef GenericLogProcessorImpl<ChannelPriceRangeExtTraits>
  ChannelPriceRangeProcessor;

// Outputs log data in the CSV format
typedef GenericLogProcessorImpl<ChannelPriceRangeExtTraits,
  LogVersionManager3<ChannelPriceRangeExtTraits> >
  ChannelPriceRangeProcessor2;

typedef GenericLogProcessorImpl<ColoUpdateStatExtTraits>
  ColoUpdateStatProcessor;

typedef GenericLogProcessorImpl<UserPropertiesExtTraits>
  UserPropertiesProcessor;

// Outputs log data in the CSV format
typedef GenericLogProcessorImpl<
          UserPropertiesExtTraits, LogVersionManager3<UserPropertiesExtTraits>
        > UserPropertiesProcessor2;

typedef GenericLogProcessorImpl<CampaignReferrerStatExtTraits>
  CampaignReferrerStatProcessor;
} // namespace LogProcessing
} // namespace AdServer

#endif /* AD_SERVER_LOG_PROCESSING_LOG_PROCESSOR_IMPL_HPP */
