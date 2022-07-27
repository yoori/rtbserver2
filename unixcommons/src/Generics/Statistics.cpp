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
/**
 * @file   Statistics.cpp
 * @author Karen Aroutiounov
 */

#include <Generics/Statistics.hpp>


//#define TRACE

namespace Generics
{
  namespace Statistics
  {
    //
    // Collection class
    //
    Collection::Collection(DumpRunner* dump_runner)
      /*throw (InvalidArgument, Exception, eh::Exception)*/
      : stat_dumper_(ReferenceCounting::add_ref(dump_runner))
    {
    }

    Collection::Collection(ActiveObjectCallback* callback)
      /*throw (InvalidArgument, Exception, eh::Exception)*/
      : stat_dumper_(new TaskDumpRunner(callback))
    {
    }

    Collection::~Collection() throw ()
    {
      items_.clear();
    }

    void
    Collection::activate_object()
      /*throw (ActiveObject::AlreadyActive, Exception, eh::Exception)*/
    {
      try
      {
        stat_dumper_->activate_object();
      }
      catch (const TaskRunner::Exception& e)
      {
        Stream::Error ostr;
        ostr << FNS << "TaskRunner::Exception:" << e.what();
        throw Exception(ostr);
      }
    }

    void
    Collection::deactivate_object()
      /*throw (Exception, eh::Exception)*/
    {
      try
      {
        stat_dumper_->deactivate_object();
      }
      catch (const TaskRunner::Exception& e)
      {
        Stream::Error ostr;
        ostr << FNS << "TaskRunner::Exception:" << e.what();
        throw Exception(ostr);
      }
    }

    void
    Collection::wait_object()
      /*throw (Exception, eh::Exception)*/
    {
      try
      {
        stat_dumper_->wait_object();
      }
      catch (const TaskRunner::Exception& e)
      {
        Stream::Error ostr;
        ostr << FNS << "TaskRunner::Exception:" << e.what();
        throw Exception(ostr);
      }
    }

    void
    Collection::add(const char* id, StatSink* stat, DumpPolicy* policy)
      /*throw (InvalidArgument, Exception, eh::Exception)*/
    {
      if (id == 0)
      {
        Stream::Error ostr;
        ostr << FNS << "id == 0";
        throw InvalidArgument(ostr);
      }

      WriteGuard_ guard(lock_);

      try
      {
        items_[id] = new Item(id, stat, policy, stat_dumper_);
      }
      catch (const Item::Exception& e)
      {
        Stream::Error ostr;
        ostr << FNS <<
          "Generics::Statistics::Collection::Item::Exception: " << e.what();
        throw InvalidArgument(ostr);
      }
    }

    void
    Collection::dump(std::ostream& ostr)
      /*throw (Exception, eh::Exception)*/
    {
      ReadGuard_ guard(lock_);

      for (ItemMap::iterator item = items_.begin(); item != items_.end();
        ++item)
      {
        item->second->dump(ostr);
        ostr << std::endl;
      }
    }

    //
    // Collection::Item class
    //

    void
    Collection::Item::dump(std::ostream& ostr)
      /*throw (eh::Exception)*/
    {
      Sync::PosixGuard guard(mutex_);

      ostr << "* " << id_.c_str() << " statistics:" << std::endl;
      ostr << current_time().c_str() << std::endl;

      stat_->dump(ostr);
    }

    std::string
    Collection::Item::current_time()
      /*throw (eh::Exception)*/
    {
      return Time::get_time_of_day().get_local_time().format(
        "%a %d %b %Y %H:%M:%S");
    }
  }
}
