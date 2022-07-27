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
#ifndef STREAM_FILE_STREAMBUF_HPP
#define STREAM_FILE_STREAMBUF_HPP

#include <memory>
#include <streambuf>

#include <Generics/ArrayAutoPtr.hpp>
#include <Generics/Uncopyable.hpp>


namespace Stream
{
  namespace File
  {
    struct IO : private Generics::Uncopyable
    {
      virtual
      ~IO() throw ();

      virtual
      size_t
      read(void* buf, size_t size) /*throw (eh::Exception)*/ = 0;

      virtual
      void
      write(const void* buf, size_t size) /*throw (eh::Exception)*/ = 0;
    };

    class InStreamBuf :
      public std::basic_streambuf<char, std::char_traits<char> >,
      private Generics::Uncopyable
    {
    public:
      DECLARE_EXCEPTION(Exception, eh::DescriptiveException);
      DECLARE_EXCEPTION(InvalidArgument, Exception);
      DECLARE_EXCEPTION(Underflow, Exception);

      InStreamBuf(IO* io, size_t buffer_size, size_t put_back_size)
        /*throw (InvalidArgument, eh::Exception)*/;

      virtual
      int_type
      underflow() /*throw (Underflow, eh::Exception)*/;

    private:
      const std::unique_ptr<IO> IO_;
      const size_t BUFFER_SIZE_;
      const size_t PUT_BACK_SIZE_;
      Generics::ArrayChar in_buffer_;
    };

    class OutStreamBuf :
      public std::basic_streambuf<char, std::char_traits<char> >,
      private Generics::Uncopyable
    {
    public:
      DECLARE_EXCEPTION(Exception, eh::DescriptiveException);
      DECLARE_EXCEPTION(InvalidArgument, Exception);
      DECLARE_EXCEPTION(Overflow, Exception);

      OutStreamBuf(IO* io, size_t buffer_size)
        /*throw (InvalidArgument, eh::Exception)*/;

      virtual
      ~OutStreamBuf() throw ();

      virtual
      int_type
      overflow(int_type c = traits_type::eof())
        /*throw (Overflow, eh::Exception)*/;

      const std::unique_ptr<IO> IO_;
      const size_t BUFFER_SIZE_;
      Generics::ArrayChar out_buffer_;
    };
  }
}

#endif
