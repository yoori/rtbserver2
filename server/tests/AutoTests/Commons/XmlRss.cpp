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

#include <Generics/Uuid.hpp>
#include "XmlRss.hpp"
#include <tests/AutoTests/Commons/Utils.hpp>

namespace
{
  const char XSEARCH_DATE_FORMAT[] = "%F.%T";
  unsigned long IMAGEWIDTH  = 129;
  unsigned long IMAGEHEIGHT = 95;
  const char IMAGEALT[] = "image for funtest";
  const char DEFAULT_COUNTRY[] = "USA";
  const char DEFAULT_SERVER[] = "1.4.56.0";
}

namespace AutoTest
{
  namespace XMLRSS
  {

    XmlRss::XmlRss(const Generics::Time& reqDate, unsigned long ttl) :
      xmlDoc(result_type::total_type(0)),
      news_count(0)
    {
      XSearch::ExTimeType reqDateXml(time2str(reqDate));
      xmlDoc.reqDate(reqDateXml);
      xmlDoc.ttl(ttl);
      xmlDoc.server(DEFAULT_SERVER);
    }

    void XmlRss::add_news(const char* language,
                          const char* source_link,
                          const Generics::Time& pubDate,
                          unsigned long capacity)
    {
      xmlDoc.total(++news_count);
      // Images
      XSearch::ImageSetType images;
      XSearch::ImageType image(genUrl() + "/image.gif");
      image.width(IMAGEWIDTH);
      image.height(IMAGEHEIGHT);
      image.alt(IMAGEALT);
      images.image().push_back(image);

      //Event
      XSearch::EventType event;
      event.id(genGuid());
      event.capacity(capacity);

      // Source
      XSearch::SourceType source;
      source.title(genGuid());
      if (source_link)
        source.link(source_link);
      else
        source.link(genUrl());
      source.country(DEFAULT_COUNTRY);

      // Item
      XSearch::ItemType item;
      item.id().push_back(genGuid());
      item.title().push_back(genGuid());
      item.description().push_back(genGuid());
      XSearch::ExTimeType pubDateXml(time2str(pubDate));
      item.pubDate().push_back(pubDateXml);
      XSearch::LinkType link(genUrl());
      item.link().push_back(link);
      XSearch::GuidType guid(genGuid());
      item.guid().push_back(guid);
      item.language().push_back(language);
      item.event().push_back(event);
      item.images().push_back(images);
      item.source().push_back(source);

      if (xmlDoc.items().present())
      {
        xmlDoc.items()->item().push_back(item);
      }
      else
      {
        XSearch::ItemsType items;
        items.item().push_back(item);
        xmlDoc.items(items);
      }

    }

    std::string XmlRss::xml() const
    {
      // Serialization
      std::ostringstream ostr;
      print(ostr);
      return ostr.str();
    }

    XSearch::ItemType& XmlRss::get_news(unsigned long news_index) /*throw(NotFound)*/
    {
      const char FUN[] = "XmlRss::get_news()";
      if (! xmlDoc.items().present())
      {
        Stream::Error ostr;
        ostr <<  FUN << ": tag items not found (no news was added)";
        throw NotFound(ostr);
      }
      if (xmlDoc.items()->item().size() <= news_index)
      {
        Stream::Error ostr;
        ostr <<  FUN << ": news container size: '" <<  xmlDoc.items()->item().size()
             << "' <= requested news index: '" << news_index << "'";
        throw NotFound(ostr);
      }
      return xmlDoc.items()->item()[news_index];
    }

    // Helper functions
    std::string XmlRss::genGuid()
    {
      return Generics::Uuid::create_random_based().to_string();
    }

    std::string XmlRss::genUrl()
    {
      return "http://www." + tolower(genGuid())   + ".com/";
    }

    std::string XmlRss::time2str(const Generics::Time& time)
    {
      return time.get_gm_time().format(XSEARCH_DATE_FORMAT);
    }

    std::ostream&  XmlRss::print (std::ostream& out) const
    {
      xml_schema::namespace_infomap map;
      map[""].name = "http://www.newsgate.com/XSearch1.3";
      XSearch::result_(out, xmlDoc, map);
      return out;
    }

  }
}

