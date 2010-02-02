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
 * \file tests/cgt/base/alloc/allocator_cxx.h
 * \brief Contains unit tests for class cgt::base::alloc::allocator.
 * \author Leandro Costa
 * \date 2009
 *
 * $LastChangedDate: 2009-11-24 22:12:23 -0200 (Tue, 24 Nov 2009) $
 * $LastChangedBy: leandro.costa $
 * $Revision: 83 $
 */

#ifndef __CGTL__CXXTEST_CGT_BASE_ALLOC_ALLOCATOR_CXX_H_
#define __CGTL__CXXTEST_CGT_BASE_ALLOC_ALLOCATOR_CXX_H_

#include <limits.h>
#include <string>
#include <cxxtest/TestSuite.h>
#include "cgt/misc/cxxtest_defs.h"
#include "cgt/base/alloc/allocator.h"


class allocator_cxx : public CxxTest::TestSuite
{
  private:
    typedef cgt::base::alloc::_Allocator<int> _Allocator_int;

  public:
    void setUp () { }
    void tearDown () { } 

  public:
    void test_basic ()
    {
      cgt::base::alloc::_Allocator<int> allocator;

      int* ptr = allocator.allocate (sizeof (int));
      allocator.construct (ptr, int (1));

      TS_ASSERT_EQUALS (allocator.max_size (), size_t (-1)/sizeof (int));
      TS_ASSERT_EQUALS (*ptr, 1);

      allocator.destroy (ptr);
      allocator.deallocate (ptr, 1);
    }

    void test_load ()
    {
      std::list<int, _Allocator_int> l;

      //for (int i = 0; i < INT_MAX; i++)
      int i;
      int max = 1000;
      for (i = 0; i <= max; i++)
        l.push_back (i);

      TS_ASSERT_EQUALS (l.back (), max);
    }
};

#endif // __CGTL__CXXTEST_CGT_BASE_ALLOC_ALLOCATOR_CXX_H_
