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
#include <stdio.h>
#include <syslog.h>

#include <String/StringManip.hpp>
#include <JavaCommons/JavaCommons.hpp>
#include <SyslogJavaAdapter/JavaAdapter.hpp>


static char saved_identity[1024];

JNIEXPORT jstring JNICALL
Java_com_phorm_oix_logging_UnixcommonsSyslog_init(
  JNIEnv* env, jobject /*cls*/, jstring identity)
{
  {
    JavaCommons::StrPtr ident(env, identity);
    String::StringManip::strlcpy(saved_identity, ident.c_str(),
      sizeof(saved_identity));
  }
  openlog(saved_identity, LOG_PID | LOG_CONS, LOG_USER);
  return env->NewStringUTF("INIT_SUCCESS");
}

JNIEXPORT jstring JNICALL
Java_com_phorm_oix_logging_UnixcommonsSyslog_publish(
  JNIEnv* env, jobject /*obj*/, jint priority, jstring text)
{
  {
    JavaCommons::StrPtr message(env, text);
    syslog(priority, "%s", message.c_str());
  }
  return env->NewStringUTF("LOG_SUCCESS");
}
