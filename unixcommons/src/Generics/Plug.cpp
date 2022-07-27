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
#include <cstdlib>


extern "C"
{
#define FUNC(x) \
void \
x(void) \
{ \
  std::abort(); \
}

  FUNC(boot_DynaLoader)

  FUNC(perl_parse)
  FUNC(Perl_newXS)
  FUNC(perl_alloc)
  FUNC(perl_free)
  FUNC(perl_run)
  FUNC(Perl_eval_pv)
  FUNC(perl_destruct)
  FUNC(perl_construct)

  FUNC(rpmReadConfigFiles)
  FUNC(rpmGetPath)
  FUNC(rpmdbOpen)
  FUNC(rpmdbClose)
  FUNC(rpmdbInitIterator)
  FUNC(rpmdbFreeIterator)
  FUNC(rpmdbNextIterator)
  FUNC(rpmdbGetIteratorOffset)

  FUNC(sensors_init)
  FUNC(sensors_get_feature)
  FUNC(sensors_get_all_features)
  FUNC(sensors_get_label)
  FUNC(sensors_get_detected_chips)

  FUNC(hosts_ctl)
}
