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
#ifndef UIDGENERATORADAPTER_KEYWORDSPROCESSOR_HPP_
#define UIDGENERATORADAPTER_KEYWORDSPROCESSOR_HPP_

#include <string>

#include <eh/Exception.hpp>
#include <ReferenceCounting/AtomicImpl.hpp>
#include <ReferenceCounting/SmartPtr.hpp>
#include <Generics/GnuHashTable.hpp>

#include <Commons/StringHolder.hpp>
#include <Frontends/UIDGeneratorAdapter/UIDGeneratorProtocol.pb.h>

namespace AdServer
{
namespace Frontends
{
  // KeywordsProcessor
  class KeywordsProcessor: public ReferenceCounting::AtomicImpl
  {
  public:
    typedef std::vector<AdServer::Commons::StringHolder_var> KeywordArray;

  public:
    KeywordsProcessor() noexcept;

    void
    process(
      KeywordArray& keywords,
      const ru::madnet::enrichment::protocol::DmpRequest& dmp_request)
      noexcept;

  protected:
    virtual ~KeywordsProcessor() noexcept {}

  private:
    struct ParamProcessor: public ReferenceCounting::AtomicImpl
    {
      virtual void
      process(
        KeywordArray& keywords,
        const String::SubString& value)
        noexcept = 0;
    };

    class NumberPreNormProcessor;
    class FloatFloorParamProcessor;
    class Log2ParamProcessor;
    class Log10ParamProcessor;
    class NumericStepParamProcessor;
    class AddPrefixParamProcessor;
    class CompositeParamProcessor;

    template<typename SepCategory = String::AsciiStringManip::Char1Category<','> >
    class SepParamProcessor;

    template<typename SepCategory = String::AsciiStringManip::Char1Category<','> >
    class SepSumParamProcessor;

    class NormParamProcessor;

    typedef ReferenceCounting::SmartPtr<ParamProcessor>
      ParamProcessor_var;

    typedef std::vector<ParamProcessor_var> ParamProcessorArray;

    typedef Generics::GnuHashTable<
      Generics::SubStringHashAdapter, ParamProcessorArray>
      ParamProcessorMap;

  private:
    void
    add_processor_(
      const String::SubString& name,
      const ParamProcessor_var& processor)
      noexcept;

    void
    process_(
      KeywordArray& keywords,
      const String::SubString& name_and_value)
      const noexcept;

  private:
    ParamProcessorMap param_processors_;
  };

  typedef ReferenceCounting::SmartPtr<KeywordsProcessor> KeywordsProcessor_var;
}
}

#endif /*UIDGENERATORADAPTER_KEYWORDSPROCESSOR_HPP_*/
