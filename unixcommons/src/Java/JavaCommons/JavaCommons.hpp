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
#ifndef JAVA_JAVACOMMONS_JAVACOMMONS_HPP
#define JAVA_JAVACOMMONS_JAVACOMMONS_HPP

#include <jni.h>

#include <Generics/Uncopyable.hpp>
#include <Generics/Function.hpp>

#include <Stream/MemoryStream.hpp>


namespace JavaCommons
{
  class StrPtr : private Generics::Uncopyable
  {
  public:
    DECLARE_EXCEPTION(Exception, eh::DescriptiveException);

    StrPtr(JNIEnv* env, jstring jstr) /*throw (Exception)*/;
    ~StrPtr() throw ();

    const char*
    c_str() const throw ();

  private:
    JNIEnv* env_;
    jstring jstr_;
    const char* str_;
  };
}

namespace JavaCommons
{
  inline
  StrPtr::StrPtr(JNIEnv* env, jstring jstr) /*throw (Exception)*/
    : env_(env), jstr_(jstr), str_(env->GetStringUTFChars(jstr, 0))
  {
    if (!str_)
    {
      Stream::Error ostr;
      ostr << FNS << "failed to make C-string from jstring";
      throw Exception(ostr);
    }
  }

  inline
  StrPtr::~StrPtr() throw ()
  {
    env_->ReleaseStringUTFChars(jstr_, str_);
  }

  inline
  const char*
  StrPtr::c_str() const throw ()
  {
    return str_;
  }
}

#endif
