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
// Common/UTF8TreeLoader.hpp
#ifndef _UTF8_TREE_LOADER_HPP_INCLUDED_
#define _UTF8_TREE_LOADER_HPP_INCLUDED_

#include <fstream>
#include <sstream>
#include <iostream>

#include <eh/Exception.hpp>

#include <String/UTF8Category.hpp>
#include <String/UnicodeSymbol.hpp>

namespace Utf8Loading
{
  DECLARE_EXCEPTION(FileOpenError, eh::DescriptiveException);

  template <typename Container>
  void
  load_properties(const char* file_name, Container& container)
    /*throw (eh::Exception, FileOpenError)*/;
}

//////////////////////////////////////////////////////////////////////////
//    Implementation
//////////////////////////////////////////////////////////////////////////
namespace Utf8Loading
{
  template <typename Container>
  void
  load_properties(const char* file_name, Container& container)
    /*throw (eh::Exception, FileOpenError)*/
  {
    std::ifstream ifs(file_name);
    if (!ifs)
    {
      Stream::Error ostr;
      ostr << "File " << file_name << " open error";
      throw FileOpenError(ostr);
    }

    while (ifs)
    {
      std::string line;
      std::getline(ifs, line);

      if (line.empty() || !isalnum(line[0]))
      {
        continue;
      }

      Stream::Parser sstr(line);

      String::UnicodeSymbol first;
      sstr >> first;
      if (!sstr)
      {
        break; // or failed on broken file ?
      }

      if (sstr.get() == '-')
      {
        String::UnicodeSymbol second;

        sstr >> second;
        if (sstr.fail())
        {
          break; // or failed on broken file ?
        }
        container.insert(first, second);
      }
      else
      {
        container.insert(first, first);
      }
    }
  }
}

#endif  //_UTF8_TREE_LOADER_HPP_INCLUDED_
