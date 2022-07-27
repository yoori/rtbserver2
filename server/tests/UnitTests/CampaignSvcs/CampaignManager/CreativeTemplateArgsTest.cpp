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
// @file CampaignManager/CreativeTemplateArgsTest.cpp
#include <iostream>
#include <CampaignSvcs/CampaignManager/CreativeTemplateArgs.hpp>

using namespace AdServer::CampaignSvcs;

int
main() noexcept
{
  int ret_code = 0;

  try
  {
    CreativeInstantiateRule rule;
    OptionTokenValueMap token_values;
    TokenProcessorMap token_processor_map;

    {
      TokenSet restrictions;
      restrictions.insert("TEST2");
      restrictions.insert("TEST3");

      BaseTokenProcessor_var token_processor =
        new BaseTokenProcessor(
          "TEST",
          restrictions);
      token_processor_map[1] = token_processor;
    }

    {
      TokenSet restrictions;
      restrictions.insert("TEST3");

      BaseTokenProcessor_var token_processor =
        new BaseTokenProcessor(
          "TEST2",
          restrictions);
      token_processor_map[2] = token_processor;
    }

    {
      TokenSet restrictions;

      BaseTokenProcessor_var token_processor =
        new BaseTokenProcessor(
          "TEST3",
          restrictions);
      token_processor_map[3] = token_processor;
    }

    {
      token_values["TEST"] = OptionValue(1, "##TEST2## ##TEST3##");
      token_values["TEST2"] = OptionValue(2, "##TEST3##");
      token_values["TEST3"] = OptionValue(3, "EEEE");

      std::string result;

      token_processor_map[1]->instantiate(
        token_values,
        token_processor_map,
        rule,
        CreativeInstantiateArgs(),
        result);

      if (result != "EEEE EEEE")
      {
        std::cerr << "Test#1: incorrect instantiate result: '" << result
          << "'." << std::endl;
        ret_code = -1;
      }
      else
      {
        std::cout << "Test#1: OK" << std::endl;
      }
    }

    {
      token_values["TEST"] = OptionValue(1, "##TEST2## ##TEST3##");
      token_values["TEST2"] = OptionValue(2, "123");
      token_values["TEST3"] = OptionValue(3, "");

      std::string result;

      token_processor_map[1]->instantiate(
        token_values,
        token_processor_map,
        rule,
        CreativeInstantiateArgs(),
        result);

      if (result != "123 ")
      {
        std::cerr << "Test#2: incorrect instantiate result: '" << result
          << "'." << std::endl;
        ret_code = -1;
      }
      else
      {
        std::cout << "Test#2: OK" << std::endl;
      }
    }

    try
    {
      token_values["TEST"] = OptionValue(1, "##TEST2## ##TEST3##");
      token_values["TEST2"] = OptionValue(2, "##TEST3## ##TEST##");
      token_values["TEST3"] = OptionValue(3, "EEEE");

      std::string result;

      token_processor_map[1]->instantiate(
        token_values,
        token_processor_map,
        rule,
        CreativeInstantiateArgs(),
        result);

      std::cerr << "Test#3: must be thrown InvalidValue exception."
        << std::endl;
      ret_code = -1;
    }
    catch (const eh::Exception& ex)
    {
      std::cout << "Test#3: OK." << std::endl;
    }
  }
  catch (const eh::Exception& ex)
  {
    std::cerr << ex.what() << std::endl;
    ret_code = -1;
  }

  return ret_code;
}
