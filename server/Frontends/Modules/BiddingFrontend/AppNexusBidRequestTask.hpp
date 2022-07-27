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
#ifndef APPNEXUSBIDREQUESTTASK_HPP_
#define APPNEXUSBIDREQUESTTASK_HPP_

#include "BidRequestTask.hpp"

namespace AdServer
{
namespace Bidding
{
  //
  // AppNexusBidRequestTask
  //
  class AppNexusBidRequestTask: public BidRequestTask
  {
  public:
    AppNexusBidRequestTask(
      Frontend* bid_frontend,
      FCGI::HttpRequestHolder_var request_holder,
      FCGI::HttpResponseWriter_var response_writer,
      const Generics::Time& start_processing_time)
      /*throw (Invalid)*/;

    virtual void
    print_request(std::ostream& out) const noexcept;

    // processing stages
    // read request & transform it to holder
    virtual bool
    read_request() noexcept;

    virtual bool
    write_response(
      const AdServer::CampaignSvcs::CampaignManager::RequestCreativeResult&
        campaign_match_result)
      noexcept;

    virtual void
    write_empty_response(unsigned int code)
      noexcept;

    virtual void
    clear() noexcept;

  public:
    //std::string bid_response;

  protected:
    virtual
    ~AppNexusBidRequestTask() noexcept = default;

  private:
    //std::string bid_request_;
    JsonProcessingContext context_;
  };
}
}

#endif /*APPNEXUSBIDREQUESTTASK_HPP_*/
