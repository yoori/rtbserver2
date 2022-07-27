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
// @file PlainStorage/File.hpp

#ifndef SYS_FILE_HPP
#define SYS_FILE_HPP

// We support large files, use mmap64 instead mmap, etc
#ifndef PS_NOT_USE_LARGEFILES

#define _LARGEFILE64_SOURCE 1
#define _FILE_OFFSET_BITS 64

#endif

#include <sys/types.h>

#include <eh/Exception.hpp>

/**
 * Wrappers over low-level system functions
 */
namespace Sys
{
  /// Modes for file opening
  enum FileOpening
  {
    FO_READ = 0,
    FO_RW,
    FO_RW_CREATE
  };

  /// Describes the desired memory protection
  enum MemoryMapping
  {
    MM_READ = 0,
    MM_RW
  };

  typedef off64_t OffsetType;

  /**
   * Handle work with file, that contain user data. Allow open, close, resize,
   * map part of file to memory and unmap chunk of file from memory
   */
  class File
  {
  public:
    DECLARE_EXCEPTION(PosixException, eh::DescriptiveException);

  public:
    File() noexcept;

    /**
     * This constructor open file_name with specified flag
     */
    File(const char* file_name, FileOpening flag) /*throw(PosixException)*/;

    /**
     * Destructor close file
     */
    ~File() noexcept;

    void
    open(const char* file_name, FileOpening flag) /*throw(PosixException)*/;

    void
    close() /*throw(PosixException)*/;

    /**
     * @return information about a file - its size.
     */
    OffsetType
    size() /*throw(PosixException)*/;

    /**
     * Change file size
     * @param new_size New size of file to be set
     */
    void
    resize(OffsetType new_size) /*throw(PosixException)*/;

    /**
     * allocate file space
     * @param pos The offset from file beginning to allocate
     * @param size The size of memory block to allocate
     */
    void alloc(OffsetType pos, OffsetType size)
      /*throw(PosixException)*/;

    /**
     * Load the part of opened file into shared memory
     * @param pos The offset from file beginning to be mapped in memory
     * @param size The size of memory block that will up from file to memory
     * @param flag The mode of memory protection
     * @return The pointer to mapped memory
     */
    void*
    mmap(OffsetType pos, OffsetType size, MemoryMapping flag)
      /*throw(PosixException)*/;

    /**
     * Synchronize mapped region
     * @param mem_ptr The pointer to memory region for synchronize
     * @param size The size of memory block that will be synchronized
     */
    void
    msync(void* mem_ptr, OffsetType size)
      /*throw(PosixException)*/;

    /**
     * Deletes the mappings for the specified address range
     * @param mem_ptr The pointer to begin of memory region to be free
     * @param size The size of memory region
     */
    void
    munmap(void* mem_ptr, OffsetType size)
      /*throw(PosixException)*/;

    void
    pread(void* buf, unsigned long read_size, unsigned long pos)
      /*throw(PosixException)*/;

    void
    pwrite(const void* buf, unsigned long read_size, unsigned long pos)
      /*throw(PosixException)*/;

    /**
     * @return The constant value of ::getpagesize() call
     */
    static int
    get_page_size() noexcept;

  protected:
    /// Descriptor for file opening
    int file_handle_;
  };
}

#endif // SYS_FILE_HPP
