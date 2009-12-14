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
 * \file tests/cgt/base/vector_cxx.h
 * \brief Contains unit tests for class cgt::base::vector.
 * \author Leandro Costa
 * \date 2009
 *
 * $LastChangedDate: 2009-11-24 22:12:23 -0200 (Tue, 24 Nov 2009) $
 * $LastChangedBy: leandro.costa $
 * $Revision: 83 $
 */

#ifndef __CGTL__CXXTEST_CGT_BASE_VECTOR_CXX_H_
#define __CGTL__CXXTEST_CGT_BASE_VECTOR_CXX_H_

#include <cxxtest/TestSuite.h>
#include "cgt/misc/cxxtest_defs.h"
#include "cgt/base/vector.h"


class vector_cxx : public CxxTest::TestSuite
{
  public:
    void setUp () { }
    void tearDown () { } 

  public:
    void test_basic ()
    {
      cgt::base::vector<int> v;
      TS_ASSERT_EQUALS (v.size (), static_cast<size_t>(0));
      TS_ASSERT_EQUALS (v.empty (), true);
    }

    void test_push_back ()
    {
      cgt::base::vector<int> v;
      v.push_back (1);
      TS_ASSERT_EQUALS (v.size (), static_cast<size_t>(1));
      TS_ASSERT_EQUALS (v.empty (), false);
      TS_ASSERT_EQUALS (v[0], 1);
    }

    void test_find ()
    {
      cgt::base::vector<int> v;
      v.push_back (1);
      TS_ASSERT_DIFFERS (v.find (1), v.end ());
      TS_ASSERT_EQUALS (*(v.find (1)), 1);
    }

    void test_clear ()
    {
      cgt::base::vector<int> v;
      v.push_back (1);
      TS_ASSERT_EQUALS (v.size (), static_cast<size_t>(1));
      v.clear ();
      TS_ASSERT_EQUALS (v.size (), static_cast<size_t>(0));
      TS_ASSERT_EQUALS (v.empty (), true);
    }

    void test_pop_back ()
    {
      cgt::base::vector<int> v;
      v.push_back (1);
      v.push_back (2);
      v.push_back (3);
      TS_ASSERT_EQUALS (v.size (), static_cast<size_t>(3));
      int* p = v.pop_back ();
      TS_ASSERT_EQUALS (v.size (), static_cast<size_t>(2));
      TS_ASSERT_EQUALS (v[0], 1);
      TS_ASSERT_EQUALS (v[1], 2);
      delete p;
    }

    void test_constructor_copy ()
    {
      cgt::base::vector<int> v1;
      v1.push_back (1);
      v1.push_back (2);
      v1.push_back (3);
      cgt::base::vector<int> v2 (v1);

      TS_ASSERT_EQUALS (v1.size (), v2.size ());

      TS_ASSERT_EQUALS (*(v1.find (1)), *(v2.find (1)));
      TS_ASSERT_EQUALS (*(v1.find (2)), *(v2.find (2)));
      TS_ASSERT_EQUALS (*(v1.find (3)), *(v2.find (3)));

      TS_ASSERT_DIFFERS (&(*(v1.find (1))), &(*(v2.find (1))));
      TS_ASSERT_DIFFERS (&(*(v1.find (2))), &(*(v2.find (2))));
      TS_ASSERT_DIFFERS (&(*(v1.find (3))), &(*(v2.find (3))));
    }

    void test_operator_assign ()
    {
      cgt::base::vector<int> v1;
      v1.push_back (1);
      v1.push_back (2);
      v1.push_back (3);
      cgt::base::vector<int> v2;
      v2 = v1;

      TS_ASSERT_EQUALS (v1.size (), v2.size ());

      TS_ASSERT_EQUALS (*(v1.find (1)), *(v2.find (1)));
      TS_ASSERT_EQUALS (*(v1.find (2)), *(v2.find (2)));
      TS_ASSERT_EQUALS (*(v1.find (3)), *(v2.find (3)));

      TS_ASSERT_DIFFERS (&(*(v1.find (1))), &(*(v2.find (1))));
      TS_ASSERT_DIFFERS (&(*(v1.find (2))), &(*(v2.find (2))));
      TS_ASSERT_DIFFERS (&(*(v1.find (3))), &(*(v2.find (3))));
    }
};

#endif // __CGTL__CXXTEST_CGT_BASE_VECTOR_CXX_H_
