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
#include <Generics/Time.hpp>

#include <Commons/Algs.hpp>
#include <RequestInfoSvcs/RequestInfoCommons/PassbackProfile.hpp>
#include <RequestInfoSvcs/RequestInfoManager/Compatibility/PassbackProfile_v32.hpp>

#include "PassbackProfileAdapter.hpp"

namespace AdServer
{
namespace RequestInfoSvcs
{
  Generics::ConstSmartMemBuf_var
  PassbackProfileAdapter::operator()(
    const Generics::ConstSmartMemBuf* mem_buf_ptr)
    /*throw(Exception)*/
  {
    static const char* FUN = "RequestProfileAdapter::operator()";

    unsigned long version_head_size = PassbackInfoVersionReader::FIXED_SIZE;
    if(mem_buf_ptr->membuf().size() < version_head_size)
    {
      Stream::Error ostr;
      ostr << "Invalid passback profile: size = " <<
        mem_buf_ptr->membuf().size() << " < " <<
        version_head_size;
      throw Exception(ostr);
    }

    try
    {
      PassbackInfoVersionReader version_reader(
        mem_buf_ptr->membuf().data(),
        version_head_size);

      if(version_reader.version() != CURRENT_PASSBACK_PROFILE_VERSION)
      {
        Generics::SmartMemBuf_var result_mem_buf = Algs::copy_membuf(mem_buf_ptr);
        Generics::MemBuf& membuf = result_mem_buf->membuf();

        unsigned long current_version = version_reader.version();

        if(current_version == 32)
        {
          current_version = 33;

          AdServer::RequestInfoSvcs::PassbackInfoWriter new_writer;
          AdServer::RequestInfoSvcs_v32::PassbackInfoReader old_reader(
            membuf.data(), membuf.size());
          new_writer.version() = 33;
          new_writer.request_id() = old_reader.request_id();
          new_writer.tag_id() = old_reader.tag_id();
          new_writer.size_id() = 0;
          new_writer.colo_id() = old_reader.colo_id();
          new_writer.time() = old_reader.time();
          new_writer.done() = old_reader.done();
          new_writer.verified() = old_reader.verified();
          new_writer.user_status() = old_reader.user_status();
          new_writer.country() = old_reader.country();
          new_writer.ext_tag_id() = old_reader.ext_tag_id();

          Generics::MemBuf mb(new_writer.size());
          new_writer.save(mb.data(), mb.size());
          membuf.assign(mb.data(), mb.size());
        }

        if(current_version != CURRENT_PASSBACK_PROFILE_VERSION)
        {
          Stream::Error ostr;
          ostr << FUN << ": Unknown passback profile version: " << current_version;
          throw Exception(ostr);
        }

        return Generics::transfer_membuf(result_mem_buf);
      }
    }
    catch(const eh::Exception& ex)
    {
      Stream::Error ostr;
      ostr << FUN << ": Can't adapt profile: " << ex.what();
      throw Exception(ostr);
    }

    return ReferenceCounting::add_ref(mem_buf_ptr);
  }
} /*RequestInfoSvcs*/
} /*AdServer*/
