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
#ifndef COMMONS_IPCRYPTER_HPP
#define COMMONS_IPCRYPTER_HPP

#include <arpa/inet.h>
#include <netinet/in.h>

#include <openssl/aes.h>
#include <openssl/crypto.h>

#include <eh/Exception.hpp>
#include <ReferenceCounting/AtomicImpl.hpp>
#include <ReferenceCounting/SmartPtr.hpp>

namespace AdServer
{
namespace Commons
{
  class AesEncryptKey
  {
  public:
    static const unsigned long KEY_SIZE = 16;

    AesEncryptKey() noexcept;

    AesEncryptKey(const unsigned char *key, unsigned long size)
      noexcept;

    ~AesEncryptKey() noexcept;

    // encrypt AES_BLOCK_SIZE=16 bytes (will be saved 16 bytes to out)
    void
    encrypt(void* out, const void* in) const
      noexcept;

  private:
    AES_KEY key_;
  };

  class AesDecryptKey
  {
  public:
    AesDecryptKey() noexcept;

    AesDecryptKey(const unsigned char *key, unsigned long size)
      noexcept;

    ~AesDecryptKey() noexcept;

    // decrypt AES_BLOCK_SIZE=16 bytes (will be saved 16 bytes to out)
    void
    decrypt(void* out, const void* in) const
      noexcept;

  private:
    AES_KEY key_;
  };

  class IPCrypter: public ReferenceCounting::AtomicImpl
  {
  public:
    DECLARE_EXCEPTION(Exception, eh::DescriptiveException);
    DECLARE_EXCEPTION(InvalidKey, Exception);
    DECLARE_EXCEPTION(InvalidParams, Exception);

    IPCrypter(const String::SubString& key)
      /*throw(InvalidKey)*/;

    void
    encrypt(
      std::string& encrypted_ip,
      const char* ip)
      /*throw(InvalidParams)*/;

    void
    decrypt(
      std::string& ip,
      const String::SubString& encrypted_ip)
      /*throw(InvalidParams)*/;

  private:
    template<typename KeyType>
    static KeyType
    make_key_(const String::SubString& key)
      /*throw(InvalidKey)*/;

  private:
    AesEncryptKey encrypt_key_;
    AesDecryptKey decrypt_key_;
  };

  typedef ReferenceCounting::SmartPtr<IPCrypter>
    IPCrypter_var;
}
}

#endif /*COMMONS_IPCRYPTER_HPP*/
