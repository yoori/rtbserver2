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

#ifndef AD_SERVER_CONTAINER_MATCHERS_HPP
#define AD_SERVER_CONTAINER_MATCHERS_HPP

#include <vector>
#include <ostream>
#include <set>
#include <eh/Exception.hpp>
#include <ChannelSvcs/ChannelCommons/CommonTypes.hpp>

namespace AdServer
{
namespace ChannelSvcs
{
  typedef std::set<unsigned int> ExcludeContainerType;

  class PositiveAtom
  {
  public:
    PositiveAtom(unsigned int c_id = 0, unsigned int t_id = 0) noexcept
      : channel_id(c_id), channel_trigger_id(t_id) {};
    bool operator<(const PositiveAtom& cp) const noexcept
    { 
      if(channel_id != cp.channel_id)
      {
        return channel_id < cp.channel_id;
      }
      return channel_trigger_id < cp.channel_trigger_id;
    }
    bool operator==(unsigned int id) const noexcept { return channel_id == id; }
    bool operator==(const PositiveAtom& id) const noexcept;
  public:
    unsigned int channel_id;
    unsigned int channel_trigger_id;
  };

  typedef std::vector<PositiveAtom> PositiveContainerType;

}// namespace ChannelSvcs
}// namespace AdServer

namespace AdServer
{
  namespace ChannelSvcs
  {

  inline
  bool PositiveAtom::operator==(const PositiveAtom& id) const noexcept
  {
    return channel_id == id.channel_id &&
      channel_trigger_id == id.channel_trigger_id;
  }

  inline
  bool operator<(const PositiveAtom& cp1, unsigned int cp2) noexcept
  {
    return cp1.channel_id < cp2;
  }

  inline
  bool operator<(unsigned int cp1, const PositiveAtom& cp2) noexcept
  {
    return cp1 < cp2.channel_id;
  }

  }// namespace ChannelSvcs
}// namespace AdServer

inline
std::ostream& operator<<(std::ostream& os, const AdServer::ChannelSvcs::PositiveAtom& atom) noexcept
{
  os << atom.channel_id << '(' << atom.channel_trigger_id << ")";
  return os;
}

#endif //AD_SERVER_CONTAINER_MATCHERS_HPP
