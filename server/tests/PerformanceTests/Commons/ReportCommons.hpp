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

#ifndef _REPORTCOMMONS_HPP
#define _REPORTCOMMONS_HPP

#include "StatCommons.hpp"
#include <eh/Exception.hpp>


// Utils

void print_line(std::ostream& out, unsigned short line_lendth);
void print_time(std::ostream& out, const Generics::Time& time);
void print_header(std::ostream& out, const char* header, unsigned short width);
    
/**
 * @class DumpInterface
 * @brief Interface for dumping statistics object
 */
class DumpInterface
{
public:
  static const unsigned short INDENTION = 15;

  static const unsigned short LINE_LENGTH = 120;
  
public:
  virtual ~DumpInterface() noexcept
  {}

  /**
   * @brief dump
   * @param output stream
   */  
  virtual std::ostream& dump(std::ostream& out) const;

protected:
  /**
   * @brief dump header
   * @param output stream
   */  
  virtual std::ostream& dump_header(std::ostream& out) const;

  /**
   * @brief dump body
   * @param output stream
   */  
  virtual std::ostream& dump_body(std::ostream& out) const;

  /**
   * @brief dump footer
   * @param output stream
   */  
  virtual std::ostream& dump_footer(std::ostream& out) const;

};

/**
 * @class DumpCounter
 * @brief Class for dumping simple counters
 */
class DumpCounter : public DumpInterface
{
public:
  /**
   * @brief Constructor.
   * @param statistics ref
   */
  DumpCounter(const Counter& counter);

  /**
   * @brief Destructor
   */
  ~DumpCounter() noexcept;

protected:
  /**
   * @brief dump body
   * @param output stream
   */  
  virtual std::ostream& dump_body(std::ostream& out) const;  
  
private:
  const Counter& counter_;   
};

/**
 * @class DumpPercenageCounter
 * @brief Class for dumping counters in percentage form
 */
class DumpPercentageCounter : public DumpInterface
{
public:
  /**
   * @brief Constructor.
   * @param statistics ref
   */
  DumpPercentageCounter(const Counter& counter);

  /**
   * @brief Destructor
   */
  ~DumpPercentageCounter() noexcept;

protected:
  /**
   * @brief dump body
   * @param output stream
   */  
  virtual std::ostream& dump_body(std::ostream& out) const;  
  
private:
  const Counter& counter_;   
};

/**
 * @class DumpRangeStats
 * @brief Class for dumping range statistics
 */
class DumpRangeStats : public DumpInterface
{
public:
  /**
   * @brief Constructor.
   * @param statistics ref
   * @param dump short form of range stats
   */
  DumpRangeStats(const RangeStats& stats,
                 bool short_form = false);

  /**
   * @brief Destructor
   */
  ~DumpRangeStats() noexcept;

protected:

  /**
   * @brief dump body
   * @param output stream
   */  
  virtual std::ostream& dump_body(std::ostream& out) const;  
  
private:
  const RangeStats& stats_;
  bool short_form_;
};


/**
 * @class DumpPerformanceStats
 * @brief Class for dumping performance statistics
 */
class DumpPerformanceStats: public DumpInterface
{
public:

  static const unsigned short INDENTION = 20;

  static const unsigned short LINE_LENGTH = 120;

  
public:
  /**
   * @brief Constructor.
   * @param statistics ref
   */
  DumpPerformanceStats(const PerformanceStatisticsBase& stats,
                       const char* header);

  /**
   * @brief Destructor
   */
  ~ DumpPerformanceStats() noexcept;

protected:

  /**
   * @brief dump header
   * @param output stream
   */  
  virtual std::ostream& dump_header(std::ostream& out) const;

  /**
   * @brief dump body
   * @param output stream
   */  
  virtual std::ostream& dump_body(std::ostream& out) const;  
  
private:
  const PerformanceStatisticsBase& stats_;
  std::string header_;
};

inline
std::ostream& 
operator<< (std::ostream& out, const DumpInterface& obj)
{
  return obj.dump(out);
}

#endif  // _REPORTCOMMONS_HPP
