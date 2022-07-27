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
 * @file   CRC.hpp
 * @author Karen Aroutiounov
 */

#ifndef GENERICS_CRC_HPP
#define GENERICS_CRC_HPP

#include <cstddef>
#include <cstdint>


namespace Generics
{
  namespace CRC
  {
    /**
     * Calculates CRC32 of the supplied data
     * @param crc initial value of CRC
     * @param data data block
     * @param size its size
     */
    uint32_t
    quick(uint32_t crc, const void* data, size_t size) throw ();

    /**
     * Calculates reversed CRC32 of the supplied data
     * @param crc initial value of CRC
     * @param data data block
     * @param size its size
     */
    uint32_t
    reversed(uint32_t crc, const void* data, size_t size) throw ();
  }
}


namespace Generics
{
  namespace CRC
  {
    extern const uint32_t CRC_QUICK_TABLE[];

    inline
    uint32_t
    quick(uint32_t crc, const void* data, size_t size)
      throw ()
    {
      register const uint8_t* udata = static_cast<const uint8_t*>(data);
      while (size-- > 0)
      {
        crc = (crc << 8) ^
          CRC_QUICK_TABLE[static_cast<uint8_t>(crc >> 24) ^ *udata++];
      }
      return crc;
    }

    extern const uint32_t CRC_REVERSED_TABLE[];

    inline
    uint32_t
    reversed(uint32_t crc, const void* data, size_t size)
      throw ()
    {
      register const uint8_t* udata = static_cast<const uint8_t*>(data);
      crc = ~crc;
      while (size-- > 0)
      {
        crc = (crc >> 8) ^
          CRC_REVERSED_TABLE[static_cast<uint8_t>(crc) ^ *udata++];
      }
      return ~crc;
    }
  }
}

#endif
