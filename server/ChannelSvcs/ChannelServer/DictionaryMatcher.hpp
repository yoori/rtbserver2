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
#ifndef CHANNEL_SVCS_DICTIONARY_MATCHER_HPP_
#define CHANNEL_SVCS_DICTIONARY_MATCHER_HPP_

#include <CORBACommons/CorbaAdapters.hpp>
#include <CORBACommons/ObjectPool.hpp>
//#include <ChannelSvcs/ChannelCommons/TriggerParser.hpp>
#include <ChannelSvcs/DictionaryProvider/DictionaryProvider.hpp>

namespace AdServer
{
namespace ChannelSvcs
{
  class DictionaryMatcher
  {
  public:
    DECLARE_EXCEPTION(Exception, eh::DescriptiveException);

    DictionaryMatcher(
      const CORBACommons::CorbaClientAdapter& adapter,
      CORBACommons::CorbaObjectRefList& dictionary_server_refs,
      Logging::Logger* logger)
      /*throw(Exception)*/;

    virtual ~DictionaryMatcher() noexcept {};

    /*
    virtual size_t add_trigger(MergeAtom& merge_atom);
    */

    typedef std::map<String::SubString, Lexeme_var> LexemeCache;

    void get_lexemes(
      const char* lang,
      LexemeCache& lexemes)
      /*throw(Exception)*/;

    virtual bool ready() const noexcept;

    static bool
    is_lexemized(const char* trigger) noexcept;


    typedef CORBACommons::ObjectPoolRefConfiguration
      DictionaryProviderPoolConfig;

    typedef
      CORBACommons::ObjectPool<
        AdServer::ChannelSvcs::DictionaryProvider,
        DictionaryProviderPoolConfig>
      DictionaryProviderPool;
    typedef std::unique_ptr<DictionaryProviderPool> DictionaryProviderPoolPtr;

  private:
    static const char* ASPECT;

    AdServer::ChannelSvcs::DictionaryProvider::LexemeSeq*
    query_dictionary_words_(
      const char* lang,
      const CORBACommons::StringSeq& seq_words) const
      /*throw(Exception)*/;

    void trace_result_(const char* lang, const LexemeCache& cache)
      noexcept;

  private:
    const CORBACommons::CorbaClientAdapter& c_adapter_;
    DictionaryProviderPoolPtr dictionary_pool_;
    Logging::Logger* logger_;
  };

}
}

namespace AdServer
{
namespace ChannelSvcs
{
    inline
    bool DictionaryMatcher::is_lexemized(const char* trigger) noexcept
    {
      char trigger_type = Serialization::trigger_type(trigger);
      return (trigger_type != 'U' && trigger_type != 'D');
    }
}
}
#endif//CHANNEL_SVCS_DICTIONARY_MATCHER_HPP_
