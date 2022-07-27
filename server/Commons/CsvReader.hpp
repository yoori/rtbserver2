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
#ifndef CSVREADER_HPP
#define CSVREADER_HPP

#include <iostream>
#include <eh/Exception.hpp>
#include <Stream/MemoryStream.hpp>
#include <String/AsciiStringManip.hpp>
#include <String/SubString.hpp>

namespace Commons
{
  class CsvReader
  {
  public:
    DECLARE_EXCEPTION(Exception, eh::DescriptiveException);

  public:
    template<typename ContainerType>
    static void
    parse_line(ContainerType& container, const String::SubString& line)
      /*throw(Exception)*/;

  protected:
    static const String::AsciiStringManip::CharCategory Q_CHARS_;
    static const String::AsciiStringManip::CharCategory P_CHARS_;
  };
}

namespace Commons
{
  template<typename ContainerType>
  void
  CsvReader::parse_line(ContainerType& container, const String::SubString& line)
    /*throw(Exception)*/
  {
    String::SubString::ConstPointer pos = line.begin();
    String::SubString::ConstPointer pre_end = line.end();
    --pre_end;

    while(pos != line.end())
    {
      // process value
      bool quota_opened = false;

      if(pos != pre_end && *pos == '"')
      {
        quota_opened = true;
        ++pos;
        if(pos == line.end())
        {
          Stream::Error ostr;
          ostr << "unexpected end of line";
          throw Exception(ostr);
        }
      }

      if(quota_opened)
      {
        // find quota end
        std::string res_value;
        String::SubString::ConstPointer block_begin_pos = pos;
        while(true)
        {
          pos = Q_CHARS_.find_owned(block_begin_pos, line.end());
          res_value += String::SubString(block_begin_pos, pos).str();
          if(pos == line.end())
          {
            break;
          }
          else if(*(pos + 1) != '"')
          {
            pos += 1;
            break;
          }

          res_value += "\"";
          block_begin_pos = pos + 2;
        }

        if(pos != line.end() && *pos != ',')
        {
          Stream::Error ostr;
          ostr << "expected field separator after value close";
          throw Exception(ostr);
        }

        container.insert(container.end(), res_value);
      }
      else // no quota
      {
        String::SubString::ConstPointer end_pos = P_CHARS_.find_owned(pos, line.end());
        container.insert(container.end(), String::SubString(pos, end_pos).str());
        pos = end_pos;
      }

      if(pos != line.end())
      {
        ++pos;
        if(pos == line.end())
        {
          container.insert(container.end(), std::string());
        }
      }
    }
  }
}

#endif /*CSVREADER_HPP*/
