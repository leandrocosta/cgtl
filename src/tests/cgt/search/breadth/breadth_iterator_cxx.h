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
 * \file tests/cgt/search/breadth/breadth_iterator_cxx.h
 * \brief Contains unit tests for class cgt::search::breadth::breadth_iterator.
 * \author Leandro Costa
 * \date 2009
 *
 * $LastChangedDate: 2009-11-24 22:12:23 -0200 (Tue, 24 Nov 2009) $
 * $LastChangedBy: leandro.costa $
 * $Revision: 83 $
 */

#ifndef __CGTL__CXXTEST_CGT_SEARCH_BREADTH_BREADTH_ITERATOR_CXX_H_
#define __CGTL__CXXTEST_CGT_SEARCH_BREADTH_BREADTH_ITERATOR_CXX_H_

#include <cxxtest/TestSuite.h>
//#include "cgt/misc/cxxtest_defs.h"
#include "cgt/graph.h"


class breadth_iterator_cxx : public CxxTest::TestSuite
{
  private:
    typedef cgt::graph<int, int> mygraph;

  public:
    void setUp () { }
    void tearDown () { } 

  public:

    void test_basic ()
    {
      mygraph g;

      g.insert_vertex (1);
      g.insert_vertex (2);
      g.insert_vertex (3);
      g.insert_vertex (4);
      g.insert_vertex (5);

      g.insert_edge (10, 1, 2);
      g.insert_edge (20, 2, 3);
      g.insert_edge (30, 2, 4);
      g.insert_edge (40, 3, 5);

      mygraph::biterator it    = g.bbegin ();
      mygraph::biterator itEnd = g.bend ();

      TS_ASSERT_DIFFERS (it, itEnd);
      TS_ASSERT_EQUALS (it->vertex ().value (), 1);

      ++it;

      TS_ASSERT_DIFFERS (it, itEnd);
      TS_ASSERT_EQUALS (it->vertex ().value (), 2);

      ++it;

      TS_ASSERT_DIFFERS (it, itEnd);
      TS_ASSERT_EQUALS (it->vertex ().value (), 3);

      ++it;

      TS_ASSERT_DIFFERS (it, itEnd);
      TS_ASSERT_EQUALS (it->vertex ().value (), 4);

      ++it;

      TS_ASSERT_DIFFERS (it, itEnd);
      TS_ASSERT_EQUALS (it->vertex ().value (), 5);

      ++it;

      TS_ASSERT_EQUALS (it, itEnd);
    }
};

#endif // __CGTL__CXXTEST_CGT_SEARCH_BREADTH_BREADTH_ITERATOR_CXX_H_
