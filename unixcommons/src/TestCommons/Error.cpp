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
#include <TestCommons/Error.hpp>


namespace TestCommons
{
  void
  Errors::add(const String::SubString& error, bool write) throw ()
  {
    try
    {
      {
        std::string key(error.data(), error.size());
        Sync::PosixGuard guard(mutex_);
        errors_[key]++;
      }

      if (write)
      {
        std::cerr << error << std::endl;
      }
    }
    catch (...)
    {
    }
  }

  void
  Errors::print() const throw ()
  {
    print(std::cout);
  }

  void
  Errors::print(std::ostream& ostr) const throw ()
  {
    Sync::PosixGuard guard(mutex_);

    if (errors_.empty())
    {
      ostr << "    None" << std::endl;
    }
    else
    {
      for (AllErrors::const_iterator itor(errors_.begin());
        itor != errors_.end(); ++itor)
      {
        ostr << "    " << itor->second << ": " << itor->first
          << std::endl;
      }
    }
  }
}
