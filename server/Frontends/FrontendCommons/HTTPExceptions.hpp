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
#include <eh/Exception.hpp>

namespace FrontendCommons
{
  /**
   * Front-ends have constraints for serving HTTP requests and parameters
   * in HTTP requests. Some structs reused while checking this constraints.
   * HTTPExceptions control exceptions declaration.
   */

  struct HTTPExceptions
  {
    DECLARE_EXCEPTION(Exception, eh::DescriptiveException);
    DECLARE_EXCEPTION(InvalidParamException, Exception);
    DECLARE_EXCEPTION(ForbiddenException, Exception);
    // Use if need separate case when size of parameter is correct,
    // but value is invalid
    DECLARE_EXCEPTION(BadParameter, Exception);
  };
}
