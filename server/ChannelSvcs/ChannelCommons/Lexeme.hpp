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
#ifndef AD_SERVER_CHANNELSVCS_LEXEME_HPP__
#define AD_SERVER_CHANNELSVCS_LEXEME_HPP__

#include<vector>
#include<String/SubString.hpp>
#include<ReferenceCounting/AtomicImpl.hpp>
#include<ReferenceCounting/SmartPtr.hpp>

namespace AdServer
{
namespace ChannelSvcs
{
  struct LexemeData
  {
    typedef std::vector<Generics::SubStringHashAdapter> Forms;
    std::string data;
    Forms forms;
  };

  class Lexeme:
    public LexemeData,
    public ReferenceCounting::AtomicImpl
  {
  public:
    size_t memory_size() const noexcept;

  private:
    virtual ~Lexeme() noexcept {};
  };

  typedef ReferenceCounting::SmartPtr<Lexeme> Lexeme_var;
}
}

namespace AdServer
{
namespace ChannelSvcs
{
  inline
  size_t Lexeme::memory_size() const noexcept
  {
    return sizeof(Lexeme) + data.capacity() +
      forms.capacity() * sizeof(String::SubString);
  }
}
}
#endif //CHANNELSVCS_LEXEME_HPP__

