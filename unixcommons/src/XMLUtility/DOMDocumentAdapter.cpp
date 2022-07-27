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
 * @file   DOMDocumentAdapter.cpp
 * @author Karen Aroutiounov <karen@ipmce.ru>
 */

#include <sstream>

#include <xercesc/dom/DOM.hpp>
#include <xercesc/parsers/XercesDOMParser.hpp>
#include <xercesc/framework/MemBufInputSource.hpp>

#include <Stream/MemoryStream.hpp>

#include <XMLUtility/DOMDocumentAdapter.hpp>
#include <XMLUtility/StringManip.hpp>
#include "ParseErrorReporter.hpp"

namespace XMLUtility
{
  void
  DOMDocumentAdapter::parse_file(const char* file,
    AbstractDOMParser::ValSchemes validate)
    /*throw (InvalidArgument, Exception, eh::Exception)*/
  {
    if (file == 0 || *file == '\0')
    {
      throw Exception("XMLUtility::DOMDocumentAdapter::parse_file(): "
        "file is undefined");
    }

    try
    {
      parser_ = XercesDOMParser_ptr(new XercesDOMParser);

      std::ostringstream error_stream;
      ParseErrorReporter error_reporter(error_stream);

      parser_->setErrorHandler(&error_reporter);
      parser_->setDoNamespaces(true);
      parser_->setCreateEntityReferenceNodes(false);

      parser_->setDoSchema(true);
      parser_->setValidationSchemaFullChecking(true);
      parser_->setValidationScheme(validate);

      if (!schema_location_.empty())
      {
        parser_->setValidationScheme(AbstractDOMParser::Val_Always);
        parser_->setExternalSchemaLocation(schema_location_.c_str());
      }

      try
      {
        parser_->parse(file);
      }
      catch (const XMLException& e)
      {
        std::string errors = error_stream.str();

        std::string msg;
        StringManip::xmlch_to_mbc(e.getMessage(), msg);

        Stream::Error ostr;
        ostr << "XMLUtility:: DOMDocumentAdapter::parse_file(): "
          "XMLException thrown by XercesDOMParser::parse. Description:" <<
          std::endl << msg.c_str();

        if (!errors.empty())
        {
          ostr << std::endl << "Parser Diagnostics:" << std::endl <<
            errors.c_str();
        }

        throw Exception(ostr);
      }
      catch (const DOMException& e)
      {
        std::string errors = error_stream.str();

        Stream::Error ostr;
        ostr << "XMLUtility:: DOMDocumentAdapter::parse_file: "
          "XMLException thrown by XercesDOMParser::parse. Description:" <<
          std::endl << "Code: " << e.code;

        XMLCh buff[2048];
        if (DOMImplementation::loadDOMExceptionMsg(e.code, buff,
          sizeof(buff) / sizeof(buff[0]) - 1))
        {
          std::string msg;
          StringManip::xmlch_to_mbc(buff, msg);

          ostr << std::endl << "Message: " << msg.c_str();
        }

        if (!errors.empty())
        {
          ostr << std::endl << "Parser Diagnostics:" << std::endl <<
            errors.c_str();
        }

        ostr << std::endl << "File:" << std::endl << file;

        throw Exception(ostr);
      }
      catch (...)
      {
        std::string errors = error_stream.str();

        Stream::Error ostr;
        ostr << "XMLUtility:: DOMDocumentAdapter::parse_file: "
          "unknown exception thrown by XercesDOMParser::parse. "
          "File:\"" << std::endl << file << "\"";

        if (!errors.empty())
        {
          ostr << std::endl << "Parser Diagnostics:" << std::endl <<
            errors.c_str();
        }

        throw Exception(ostr);
      }

      if (error_reporter.errors())
      {
        std::string errors = error_stream.str();

        Stream::Error ostr;
        ostr << "XMLUtility:: DOMDocumentAdapter::parse_file: parsing failed, "
          "file \"" << file << "\"" << std::endl <<
          "Parser Diagnostics:" << std::endl << errors.c_str();

        throw Exception(ostr);
      }
    }
    catch (...)
    {
      try
      {
        clear();
      }
      catch (...)
      {
      }

      throw;
    }
  }

