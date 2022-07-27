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

#ifndef __AUTOTESTS_COMMONS_ADMINS_FREQCAPCHECKER_HPP
#define __AUTOTESTS_COMMONS_ADMINS_FREQCAPCHECKER_HPP

#include <tests/AutoTests/Commons/Admins/FreqCapAdmin.hpp>
#include <tests/AutoTests/Commons/Checkers/AdminsChecker.hpp>
#include <tests/AutoTests/Commons/Checkers/Checker.hpp>

namespace AutoTest
{
  template<typename ExpectedType = FreqCapAdmin::Expected>  
  class FreqCapChecker_:  
    public AutoTest::Checker  
  {  
    public:    

      typedef ExpectedType Expected;      

      FreqCapChecker_(      
        BaseUnit* test,      
        unsigned long freqcap,      
        const Expected& expected,      
        AdminExistCheck exists = AEC_EXISTS) :      
        test_(test),      
        freqcap_(freqcap),      
        expected_(expected),      
        exists_(exists)      
        {}      

      virtual ~FreqCapChecker_() noexcept {}      

      bool check(bool throw_error = true) /*throw (CheckFailed, eh::Exception)*/;      

    private:    

      BaseUnit* test_;      
      unsigned long freqcap_;      
      Expected expected_;      
      AdminExistCheck exists_;      

  };  

  typedef FreqCapChecker_<FreqCapAdmin::Expected> FreqCapChecker;  
  typedef FreqCapChecker_<std::string> FreqCapCheckerSimple;  

}

#include "FreqCapChecker.tpp"

#endif  // __AUTOTESTS_COMMONS_ADMINS_FREQCAPCHECKER_HPP

