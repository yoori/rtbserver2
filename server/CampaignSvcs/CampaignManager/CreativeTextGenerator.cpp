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
#include <iostream>
#include "CreativeTextGenerator.hpp"

namespace AdServer
{
namespace CampaignSvcs
{
  void
  CreativeTextGenerator::init_creative_tokens(
    const CreativeInstantiateRule& rule,
    const CreativeInstantiateArgs& creative_instantiate_args,
    const TokenProcessorMap& token_processors,
    const TokenValueMap& request_args,
    const OptionTokenValueMap& creative_args,
    TokenValueMap& result_creative_args)
    /*throw(eh::Exception)*/
  {
    OptionTokenValueMap union_args;
    for(TokenValueMap::const_iterator req_arg_it =
          request_args.begin();
        req_arg_it != request_args.end(); ++req_arg_it)
    {
      union_args.insert(std::make_pair(
        req_arg_it->first,
        OptionValue(0, req_arg_it->second.c_str())));
    }

    for(OptionTokenValueMap::const_iterator cr_arg_it =
          creative_args.begin();
        cr_arg_it != creative_args.end(); ++cr_arg_it)
    {
      union_args[cr_arg_it->first] = cr_arg_it->second;
    }

    for(OptionTokenValueMap::const_iterator it = creative_args.begin();
        it != creative_args.end();
        ++it)
    {
      BaseTokenProcessor_var token_processor;
      TokenProcessorMap::const_iterator proc_it = token_processors.find(
        it->second.option_id);
      if(proc_it == token_processors.end())
      {
        token_processor =
          BaseTokenProcessor::default_token_processor(it->first.c_str());
      }
      else
      {
        token_processor = proc_it->second;
      }

      std::string res;
      token_processor->instantiate(
        union_args,
        token_processors,
        rule,
        creative_instantiate_args,
        res);
      result_creative_args[it->first].swap(res);
    }
  }
}
}
