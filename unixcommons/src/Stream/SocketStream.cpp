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
/**
 * @file   Stream/SocketStream.cpp
 * @author Pavel Gubin
 */

#include <Stream/SocketStream.hpp>


namespace Stream
{
  //
  // SocketStreambuf
  //

  const size_t SocketStreambuf::IN_BUFFER_SIZE;
  const size_t SocketStreambuf::OUT_BUFFER_SIZE;
  const size_t SocketStreambuf::PUTBACK_SIZE;

  SocketStreambuf::SocketStreambuf(ACE_SOCK_Stream& sock_stream,
    std::ios_base::openmode mode, const Generics::Time* send_timeout,
    const Generics::Time* recv_timeout)
    : sock_stream_(sock_stream),
      send_timeout_(send_timeout ? new ACE_Time_Value(*send_timeout) : 0),
      recv_timeout_(recv_timeout ? new ACE_Time_Value(*recv_timeout) : 0),
      in_buffer_(0), out_buffer_(0), bytes_sent_(0), bytes_received_(0)
  {
    if ((mode & std::ios_base::in) == std::ios_base::in)
    {
      in_buffer_.reset(IN_BUFFER_SIZE);
    }

    if ((mode & std::ios_base::out) == std::ios_base::out)
    {
      out_buffer_.reset(OUT_BUFFER_SIZE);
    }
  }

  SocketStreambuf::~SocketStreambuf()
  {
  }

  std::streamsize
  SocketStreambuf::showmanyc()
  {
    return egptr() - gptr();
  }

  SocketStreambuf::int_type
  SocketStreambuf::underflow()
  {
    if (gptr() < egptr())
    {
      return traits_type::to_int_type(*gptr());
    }

    size_t num_putback = gptr() - eback();
    if (num_putback > PUTBACK_SIZE)
    {
      num_putback = PUTBACK_SIZE;
    }

    memmove(in_buffer_.get() + (PUTBACK_SIZE - num_putback),
      gptr() - num_putback, num_putback);

    int num = sock_stream_.recv(in_buffer_.get() + PUTBACK_SIZE,
      IN_BUFFER_SIZE - PUTBACK_SIZE, recv_timeout_.get());

    if (num <= 0)
    {
      return traits_type::eof();
    }

    bytes_received_ += num;

    setg(in_buffer_.get() + (PUTBACK_SIZE - num_putback),
      in_buffer_.get() + PUTBACK_SIZE, in_buffer_.get() + PUTBACK_SIZE + num);

    return traits_type::to_int_type(*gptr());
  }


  //
  // SocketInStream
  //

  SocketInStream::SocketInStream(ACE_SOCK_Stream& sock_stream,
    const Generics::Time* recv_timeout)
    : std::basic_istream<char, std::char_traits<char> >(0),
      buf_(sock_stream, std::ios_base::in, 0, recv_timeout)
  {
    init(&buf_);
  }
}
