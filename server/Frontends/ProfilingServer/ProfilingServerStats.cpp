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
/* $Id: ProfilingServerStats.cpp 185976 2020-07-01 22:11:23Z jurij_kuznecov $
* @file ProfilingServerStats.cpp
* @author Artem V. Nikitin (artem_nikitin@ocslab.com)
* Profiling server statistics
*/
#include "ProfilingServerStats.hpp"

namespace AdServer
{
  namespace Profiling
  {
    const Generics::StringHashAdapter
    ProfilingServerStats::SENT_MESSAGES_COUNT_("sentMessagesCount");
    
    const Generics::StringHashAdapter
    ProfilingServerStats::SENT_MESSAGES_SIZE_("sentMessagesSize");
    
    const Generics::StringHashAdapter
    ProfilingServerStats::FILTERED_MESSAGES_COUNT_("filteredMessagesCount");
    
    const Generics::StringHashAdapter
    ProfilingServerStats::RECEIVED_MESSAGES_COUNT_("recvMessagesCount");
    
    const Generics::StringHashAdapter
    ProfilingServerStats::RECEIVED_MESSAGES_SIZE_("recvMessagesSize");

    const Generics::StringHashAdapter
    ProfilingServerStats::KAFKA_ERRORS_COUNT_("kafkaErrorsCount");

    ProfilingServerStats::ProfilingServerStats(
       DMPKafkaStreamer* streamer) noexcept
      : streamer_(ReferenceCounting::add_ref(streamer)),
        filtered_messages_count_(0),
        received_messages_count_(0),
        received_messages_size_(0)
    {}

    void
    ProfilingServerStats::add_filtered_messages(unsigned long filtered_count)
    noexcept
    {
      filtered_messages_count_ += filtered_count;
    }
    
    void
    ProfilingServerStats::add_received_messages(
      unsigned long received_count,
      unsigned long received_size)
      noexcept
    {
      received_messages_count_ += received_count;
      received_messages_size_ += received_size;
    }
    
    unsigned long
    ProfilingServerStats::filtered_messages() const noexcept
    {
      return filtered_messages_count_;
    }

    unsigned long
    ProfilingServerStats::sent_messages() const noexcept
    {
      return streamer_->sent_messages();
    }

    unsigned long
    ProfilingServerStats::kafka_errors() const noexcept
    {
      return streamer_->errors();
    }

    unsigned long
    ProfilingServerStats::sent_messages_size() const noexcept
    {
      return streamer_->sent_bytes();
    }
    
    unsigned long
    ProfilingServerStats::received_messages() const noexcept
    {
      return received_messages_count_;
    }
    
    unsigned long
    ProfilingServerStats::received_messages_size() const noexcept
    {
      return received_messages_size_;
    }
  }
}
