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
 * @file   Stream/GzipStreams.hpp
 * @author Dmitry Trifilov
 */
#ifndef STREAM_GZIP_STREAMS_HPP
#define STREAM_GZIP_STREAMS_HPP

#include <istream>
#include <ostream>

#include <Stream/FileStreamBuf.hpp>


namespace Stream
{
  /**
   * Stream with std::istream interface to read gzip'ed files
   */
  class GzipInStream :
    public std::basic_istream<char, std::char_traits<char> >
  {
  public:
    /**
     * Constructor transmit parameters to GzipInStreambuf constructor
     * (aggregated member)
     * @param gzip_file_name File name to read and decompress data
     * @param buffer_size Memory size to be allocate for read data buffer
     * @param put_back_size The size of the data obtained in the previous
     * decompression query saved before new decompression. Each time buffer
     * will contain put_back_size bytes early loaded data.
     */
    explicit
    GzipInStream(const char* gzip_file_name,
      size_t buffer_size = 64 * 1024,
      size_t put_back_size = 64)
      /*throw (eh::Exception)*/;

  protected:
    File::InStreamBuf buf_;
  };

  /**
   * Stream with std::ostream interface to write gzip'ed files
   */
  class GzipOutStream :
    public std::basic_ostream<char, std::char_traits<char> >
  {
  public:
    /**
     * Constructor transmit parameters to GzipOutStreambuf constructor
     * (aggregated member)
     * @param gzip_file_name File name to read and decompress data
     * @param buffer_size Memory size to be allocate for write data buffer
     */
    explicit
    GzipOutStream(const char* gzip_file_name,
      size_t buffer_size = 64 * 1024)
      /*throw (eh::Exception)*/;

  protected:
    File::OutStreamBuf buf_;
  };
}

#endif
