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
#include<iostream>
#include<Generics/Time.hpp>
#include <Frontends/FrontendCommons/OptOutManip.hpp> 


int main(int argc, char* argv[])
{
  if(argc>2)
  {
    std::cout << "usage OptOutTest [days]" << std::endl;
    return 1;
  }
  unsigned long days =0;
  if(argc==2)
  {
    std::stringstream convert;
    convert << argv[1];
    convert >> days;
  }
  std::cout << "days: " << days << std::endl;
  unsigned long tm = time(0);
  std::cout << "start time: " << tm << std::endl;
  tm += (days * 24 * 3600);
  std::cout << "time with ofset: " << tm << std::endl;
  Generics::Time opt_in_days_time(tm), restore_time;
  std::cout << "Time: " << opt_in_days_time << std::endl;
  std::string buf;
  AdServer::OptInDays::save_opt_in_days(opt_in_days_time, buf);
  AdServer::OptInDays::load_opt_in_days(buf.c_str(), restore_time);
  std::cout << "Restore time: " << restore_time << std::endl;
return 0;
}

