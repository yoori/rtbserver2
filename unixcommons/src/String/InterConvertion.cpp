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
 * @file   InterConvertion.hpp
 * @author Andrey Gusev
 *
 * Contains international conversion interface
 */
#include <errno.h>

#include <String/InterConvertion.hpp>

#include <Generics/Function.hpp>

#include <Stream/MemoryStream.hpp>


namespace String
{
  namespace International
  {
    const iconv_t Convertion::INVALID_ =
      reinterpret_cast<const iconv_t>(-1);

    void
    Convertion::set_encodings(const char* to_code, const char* from_code)
      /*throw (NotSupported)*/
    {
      if (fd_ != INVALID_)
      {
        iconv_close(fd_);
        mult_ = 1;
      }
      fd_ = iconv_open(to_code, from_code);
      if (fd_ == INVALID_)
      {
        Stream::Error ostr;
        ostr << FNS << "Encoding to '" << to_code << "' from '" <<
          from_code << "' not supported";
        throw NotSupported(ostr);
      }
    }

    void
    Convertion::encode(const char* input_chars, size_t count,
      std::string& out) /*throw (eh::Exception, BadSequence)*/
    {
      if (count)
      {
        size_t left_in, left_out;
        char* in_buf = const_cast<char*>(input_chars);
        char* out_buf;
        left_in = count;
        left_out = count * mult_;
        out.resize(left_out);
        out_buf = &out[0];
        while (iconv(fd_, &in_buf, &left_in, &out_buf, &left_out) ==
          static_cast<size_t>(-1))
        {
          if (errno == E2BIG)
          {
            out.resize(out.size() + count);
            left_out += count;
            out_buf = &out[out.size() - left_out];
            mult_++;
            continue;
          }
          Stream::Error ostr;
          ostr << FNS << "Bad characters sequence.";
          throw BadSequence(ostr);
        }
      }
    }
  }//namespace international
}//namespace String
