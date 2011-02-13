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
 * \file tests/cgt/search/search_state_cxx.h
 * \brief Contains unit tests for class cgt::search::_SearchState.
 * \author Leandro Costa
 * \date 2009
 *
 * $LastChangedDate: 2009-11-24 22:12:23 -0200 (Tue, 24 Nov 2009) $
 * $LastChangedBy: leandro.costa $
 * $Revision: 83 $
 */

#ifndef __CGTL__CXXTEST_CGT_SEARCH_SEARCH_STATE_CXX_H_
#define __CGTL__CXXTEST_CGT_SEARCH_SEARCH_STATE_CXX_H_

#include <cxxtest/TestSuite.h>
#include "cgt/misc/cxxtest_defs.h"
#include "cgt/graph.h"

#include <list>


class search_state_cxx : public CxxTest::TestSuite
{
  private:
    typedef cgt::_GraphNode<int, int>          	_Node;
    typedef cgt::search::_SearchState<int, int>	_State;

  public:
    void setUp () { }
    void tearDown () { } 

  public:
    void test_basic ()
    {
      _Node _n (1);
      _State _s (_n);

	  /*
      TS_ASSERT_EQUALS (_s.node ().vertex ().value (), 1);
      TS_ASSERT_EQUALS (_s.parent (), static_cast<_Node*>(NULL));
      TS_ASSERT_EQUALS (_s.color (), _Info::WHITE);
      TS_ASSERT_EQUALS (_s.discovery (), static_cast<unsigned long>(0));
      TS_ASSERT_EQUALS (_s.finish (), static_cast<unsigned long>(0));
	  */
    }

	/*
    void atest_set ()
    {
      _Node _n1 (1);
      _Node _n2 (2);
      _Info _s (_n1);

      _s.set_parent (&_n2);
      _s.set_color (_Info::GRAY);
      _s.set_discovery (5);
      _s.set_finish (10);

      TS_ASSERT_EQUALS (_s.node ().vertex ().value (), 1);
      TS_ASSERT_EQUALS (_s.parent (), &_n2);
      TS_ASSERT_EQUALS (_s.color (), _Info::GRAY);
      TS_ASSERT_EQUALS (_s.discovery (), static_cast<unsigned long>(5));
      TS_ASSERT_EQUALS (_s.finish (), static_cast<unsigned long>(10));
    }
	*/
};

#endif // __CGTL__CXXTEST_CGT_SEARCH_SEARCH_STATE_CXX_H_
