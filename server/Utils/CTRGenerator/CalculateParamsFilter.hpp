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

#include "CTRGenerator.hpp"
#include <Generics/BitAlgs.hpp>

namespace AdServer
{
  namespace CampaignSvcs
  {
    class CalculateParamsFiller
    {
    public:
      static const unsigned long BF_TIMESTAMP;
      static const unsigned long BF_LINK;
    
      CalculateParamsFiller();
      
      void
      set_value(
        CTRGenerator::CalculateParams& calc_params,
        unsigned long basic_feature, // CTR::BasicFeature + syntetic features
        const String::SubString& str);
      
    protected:
      class CalcParamFiller: public ReferenceCounting::AtomicImpl
      {
      public:
        virtual void
        set_value(
          CTRGenerator::CalculateParams& calc_params,
          const String::SubString& str) = 0;
        
      protected:
        virtual
        ~CalcParamFiller() noexcept = default;
      };
      
      typedef ReferenceCounting::SmartPtr<CalcParamFiller>
      CalcParamFiller_var;
      
      typedef std::vector<CalcParamFiller_var> CalcParamFillerArray;
    
      template<typename IntType>
      class CalcParamFillerIntImpl: public CalcParamFiller
      {
      public:
        CalcParamFillerIntImpl(
          IntType CTRGenerator::CalculateParams::* field);
        
        virtual void
        set_value(
          CTRGenerator::CalculateParams& calc_params,
          const String::SubString& str);
        
      protected:
        virtual
        ~CalcParamFillerIntImpl() noexcept = default;
        
        IntType CTRGenerator::CalculateParams::* field_;
      };
      
      class CampaignFreqFiller: public CalcParamFiller
      {
      public:
        CampaignFreqFiller();
      
        virtual void
        set_value(
          CTRGenerator::CalculateParams& calc_params,
          const String::SubString& str);
      
      protected:
        virtual
        ~CampaignFreqFiller() noexcept = default;
      };
      
      class CalcParamFillerStringImpl: public CalcParamFiller
      {
      public:
        CalcParamFillerStringImpl(
          std::string CTRGenerator::CalculateParams::* field);
      
        virtual void
        set_value(
          CTRGenerator::CalculateParams& calc_params,
          const String::SubString& str);
      
      protected:
        virtual
        ~CalcParamFillerStringImpl() noexcept = default;
      
        std::string CTRGenerator::CalculateParams::* field_;
      };
    
      class CalcParamFillerIntListImpl: public CalcParamFiller
      {
      public:
        CalcParamFillerIntListImpl(
          CTRGenerator::IdSet CTRGenerator::CalculateParams::* field);
      
        virtual void
        set_value(
          CTRGenerator::CalculateParams& calc_params,
          const String::SubString& str);

      protected:
        virtual
        ~CalcParamFillerIntListImpl() noexcept = default;
      
        CTRGenerator::IdSet CTRGenerator::CalculateParams::* field_;
      };
    
      class CalcParamFillerTimestampImpl: public CalcParamFiller
      {
      public:
        CalcParamFillerTimestampImpl();
      
        virtual void
        set_value(
          CTRGenerator::CalculateParams& calc_params,
          const String::SubString& str);
      
      protected:
        virtual
        ~CalcParamFillerTimestampImpl() noexcept = default;
      };

      struct LinkFillerImpl: public CalcParamFiller
      {
      public:
        LinkFillerImpl();

        virtual void
        set_value(
          CTRGenerator::CalculateParams& calc_params,
          const String::SubString& str);
      };
    
    protected:
      CalcParamFillerArray processors_;
    };
  }
}

#include "CalculateParamsFilter.tpp"
