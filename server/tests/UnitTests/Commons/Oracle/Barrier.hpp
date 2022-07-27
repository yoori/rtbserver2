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
#ifndef BARRIER_HPP
#define BARRIER_HPP

#include <Generics/Uncopyable.hpp>
#include <pthread.h>

class Barrier: private Generics::Uncopyable
{
public:
  Barrier(unsigned int count) noexcept;

  ~Barrier() noexcept;

  bool wait() noexcept;

private:
  pthread_barrier_t barrier_;
};

inline
Barrier::Barrier(unsigned int count) noexcept
{
  pthread_barrier_init(&barrier_, NULL, count);
}

inline
Barrier::~Barrier() noexcept
{
  pthread_barrier_destroy(&barrier_);
}

inline
bool
Barrier::wait() noexcept
{
  int res = pthread_barrier_wait(&barrier_);
  return (res == PTHREAD_BARRIER_SERIAL_THREAD);
}

#endif  /*BARRIER_HPP*/
