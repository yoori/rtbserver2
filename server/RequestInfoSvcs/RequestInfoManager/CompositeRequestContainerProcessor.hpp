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
#ifndef _COMPOSITE_REQUEST_CONTAINER_PROCESSOR_HPP_
#define _COMPOSITE_REQUEST_CONTAINER_PROCESSOR_HPP_

#include <eh/Exception.hpp>
#include <ReferenceCounting/AtomicImpl.hpp>
#include "RequestActionProcessor.hpp"

namespace AdServer
{
  namespace RequestInfoSvcs
  {
    /**
     * CompositeRequestContainerProcessor
     * delegate request processing to child RequestContainerProcessor's
     */
    class CompositeRequestContainerProcessor:
      public virtual RequestContainerProcessor,
      public virtual ReferenceCounting::AtomicImpl
    {
    public:
      DECLARE_EXCEPTION(Exception, RequestContainerProcessor::Exception);

      void
      add_child_processor(RequestContainerProcessor* child_processor) /*throw(Exception)*/;

      virtual void
      process_request(const RequestInfo& request_info)
        /*throw(RequestContainerProcessor::Exception)*/;

      virtual void
      process_impression(const ImpressionInfo& impression_info)
        /*throw(RequestContainerProcessor::Exception)*/;

      virtual void
      process_action(
        ActionType action_type,
        const Generics::Time& time,
        const AdServer::Commons::RequestId& request_id)
        /*throw(RequestContainerProcessor::Exception)*/;

      virtual void
      process_custom_action(
        const AdServer::Commons::RequestId& request_id,
        const AdvCustomActionInfo& adv_custom_action_info)
        /*throw(RequestContainerProcessor::Exception)*/;

      virtual void
      process_impression_post_action(
        const AdServer::Commons::RequestId& request_id,
        const RequestPostActionInfo& request_post_action_info)
        /*throw(RequestContainerProcessor::Exception)*/;

    protected:
      virtual ~CompositeRequestContainerProcessor() noexcept {}

    private:
      typedef std::list<RequestContainerProcessor_var> RequestContainerProcessorList;
      RequestContainerProcessorList child_processors_;
    };

    typedef ReferenceCounting::SmartPtr<CompositeRequestContainerProcessor>
      CompositeRequestContainerProcessor_var;
  }
}

namespace AdServer
{
namespace RequestInfoSvcs
{
  /* CompositeRequestContainerProcessor */
  inline
  void
  CompositeRequestContainerProcessor::add_child_processor(
    RequestContainerProcessor* child_processor) /*throw(Exception)*/
  {
    RequestContainerProcessor_var add_processor(
      ReferenceCounting::add_ref(child_processor));
    child_processors_.push_back(add_processor);
  }

  inline
  void CompositeRequestContainerProcessor::process_request(
    const RequestInfo& request_info)
    /*throw(RequestContainerProcessor::Exception)*/
  {
    for(RequestContainerProcessorList::iterator it = child_processors_.begin();
        it != child_processors_.end();
        ++it)
    {
      (*it)->process_request(request_info);
    }
  }

  inline
  void CompositeRequestContainerProcessor::process_impression(
    const ImpressionInfo& impression_info)
    /*throw(RequestContainerProcessor::Exception)*/
  {
    for(RequestContainerProcessorList::iterator it = child_processors_.begin();
        it != child_processors_.end();
        ++it)
    {
      (*it)->process_impression(impression_info);
    }
  }

  inline
  void CompositeRequestContainerProcessor::process_action(
    ActionType action_type,
    const Generics::Time& time,
    const AdServer::Commons::RequestId& request_id)
    /*throw(RequestContainerProcessor::Exception)*/
  {
    for(RequestContainerProcessorList::iterator it = child_processors_.begin();
        it != child_processors_.end();
        ++it)
    {
      (*it)->process_action(action_type, time, request_id);
    }
  }

  inline
  void CompositeRequestContainerProcessor::process_custom_action(
    const AdServer::Commons::RequestId& request_id,
    const AdvCustomActionInfo& adv_custom_action_info)
    /*throw(RequestContainerProcessor::Exception)*/
  {
    for(RequestContainerProcessorList::iterator it = child_processors_.begin();
        it != child_processors_.end();
        ++it)
    {
      (*it)->process_custom_action(request_id, adv_custom_action_info);
    }
  }

  inline void
  CompositeRequestContainerProcessor::process_impression_post_action(
    const AdServer::Commons::RequestId& request_id,
    const RequestPostActionInfo& request_post_action_info)
    /*throw(RequestContainerProcessor::Exception)*/
  {
    for(RequestContainerProcessorList::iterator it = child_processors_.begin();
        it != child_processors_.end();
        ++it)
    {
      (*it)->process_impression_post_action(request_id, request_post_action_info);
    }
  }
}
}

#endif
