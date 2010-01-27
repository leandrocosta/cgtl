/*
 * CGTL - A graph template library for C++
 * ---------------------------------------
 * Copyright (C) 2009 Leandro Costa
 *
 * This file is part of CGTL.
 *
 * CGTL is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as
 * published by the Free Software Foundation, either version 3 of
 * the License, or (at your option) any later version.
 *
 * CGTL is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with CGTL. If not, see <http://www.gnu.org/licenses/>.
 */

/*!
 * \file tests/cgt/base/alloc/storage_cxx.h
 * \brief Contains unit tests for class cgt::base::alloc::storage.
 * \author Leandro Costa
 * \date 2009
 *
 * $LastChangedDate: 2009-11-24 22:12:23 -0200 (Tue, 24 Nov 2009) $
 * $LastChangedBy: leandro.costa $
 * $Revision: 83 $
 */

#ifndef __CGTL__CXXTEST_CGT_BASE_ALLOC_STORAGE_CXX_H_
#define __CGTL__CXXTEST_CGT_BASE_ALLOC_STORAGE_CXX_H_

#include <stdlib.h>

#include <iostream>
#include <string>
#include <cxxtest/TestSuite.h>
#include "cgt/misc/cxxtest_defs.h"
#include "cgt/base/alloc/storage.h"


class storage_cxx : public CxxTest::TestSuite
{
  private:
    typedef cgt::base::alloc::_Storage<int> _Storage;
    typedef _Storage::_Chunk                _Chunk;
    typedef _Chunk::_Block                  _Block;

  private:
    static const size_t blocksize = (sizeof (int) >= sizeof (_Block *) ? sizeof (int):sizeof (_Block *));
    static const size_t numblocks = cgt::base::alloc::_CHUNK_SIZE/blocksize;

  public:
    void setUp () { }
    void tearDown () { } 

  public:
    void test_basic ()
    {
      _Storage storage;

      TS_ASSERT_EQUALS (storage._head, static_cast<_Chunk*>(NULL));
      TS_ASSERT_EQUALS (storage._free, static_cast<_Block*>(NULL));

      int* ptr = storage.allocate ();
      new (ptr) int (1);

      TS_ASSERT_EQUALS (*ptr, 1);
      TS_ASSERT_EQUALS (storage._head, reinterpret_cast<_Chunk*>(ptr));
      TS_ASSERT_EQUALS (storage._free, reinterpret_cast<_Block *>(reinterpret_cast<char *>(ptr)+blocksize));
      TS_ASSERT_EQUALS (reinterpret_cast<_Chunk*>(ptr)->_next, static_cast<_Chunk*> (NULL));

      storage.deallocate (ptr);

      TS_ASSERT_EQUALS (storage._head, reinterpret_cast<_Chunk*>(ptr));
      TS_ASSERT_EQUALS (storage._free, reinterpret_cast<_Block*>(ptr));
      TS_ASSERT_EQUALS (reinterpret_cast<_Chunk*>(ptr)->_next, static_cast<_Chunk*> (NULL));
    }

    void test_two_chunks ()
    {
      _Storage storage;

      int* ptr = storage.allocate ();
      new (ptr) int (1);

      for (unsigned int i = 1; i < numblocks; i++)
      {
        int* p = storage.allocate ();
        new (p) int (i);
      }

      TS_ASSERT_EQUALS (storage._head, reinterpret_cast<_Chunk*>(ptr));
      TS_ASSERT_EQUALS (storage._free, reinterpret_cast<_Block*>(NULL));
      TS_ASSERT_EQUALS (reinterpret_cast<_Chunk*>(ptr)->_next, static_cast<_Chunk*> (NULL));

      int* ptr2 = storage.allocate ();
      new (ptr2) int (2);

      TS_ASSERT_EQUALS (*ptr2, 2);
      TS_ASSERT_EQUALS (storage._head, reinterpret_cast<_Chunk*>(ptr2));
      TS_ASSERT_EQUALS (storage._free, reinterpret_cast<_Block *>(reinterpret_cast<char *>(ptr2) + blocksize));
      TS_ASSERT_EQUALS (reinterpret_cast<_Chunk*>(ptr)->_next, static_cast<_Chunk*> (NULL));
      TS_ASSERT_EQUALS (reinterpret_cast<_Chunk*>(ptr2)->_next, reinterpret_cast<_Chunk*> (ptr));
    }

    void test_dealloc_three_chunks ()
    {
      _Storage storage;

      int** array_ptrs = (int**) malloc ((3 * numblocks + 1) * sizeof (int*));

      //for (unsigned int i = 0; i < 3 * cgt::base::alloc::_CHUNK_SIZE; i++)
      for (unsigned int i = 0; i < 3 * numblocks; i++)
      {
        array_ptrs [i] = storage.allocate ();
        new (array_ptrs [i]) int (i);
      }

      TS_ASSERT_EQUALS (storage._free, reinterpret_cast<_Block*>(NULL));

      array_ptrs [3 * numblocks] = storage.allocate ();
      new (array_ptrs [3 * numblocks]) int (3 * numblocks);

      TS_ASSERT_DIFFERS (storage._free, reinterpret_cast<_Block*>(NULL));

      _Block* last_free = storage._free;
      storage.deallocate (array_ptrs [0]);
      TS_ASSERT_EQUALS (storage._free, reinterpret_cast<_Block*>(array_ptrs [0]));
      TS_ASSERT_EQUALS (reinterpret_cast<_Block*> (array_ptrs [0])->_next, last_free);

      for (unsigned int i = 1; i <= 3 * numblocks; i++)
      {
        storage.deallocate (array_ptrs [i]);
        TS_ASSERT_EQUALS (reinterpret_cast<_Block*> (array_ptrs [i])->_next, reinterpret_cast<_Block*> (array_ptrs [i-1]));
      }

      TS_ASSERT_EQUALS (storage._free, reinterpret_cast<_Block*>(array_ptrs [3 * numblocks]));
      TS_ASSERT_EQUALS (reinterpret_cast<_Block*> (array_ptrs [0])->_next, last_free);
    }

    void test_chunk ()
    {
      _Chunk chunk;

      TS_ASSERT_EQUALS (chunk._next, static_cast<_Chunk*>(NULL));
      TS_ASSERT_EQUALS (sizeof (chunk._block), cgt::base::alloc::_CHUNK_SIZE);

      //char* _ptr_last = &(chunk._block [(cgt::base::alloc::_CHUNK_SIZE-1) * blocksize]);
      char* _ptr_last = &(chunk._block [(numblocks - 1) * blocksize]);

      for (char* _ptr = chunk._block; _ptr < _ptr_last; _ptr += blocksize)
        TS_ASSERT_EQUALS (reinterpret_cast<_Block *>(_ptr)->_next, reinterpret_cast<_Block *>(reinterpret_cast<char *>(_ptr) + blocksize));

      TS_ASSERT_EQUALS (reinterpret_cast<_Block *>(_ptr_last)->_next, static_cast<_Block *> (NULL));
    }
};

#endif // __CGTL__CXXTEST_CGT_BASE_ALLOC_STORAGE_CXX_H_
