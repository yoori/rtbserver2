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
#ifndef _BENCHMARKSTORAGE_HPP
#define _BENCHMARKSTORAGE_HPP

#include "AdServerClient.hpp"
#include "Configuration.hpp"

// Number of different request types
const long REQUEST_TYPE_SIZE = 8;

/**
 * @class RequestStorage
 * @brief Store generated request URLs
 */
class RequestStorage : public virtual ReferenceCounting::Interface,
                       public virtual ReferenceCounting::AtomicImpl
{

  typedef std::list<std::string> RequestList;
  typedef RequestList::const_iterator RequestIterator;

public:

  /**
   * @brief Constructor.
   */
  RequestStorage();

  /**
   * @brief Destructor
   */
  ~RequestStorage()  noexcept;

  /**
   * @brief Push requests to container
   *
   * @param request
   */
  void push(const char* request);

  /**
   * @brief Get next request from container
   *
   * @param [out] request
   * @return if we reach "last" request  - true.
   */  
  bool get(std::string& request);

  /**
   * @brief Get container size
   *
   * @return container size
   */  
  size_t size();

  /**
   * @brief Clear, remove all requests
   */  
  void clear();


private:
  RequestList requests_;             // request container
  RequestIterator current_request_;  // current request
};

typedef ReferenceCounting::SmartPtr<RequestStorage> RequestStorage_var;

/**
 * @class ClientStorage
 * @brief Store clients & it generated requests
 */
class ClientStorage : public virtual ReferenceCounting::Interface,
                      public virtual ReferenceCounting::AtomicImpl
{

  typedef std::map<unsigned long, RequestStorage_var> RequestStoragesList;
  typedef RequestStoragesList::const_iterator ClientIterator;
  
public:

  /**
   * @brief Constructor.
   *
   * @param AdServer client
   */
  ClientStorage();

  /**
   * @brief Destructor
   */
  ~ClientStorage()  noexcept;

  /**
   * @brief Push generated requests
   *
   * @param client ID
   * @param request URL
   */
  void push_request(unsigned long client_id,
                    const char* request);

  /**
   * @brief Get total request containers size
   *
   * @return size
   */  
  size_t requests();

  /**
   * @brief Send generated request from client
   *
   * @param [out]r request
   */  
  unsigned long get_request(std::string& request);

  /**
   * @brief Clear storage, remove all requests
   */  
  void clear();


private:
  RequestStoragesList requests_;  // request storages list
  ClientIterator current_client_; // current client
  size_t size_;                   // total request containers size
};

typedef ReferenceCounting::SmartPtr<ClientStorage> ClientStorage_var;

/**
 * @class BenchmarkStorage
 * @brief Benchmark storage
 */
class BenchmarkStorage
{

  typedef std::map<unsigned long, AdServerClient_var> ClientMap;
  typedef std::vector<ClientStorage_var> ClientStorageList;
  typedef ClientMap::const_iterator ClientIterator;
  typedef Sync::PosixRWLock Mutex_;
  typedef Sync::PosixRGuard ReadGuard_;
  typedef Sync::PosixWGuard WriteGuard_;
  
public:

  /**
   * @brief Constructor.
   */
  BenchmarkStorage(Statistics* stats);

  /**
   * @brief Destructor.
   */
  ~BenchmarkStorage()  noexcept;


  /**
   * @brief Push request pair (client/request)
   *
   * @param frontend_type
   * @param client
   * @param request
   */
  void push_request_pair(FrontendType frontend_type,
                         AdServerClientBase* client,
                         const char* request) noexcept;

  /**
   * @brief Push client
   *
   * @param client
   */
  void push_client(AdServerClientBase* client);

  /**
   * @brief Get next request pair from storage
   *
   * @param frontend type
   * @param [out] request
   * @return client
   */  
  AdServerClientBase* get_request_pair(FrontendType frontend_type,
                                       std::string& request);

  /**
   * @brief Get next client from storage
   *
   * @return client
   */  
  AdServerClientBase* get_client();


  /**
   * @brief Get total generated requests for frontend type
   *
   * @param frontend type
   * @return count of requests
   */  
  size_t request_size(FrontendType frontend_type);


  /**
   * @brief Get total clients size
   *
   * @return size
   */  
  size_t client_size();

  /**
   * @brief Clear storage, remove all clients & requests
   */  
  void clear();

  /**
   * @brief Get statistics
   *
   * @return statistics
   */  
  Statistics* stats();

private:
  ClientStorageList storages_;        // clients storages list
  ClientMap clients_;                 // clients list
  ClientIterator current_client_;     // current client
  Statistics* stats_;                 // statistics
  mutable Mutex_ lock_;
};


#endif  // _BENCHMARKSTORAGE_HPP
