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
// Generics/CompositeActiveObject.cpp
#include <Generics/CompositeActiveObject.hpp>


namespace Generics
{
  //
  // CompositeSetActiveObject class
  //

  CompositeSetActiveObject::CompositeSetActiveObject(bool sync_termination)
    /*throw (eh::Exception)*/
    : CompositeActiveObjectBase<std::set<ActiveObject*>,
        Inserter<std::set<ActiveObject*>>,
        Inserter<std::set<ActiveObject*>>>(sync_termination)
  {
  }

  void
  CompositeSetActiveObject::remove_child_(ActiveObject* child) throw ()
  {
    Sync::PosixGuard guard(cond_);
    this->child_objects_.erase(child);
  }


  //
  // RemovableActiveObject class
  //

  RemovableActiveObject::RemovableActiveObject(
    ActiveObjectChildRemover* owner) throw ()
    : owner_(ReferenceCounting::add_ref(owner))
  {
  }

  void
  RemovableActiveObject::delete_this_() const throw ()
  {
    if (owner_)
    {
      RemovableActiveObject* ths =
        const_cast<RemovableActiveObject*>(this);
      ths->before_remove_child_();
      ths->owner_->remove_child_(ths);
    }
    AtomicImpl::delete_this_();
  }

  void
  RemovableActiveObject::before_remove_child_() throw ()
  {
  }
}
