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
 * @file   ParseErrorReporter.hpp
 * @author Karen Aroutiounov <karen@ipmce.ru>
 */

#include <iostream>
#include <string>

#include <eh/Exception.hpp>

#include <xercesc/sax/ErrorHandler.hpp>
#include <xercesc/sax/SAXParseException.hpp>

#include "StringManip.hpp"
#include "ParseErrorReporter.hpp"

namespace XMLUtility
{
  void
  ParseErrorReporter::warning(const SAXParseException& toCatch)
    /*throw (eh::Exception)*/
  {
    if (show_warnings_)
    {
      std::string msg;
      StringManip::xmlch_to_mbc(toCatch.getMessage(), msg);

      std::string file;
      StringManip::xmlch_to_mbc(toCatch.getSystemId(), file);

      ostream_ << "XMLUtility::ParseErrorReporter: "
        "Warning at file \"" << file.c_str() <<
        "\", line " << toCatch.getLineNumber() << ", column " <<
        toCatch.getColumnNumber() << std::endl << "   Message: " <<
        msg.c_str() << std::endl;
    }
  }

  void
  ParseErrorReporter::error(const SAXParseException& toCatch)
    /*throw (eh::Exception)*/
  {
    errors_ = true;

    std::string msg;
    StringManip::xmlch_to_mbc(toCatch.getMessage(), msg);

    std::string file;
    StringManip::xmlch_to_mbc(toCatch.getSystemId(), file);

    ostream_ << "XMLUtility::ParseErrorReporter: "
      "Error at file \"" << file.c_str() <<
      "\", line " << toCatch.getLineNumber() << ", column " <<
      toCatch.getColumnNumber() << std::endl << "   Message: " <<
      msg.c_str() << std::endl;
  }

  void
  ParseErrorReporter::fatalError(const SAXParseException& toCatch)
    /*throw (eh::Exception)*/
  {
    errors_ = true;

    std::string msg;
    StringManip::xmlch_to_mbc(toCatch.getMessage(), msg);

    std::string file;
    StringManip::xmlch_to_mbc(toCatch.getSystemId(), file);

    ostream_ << "XMLUtility::ParseErrorReporter: "
      "Fatal Error at file \"" << file.c_str() <<
      "\", line " << toCatch.getLineNumber() << ", column " <<
      toCatch.getColumnNumber() << std::endl << "   Message: " <<
      msg.c_str() << std::endl;
  }

  void
  ParseErrorReporter::resetErrors() /*throw (eh::Exception)*/
  {
    errors_ = false;
  }
}
