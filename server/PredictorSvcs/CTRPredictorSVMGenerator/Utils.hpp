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
/* $Id: Utils.hpp 185976 2020-07-01 22:11:23Z jurij_kuznecov $
* @file Utils.hpp
* @author Artem V. Nikitin (artem_nikitin@ocslab.com)
* Utils
*/

#include <Logger/Logger.hpp>
#include <string>
#include <list>

#pragma once

namespace AdServer
{
  namespace Predictor
  {

    static const char ASPECT[] = "CTRPredictorSVMGenerator";
    static const char CSV_EXTENSION[] = ".csv";
    static const char DICT_EXTENSION[] = ".dict";
    static const char LIBSVM_EXTENSION[] = ".libsvm";
    static const char LIBSVM_FILENAME_TIME_FORMAT[] = "%Y%m%d%H%M%S";
    static const char CSV_MASK[] = "PRImpression_*.csv";

    typedef std::list<std::string> FileList;

    /**
     * @brief remove extension from file name.
     *
     * @param file name
     */
    std::string remove_ext(
      const std::string& filename);

    /**
     * @brief remove files by mask.
     *
     * @param path
     * @param mask
     * @param logger
     */
    void
    remove_files (
      const char* path,
      const char* mask,
      Logging::Logger* logger) noexcept;

    /**
     * @brief remove obsolete files by mask.
     *
     * @param path
     * @param mask
     * @param interval to keep fresh files
     * @param logger
     */
    void
    remove_obsolete_files(
      const char* path,
      const char* mask,
      Generics::Time keep_interval,
      Logging::Logger* logger) noexcept;
  }
}
