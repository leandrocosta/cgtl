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

#include <string>
#include <cxxtest/TestSuite.h>
#include "cgt/misc/cxxtest_defs.h"
#include "cgt/base/alloc/storage.h"


class storage_cxx : public CxxTest::TestSuite
{
  public:
    void setUp () { }
    void tearDown () { } 

  public:
    void test_basic ()
    {
      cgt::base::alloc::_Storage<int> storage;
//      cgt::base::alloc::_Storage<int>::_Chunk::_Block* ptr_block1 = storage._free;
//      cgt::base::alloc::_Storage<int>::_Chunk::_Block* ptr_block2 = ptr_block1->_next;
//      cgt::base::alloc::_Storage<int>::_Chunk::_Block* ptr_block3 = ptr_block2->next;

      TS_ASSERT_EQUALS (storage._free, static_cast<cgt::base::alloc::_Storage<int>::_Chunk::_Block*>(NULL));

      int* ptr = storage.allocate ();
      new (ptr) int (1);

      TS_ASSERT_EQUALS (*ptr, 1);
      TS_ASSERT_EQUALS (storage._free, reinterpret_cast<cgt::base::alloc::_Storage<int>::_Chunk::_Block*>(ptr+1));

      storage.deallocate (ptr);
    }
};

#endif // __CGTL__CXXTEST_CGT_BASE_ALLOC_STORAGE_CXX_H_
