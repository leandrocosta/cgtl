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
 * \file tests/cgt/base/exception/mem_except_cxx.h
 * \brief Contains unit tests for class cgt::base::exception::mem_except.
 * \author Leandro Costa
 * \date 2009
 *
 * $LastChangedDate: 2009-11-24 22:12:23 -0200 (Tue, 24 Nov 2009) $
 * $LastChangedBy: leandro.costa $
 * $Revision: 83 $
 */

#ifndef __CGTL__CXXTEST_CGT_BASE_EXCEPTION_MEM_EXCEPT_CXX_H_
#define __CGTL__CXXTEST_CGT_BASE_EXCEPTION_MEM_EXCEPT_CXX_H_

#include <string>
#include <cxxtest/TestSuite.h>
#include "cgt/base/exception/mem_except.h"


class mem_except_cxx : public CxxTest::TestSuite
{
  public:
    void setUp () { }
    void tearDown () { } 

  public:
    void test_basic ()
    {
      cgt::base::exception::mem_except e ("test mem_except");
      TS_ASSERT_EQUALS (std::string (e.message ()), "test mem_except");
    }
};

#endif // __CGTL__CXXTEST_CGT_BASE_EXCEPTION_MEM_EXCEPT_CXX_H_
