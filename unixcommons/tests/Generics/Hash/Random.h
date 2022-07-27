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
#pragma once

#include "Types.h"

//-----------------------------------------------------------------------------
// Xorshift RNG based on code by George Marsaglia
// http://en.wikipedia.org/wiki/Xorshift

struct Rand
{
  uint32_t x;
  uint32_t y;
  uint32_t z;
  uint32_t w;

  Rand()
  {
    reseed(uint32_t(0));
  }

  Rand( uint32_t seed )
  {
    reseed(seed);
  }

  void reseed ( uint32_t seed )
  {
    x = 0x498b3bc5 ^ seed;
    y = 0;
    z = 0;
    w = 0;

    for(int i = 0; i < 10; i++) mix();
  }

  void reseed ( uint64_t seed )
  {
    x = 0x498b3bc5 ^ (uint32_t)(seed >>  0);
    y = 0x5a05089a ^ (uint32_t)(seed >> 32);
    z = 0;
    w = 0;

    for(int i = 0; i < 10; i++) mix();
  }

  //-----------------------------------------------------------------------------

  void mix ( void )
  {
    uint32_t t = x ^ (x << 11);
    x = y; y = z; z = w;
    w = w ^ (w >> 19) ^ t ^ (t >> 8);
  }

  uint32_t rand_u32 ( void )
  {
    mix();

    return x;
  }

  uint64_t rand_u64 ( void )
  {
    mix();

    uint64_t a = x;
    uint64_t b = y;

    return (a << 32) | b;
  }

  void rand_p ( void * blob, int bytes )
  {
    uint32_t * blocks = reinterpret_cast<uint32_t*>(blob);

    while(bytes >= 4)
    {
      uint32_t r = rand_u32();
      memcpy(blocks, &r, 4);
      blocks++;
      bytes -= 4;
    }

    uint8_t * tail = reinterpret_cast<uint8_t*>(blocks);

    for(int i = 0; i < bytes; i++)
    {
      tail[i] = (uint8_t)rand_u32();
    }
  }
};

//-----------------------------------------------------------------------------

extern Rand g_rand1;

inline uint32_t rand_u32 ( void ) { return g_rand1.rand_u32(); }
inline uint64_t rand_u64 ( void ) { return g_rand1.rand_u64(); }

inline void rand_p ( void * blob, int bytes )
{
  uint32_t * blocks = (uint32_t*)blob;

  while(bytes >= 4)
  {
    *blocks++ = rand_u32();
    bytes -= 4;
  }

  uint8_t * tail = (uint8_t*)blocks;

  for(int i = 0; i < bytes; i++)
  {
    tail[i] = (uint8_t)rand_u32();
  }
}

//-----------------------------------------------------------------------------
