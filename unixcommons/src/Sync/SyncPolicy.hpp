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
 * @file   SyncPolicy.hpp
 * @author Karen Aroutiounov
 */

#ifndef SYNC_SYNC_POLICY_HPP
#define SYNC_SYNC_POLICY_HPP

#include <Sync/PosixLock.hpp>


namespace Sync
{
  namespace Policy
  {
    template <typename AdoptedMutex, typename AdoptedReadGuard,
      typename AdoptedWriteGuard>
    class PolicyAdapter
    {
    public:
      typedef AdoptedMutex Mutex;
      typedef AdoptedReadGuard ReadGuard;
      typedef AdoptedWriteGuard WriteGuard;
    };

    typedef PolicyAdapter<PosixMutex, PosixGuard, PosixGuard>
      PosixThread;
    typedef PolicyAdapter<PosixSpinLock, PosixSpinGuard, PosixSpinGuard>
      PosixSpinThread;
    typedef PolicyAdapter<PosixRWLock, PosixRGuard, PosixWGuard>
      PosixThreadRW;
  }
}

#endif
