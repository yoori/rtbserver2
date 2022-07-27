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
#ifndef PASSBACKPROFILEUTILS_HPP
#define PASSBACKPROFILEUTILS_HPP

#include <Generics/Time.hpp>
#include <UtilCommons/Table.hpp>
#include <Commons/Algs.hpp>
#include <RequestInfoSvcs/RequestInfoCommons/PassbackProfile.hpp>

namespace AdServer
{
namespace RequestInfoSvcs
{
  void
  print_passback_profile(std::ostream& out,
    const PassbackInfoReader& reader)
    noexcept;
}
}

namespace AdServer
{
namespace RequestInfoSvcs
{
  namespace
  {
    const Table::Column PASSBACK_TABLE_COLUMNS[] =
    {
      Table::Column("request_id", Table::Column::TEXT),
      Table::Column("tag_id", Table::Column::NUMBER),
      Table::Column("size_id", Table::Column::NUMBER),
      Table::Column("ext_tag_id", Table::Column::TEXT),
      Table::Column("colo_id", Table::Column::NUMBER),
      Table::Column("country", Table::Column::TEXT),
      Table::Column("user_status", Table::Column::TEXT),
      Table::Column("referer", Table::Column::TEXT),
      Table::Column("time", Table::Column::TEXT),
      Table::Column("done", Table::Column::TEXT),
      Table::Column("verified", Table::Column::TEXT)
    };
  }

  inline
  void
  print_passback_profile(
    std::ostream& out,
    const PassbackInfoReader& passback_reader)
    noexcept
  {
    unsigned long columns =
      sizeof(PASSBACK_TABLE_COLUMNS) /
      sizeof(PASSBACK_TABLE_COLUMNS[0]);

    Table table(columns);

    for(unsigned long i = 0; i < columns; i++)
    {
      table.column(i, PASSBACK_TABLE_COLUMNS[i]);
    }

    Table::Row row(table.columns());

    row.add_field(passback_reader.request_id());
    row.add_field(passback_reader.tag_id());
    row.add_field(passback_reader.size_id());
    row.add_field(passback_reader.ext_tag_id());
    row.add_field(passback_reader.colo_id());
    row.add_field(passback_reader.country());
    row.add_field(passback_reader.user_status());
    row.add_field(passback_reader.referer());
    row.add_field(
      Generics::Time(passback_reader.time()).gm_ft());
    row.add_field(passback_reader.done());
    row.add_field(passback_reader.verified());

    table.add_row(row);
    table.dump(out);
  }
}
}

#endif /*PASSBACKPROFILEUTILS_HPP*/
