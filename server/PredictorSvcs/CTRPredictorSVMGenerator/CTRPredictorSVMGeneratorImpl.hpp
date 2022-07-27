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
/* $Id: CTRPredictorSVMGeneratorImpl.hpp 185978 2020-07-04 00:12:49Z jurij_kuznecov $
* @file CTRPredictorSVMGeneratorImpl.hpp
* @author Artem V. Nikitin (artem_nikitin@ocslab.com)
* Predictor CTR lobsvm generator implemenation
*/
#pragma once

#include <Generics/Time.hpp>
#include <Commons/DelegateActiveObject.hpp>
#include <Logger/Logger.hpp>
#include <Sync/PosixLock.hpp>
#include <Sync/Condition.hpp>
#include <Sync/SyncPolicy.hpp>
#include <Utils/CTRGenerator/CTRGenerator.hpp>
#include "FeatureContainer.hpp"

namespace AdServer
{
  namespace Predictor
  {
    /**
     * CTRPredictorSVMGenerator service implementation
     */
    class CTRPredictorSVMGeneratorImpl: public Commons::DelegateActiveObject
    {
      
    public:

      /**
       * @brief Constructor.
       *
       * @param logger
       * @param active object callback
       * @param input path (PRImpression - csv-files folder)
       * @param output path (LibSVM - libsvm-files folder)
       * @param days to keep files
       * @param feature dimension from the config
       */
      CTRPredictorSVMGeneratorImpl(
        Logging::Logger* logger,
        Generics::ActiveObjectCallback* callback,
        const char* input_path,
        const char* output_path,
        unsigned long days_to_keep,
        unsigned long feature_dimension)
        /*throw (eh::Exception)*/;

    private:
      
      /**
       * @brief Main working cycle.
       */
      void
      work_() noexcept;

      /**
       * @brief Termination.
       */
      virtual void
      terminate_() noexcept;

      /**
       * @brief Process csv files.
       */
      void process_files_() noexcept;
      
    protected:
      /**
       * @brief Destructor.
       */
      virtual
      ~CTRPredictorSVMGeneratorImpl() noexcept;

    private:
      typedef Sync::Policy::PosixThread SyncPolicy;

      SyncPolicy::Mutex timeout_cond_lock_;
      Sync::Conditional timeout_condition_;
      Logging::Logger_var logger_;
      const std::string input_path_;
      const std::string output_path_;
      const Generics::Time keep_interval_;
      unsigned long feature_dimension_;
    };
  }
}