  void
  DOMDocumentAdapter::parse(const char* text,
    AbstractDOMParser::ValSchemes validate)
    /*throw (InvalidArgument, Exception, eh::Exception)*/
  {
    if (text == 0 || *text == '\0')
    {
      throw Exception("XMLUtility::DOMDocumentAdapter::parse(): "
        "text is undefined");
    }

    try
    {
      parser_ = XercesDOMParser_ptr(new XercesDOMParser);

      std::ostringstream error_stream;
      ParseErrorReporter error_reporter(error_stream);

      parser_->setErrorHandler(&error_reporter);
      parser_->setDoNamespaces(true);
      parser_->setCreateEntityReferenceNodes(false);

      parser_->setDoSchema(true);
      parser_->setValidationSchemaFullChecking(true);
      parser_->setValidationScheme(validate);

      if (!schema_location_.empty())
      {
        parser_->setValidationScheme(AbstractDOMParser::Val_Always);
        parser_->setExternalSchemaLocation(schema_location_.c_str());
      }

      MemBufInputSource mem_is(reinterpret_cast<const XMLByte*>(text),
        strlen(text), "XMLUtility::DOMDocumentAdapter::parse", false);

      try
      {
        parser_->parse(mem_is);
      }
      catch (const XMLException& e)
      {
        std::string errors = error_stream.str();

        std::string msg;
        StringManip::xmlch_to_mbc(e.getMessage(), msg);

        Stream::Error ostr;
        ostr << "XMLUtility:: DOMDocumentAdapter::parse: "
          "XMLException thrown by XercesDOMParser::parse. Description:" <<
          std::endl << msg.c_str();

        if (!errors.empty())
        {
          ostr << std::endl << "Parser Diagnostics:" << std::endl <<
            errors.c_str();
        }

        throw Exception(ostr);
      }
      catch (const DOMException& e)
      {
        std::string errors = error_stream.str();

        Stream::Error ostr;
        ostr << "XMLUtility:: DOMDocumentAdapter::parse: "
          "XMLException thrown by XercesDOMParser::parse. Description:" <<
          std::endl << "Code: " << e.code;

        XMLCh buff[2048];
        if (DOMImplementation::loadDOMExceptionMsg(e.code, buff,
          sizeof(buff) / sizeof(buff[0]) - 1))
        {
          std::string msg;
          StringManip::xmlch_to_mbc(buff, msg);

          ostr << std::endl << "Message: " << msg.c_str();
        }

        if (!errors.empty())
        {
          ostr << std::endl << "Parser Diagnostics:" << std::endl <<
            errors.c_str();
        }

        ostr << std::endl << "Content:" << std::endl << text;

        throw Exception(ostr);
      }
      catch (...)
      {
        std::string errors = error_stream.str();

        Stream::Error ostr;
        ostr << "XMLUtility:: DOMDocumentAdapter::parse: unknown exception "
          "thrown by XercesDOMParser::parse. Content:\"" << std::endl <<
          text << "\"";

        if (!errors.empty())
        {
          ostr << std::endl << "Parser Diagnostics:" << std::endl <<
            errors.c_str();
        }

        throw Exception(ostr);
      }

      if (error_reporter.errors())
      {
        std::string errors = error_stream.str();

        Stream::Error ostr;
        ostr << "XMLUtility:: DOMDocumentAdapter::parse: parsing failed, "
          "content \"" << text << "\"" << std::endl <<
          "Parser Diagnostics:" << std::endl << errors.c_str();

        throw Exception(ostr);
      }
    }
    catch (...)
    {
      try
      {
        clear();
      }
      catch (...)
      {
      }

      throw;
    }
  }

  DOMDocument*
  DOMDocumentAdapter::root()
    /*throw (NotParsed, Exception, eh::Exception)*/
  {
    if (parser_.get() == 0)
    {
      throw NotParsed("XMLUtility::DOMDocumentAdapter::root(): "
        "need to parse first");
    }

    DOMDocument* doc = parser_->getDocument();
    if (doc == 0)
    {
      throw NotParsed("XMLUtility::DOMDocumentAdapter::root(): "
        "document empty.");
    }

    return doc;
  }
}
