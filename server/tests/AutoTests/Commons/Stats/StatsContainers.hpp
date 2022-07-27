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
#ifndef AUTOTESTS_COMMONS_STATS_STATSCONTAINERS_HPP
#define AUTOTESTS_COMMONS_STATS_STATSCONTAINERS_HPP

#include <list>
#include <tr1/array>

/**
 * StatsArray : fixed size stats container
 * StatsList : non fixed size stats container
 */
namespace AutoTest
{
namespace ORM
{
  template<typename StatsContainerType>
  class StatsContainerWrapper: public StatsContainerType
  {
  public:
    DECLARE_EXCEPTION(Exception, eh::DescriptiveException);

    typedef StatsContainerWrapper<StatsContainerType> Self;

    typedef typename StatsContainerType::value_type ElementType;
    typedef typename ElementType::diffs_type element_diffs_type;

  public:
    StatsContainerWrapper() {}

    StatsContainerWrapper(const StatsContainerWrapper& init);

    StatsContainerWrapper& operator=(const StatsContainerWrapper& init);

    bool operator==(const StatsContainerType& stats) const;

    bool operator!=(const StatsContainerType& stats) const;

    void print_idname(std::ostream& out) const;

    bool select(StatsDB::IConn& connection, bool initial = true);

    template<typename DiffType>
    static void print_each_diff(
      std::ostream& out,
      const DiffType& diff);

  protected:
    template<typename DiffIteratorType>
    static void print_diff_array_(
      std::ostream& out,
      DiffIteratorType diff_it,
      DiffIteratorType diff_end_it);

    template<typename IteratorType, typename DiffIteratorType>
    void print_diff_(
      std::ostream& out,
      IteratorType real_it,
      IteratorType real_end_it,
      DiffIteratorType diff_it,
      DiffIteratorType diff_end_it) const;

    // print difference between (*this)[i] + diff and (real_it, real_end_it)[i] (for all i)
    template<typename IteratorType, typename DiffType>
    void print_each_diff_(
      std::ostream& out,
      IteratorType real_it,
      IteratorType real_end_it,
      const DiffType& diff) const;
  };

  template<typename ValueType, std::size_t SIZE>
  struct FixedArray: public std::tr1::array<ValueType, SIZE>
  {};

  template<typename ValueType, std::size_t SIZE>
  class StatsArray:
    public StatsContainerWrapper<FixedArray<ValueType, SIZE> >
  {
  public:
    
    // print difference: (*this)[i] + diff[i] ? real[i]
    template<typename DiffType>
    void print_diff(
      std::ostream& out,
      const DiffType (&diff)[SIZE],
      const StatsArray<ValueType, SIZE>& real)
      const;

    // print difference: (*this)[i] + diff ? real[i]
    template<typename DiffType>
    void print_each_diff(
      std::ostream& out,
      const DiffType& diff,
      const StatsArray<ValueType, SIZE>& real)
      const;

    // print difference array
    template<typename DiffType>
    static void print_diff(
      std::ostream& out,
      const DiffType (&diff)[SIZE]);

    using StatsContainerWrapper<FixedArray<ValueType, SIZE> >::print_each_diff;
  };

  template<typename ValueType>
  struct StatsList:
    public StatsContainerWrapper<std::list<ValueType> >
  {
  public:
    
    template<typename StatsDiffContainerType, typename StatsContainerType>
    void print_diff(
      std::ostream& out,
      const StatsDiffContainerType& diffs,
      const StatsContainerType& real)
      const;

    template<typename StatsDiffContainerType>
    static  void print_diff(
      std::ostream& out,
      const StatsDiffContainerType& diffs);


    template<typename DiffType, typename StatsContainerType>
    void print_each_diff(
      std::ostream& out,
      const DiffType& diff,
      const StatsContainerType& real)
      const;

    using StatsContainerWrapper<std::list<ValueType> >::print_each_diff;
  };

  template<typename StatsContainerType>
  std::ostream& operator<<(
    std::ostream& out,
    const StatsContainerWrapper<StatsContainerType>& stats);

}
}

#include "StatsContainers.tpp"

#endif /*AUTOTESTS_COMMONS_STATS_STATSCONTAINERS_HPP*/
