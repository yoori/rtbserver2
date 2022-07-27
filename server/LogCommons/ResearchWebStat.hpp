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
#ifndef AD_SERVER_LOG_PROCESSING_RESEARCH_WEB_STAT_HPP
#define AD_SERVER_LOG_PROCESSING_RESEARCH_WEB_STAT_HPP


#include <LogCommons/LogCommons.hpp>
#include <LogCommons/StatCollector.hpp>
#include <LogCommons/CsvUtils.hpp>

namespace AdServer {
namespace LogProcessing {

struct ResearchWebStatData
{
  SecondsTimestamp time;
  RequestId request_id;
  RequestId global_request_id;
  std::string app;
  std::string source;
  std::string operation;
  char result;
  std::string referer;
  std::string ip_address;
  std::string external_user_id;
  std::string user_agent;
};

typedef SeqCollector<ResearchWebStatData> ResearchWebStatCollector;

struct ResearchWebStatTraits:
  LogDefaultTraits<ResearchWebStatCollector, false, false>
{
  static const char* csv_base_name() { return "RWebStat"; }

  static const char* csv_header()
  {
    return "Timestamp,Request ID,Global Request ID,"
      "App,Source,Operation,Result,Referer,IP Address, External User ID,User-Agent";
  }

  static std::ostream&
  write_data_as_csv(
    std::ostream& os,
    const BaseTraits::CollectorType::DataT& data
  )
  {
    std::string und_user_agent;
    undisplayable_mime_encode(und_user_agent, data.user_agent);

    write_date_as_csv(os, data.time) << ',';
    os << static_cast<const UuidIoCsvWrapper&>(data.request_id ) << ',';
    os << static_cast<const UuidIoCsvWrapper&>(data.global_request_id ) << ',';
    write_string_as_csv(os, data.app) << ',';
    write_string_as_csv(os, data.source) << ',';
    write_string_as_csv(os, data.operation) << ',';
    os << data.result << ',';
    write_string_as_csv(os, data.referer) << ',';
    write_string_as_csv(os, data.ip_address) << ',';
    write_string_as_csv(os, data.external_user_id) << ',';
    write_string_as_csv(os, und_user_agent);
    return os;
  }
};

} // namespace LogProcessing
} // namespace AdServer

#endif /* AD_SERVER_LOG_PROCESSING_RESEARCH_WEB_STAT_HPP */

