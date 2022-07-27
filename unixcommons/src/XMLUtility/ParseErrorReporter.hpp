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
 *
 * File contains group of utility classes related to XML parsing
 * errors reporting.
 */

#ifndef XML_UTILITY_PARSE_ERROR_REPORTER_HPP
#define XML_UTILITY_PARSE_ERROR_REPORTER_HPP

#include <iostream>

#include <eh/Exception.hpp>

#include <xercesc/sax/ErrorHandler.hpp>
#include <xercesc/sax/SAXParseException.hpp>

XERCES_CPP_NAMESPACE_USE

namespace XMLUtility
{
  /**
   * Writes error messages and warnings produced by a Xerces SAX parser into
   * an output stream.
   */
  class ParseErrorReporter : public ErrorHandler
  {
  public:
    /**
     * Parametric constructor.
     *
     * @param ostr The output stream to use for writing messages.
     * @param show_warnings Determines whether <code>ParseErrorReporter</code>
     * reports warning messages. By
     * default, warnings appear in the output stream.
     */
    ParseErrorReporter(std::ostream& ostr, bool show_warnings = true)
      /*throw (eh::Exception)*/;

    /**
     * Determines whether <code>ParseErrorReporter</code> reports error
     * messages.
     *
     * @return <code>true</code> if error messages are reported;
     * <code>false</code> otherwise.
     */
    bool
    errors() throw ();

  protected:
    virtual
    void
    warning(const SAXParseException& toCatch) /*throw (eh::Exception)*/;

    virtual
    void
    error(const SAXParseException& toCatch) /*throw (eh::Exception)*/;

    virtual
    void
    fatalError(const SAXParseException& toCatch) /*throw (eh::Exception)*/;

    virtual
    void
    resetErrors() /*throw (eh::Exception)*/;

  protected:
    bool errors_;
    bool show_warnings_;
    std::ostream& ostream_;
  };
}

///////////////////////////////////////////////////////////////////////////////
// Inlines
///////////////////////////////////////////////////////////////////////////////

namespace XMLUtility
{
  inline
  ParseErrorReporter::ParseErrorReporter(std::ostream& ostr,
    bool show_warnings) /*throw (eh::Exception)*/
    : errors_(false), show_warnings_(show_warnings), ostream_(ostr)
  {
  }

  inline
  bool
  ParseErrorReporter::errors() throw ()
  {
    return errors_;
  }
}

#endif
