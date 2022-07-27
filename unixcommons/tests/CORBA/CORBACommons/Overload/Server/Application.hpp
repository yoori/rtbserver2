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
#ifndef TEST_CORBA_OVERLOAD_SERVER_APPLICATION_HPP
#define TEST_CORBA_OVERLOAD_SERVER_APPLICATION_HPP

#include <eh/Exception.hpp>

#include <CORBACommons/ProcessControlImpl.hpp>
#include <CORBACommons/CorbaAdapters.hpp>

#include "TestIntImpl.hpp"


class Application:
  public CORBACommons::ProcessControlImpl,
  private CORBATest::TestIntImpl::Callback
{
public:
  DECLARE_EXCEPTION(Exception, eh::DescriptiveException);

public:
  Application() /*throw (eh::Exception)*/;

  void
  run(int argc, char* argv[]) /*throw (Exception, eh::Exception)*/;

  void
  error(const char* message) throw ();

  virtual char*
  control(const char* param_name, const char* param_value) throw ();

protected:
  virtual
  ~Application() throw ();

private:
  bool error_state_;
};

#endif
