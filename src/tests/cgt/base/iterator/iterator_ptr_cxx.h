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
 * \file tests/cgt/base/iterator/iterator_ptr_cxx.h
 * \brief Contains unit tests for class cgt::base::iterator::iterator_ptr.
 * \author Leandro Costa
 * \date 2009
 *
 * $LastChangedDate: 2009-11-24 22:12:23 -0200 (Tue, 24 Nov 2009) $
 * $LastChangedBy: leandro.costa $
 * $Revision: 83 $
 */

#ifndef __CGTL__CXXTEST_CGT_BASE_ITERATOR_ITERATOR_PTR_CXX_H_
#define __CGTL__CXXTEST_CGT_BASE_ITERATOR_ITERATOR_PTR_CXX_H_

#include <string>
#include <cxxtest/TestSuite.h>
#include "cgt/base/iterator/iterator_ptr.h"


class iterator_ptr_cxx : public CxxTest::TestSuite
{
  private:
    template<typename _TpItem, template<typename> class _TpIterator>
      class _IteratorPtrTester : public cgt::base::iterator::_IteratorPtr<_TpItem, _TpIterator>
    {
      public:
        _IteratorPtrTester () { }
        _IteratorPtrTester (_TpItem* _p) : cgt::base::iterator::_IteratorPtr<_TpItem, _TpIterator>(_p) { }
        _IteratorPtrTester (const _IteratorPtrTester<_TpItem, cgt::base::iterator::_TpCommon>& _it) : cgt::base::iterator::_IteratorPtr<_TpItem, _TpIterator>(_it) { }

      private:
        void _incr () { }
    };

  public:
    void setUp () { }
    void tearDown () { } 

  public:
    void test_basic ()
    {
      _IteratorPtrTester<int, cgt::base::iterator::_TpCommon> it1, it2;
      _IteratorPtrTester<int, cgt::base::iterator::_TpConst> it3, it4;

      TS_ASSERT_EQUALS (it1, it1);
      TS_ASSERT_EQUALS (it1, it2);
      TS_ASSERT_EQUALS (it1, it3);
      TS_ASSERT_EQUALS (it1, it4);
      TS_ASSERT_EQUALS (it2, it2);
      TS_ASSERT_EQUALS (it2, it3);
      TS_ASSERT_EQUALS (it2, it4);
      TS_ASSERT_EQUALS (it3, it3);
      TS_ASSERT_EQUALS (it3, it4);
      TS_ASSERT_EQUALS (it4, it4);
    }

    void test_common_different ()
    {
      int i = 1;

      _IteratorPtrTester<int, cgt::base::iterator::_TpCommon> it1;
      _IteratorPtrTester<int, cgt::base::iterator::_TpCommon> it2 (&i);
      _IteratorPtrTester<int, cgt::base::iterator::_TpConst> it3, it4;

      TS_ASSERT_EQUALS (it1, it1);
      TS_ASSERT_DIFFERS (it1, it2);
      TS_ASSERT_EQUALS (it1, it3);
      TS_ASSERT_EQUALS (it1, it4);
      TS_ASSERT_EQUALS (it2, it2);
      TS_ASSERT_DIFFERS (it2, it3);
      TS_ASSERT_DIFFERS (it2, it4);
      TS_ASSERT_EQUALS (it3, it3);
      TS_ASSERT_EQUALS (it3, it4);
      TS_ASSERT_EQUALS (it4, it4);
    }

    void test_const_different ()
    {
      int i = 1;

      _IteratorPtrTester<int, cgt::base::iterator::_TpCommon> it1, it2;
      _IteratorPtrTester<int, cgt::base::iterator::_TpConst> it3;
      _IteratorPtrTester<int, cgt::base::iterator::_TpConst> it4 (&i);

      TS_ASSERT_EQUALS (it1, it1);
      TS_ASSERT_EQUALS (it1, it2);
      TS_ASSERT_EQUALS (it1, it3);
      TS_ASSERT_DIFFERS (it1, it4);
      TS_ASSERT_EQUALS (it2, it2);
      TS_ASSERT_EQUALS (it2, it3);
      TS_ASSERT_DIFFERS (it2, it4);
      TS_ASSERT_EQUALS (it3, it3);
      TS_ASSERT_DIFFERS (it3, it4);
      TS_ASSERT_EQUALS (it4, it4);
    }

    void test_two_different ()
    {
      int i = 1, j = 2;

      _IteratorPtrTester<int, cgt::base::iterator::_TpCommon> it1;
      _IteratorPtrTester<int, cgt::base::iterator::_TpCommon> it2 (&i);
      _IteratorPtrTester<int, cgt::base::iterator::_TpConst> it3;
      _IteratorPtrTester<int, cgt::base::iterator::_TpConst> it4 (&j);

      TS_ASSERT_EQUALS (it1, it1);
      TS_ASSERT_DIFFERS (it1, it2);
      TS_ASSERT_EQUALS (it1, it3);
      TS_ASSERT_DIFFERS (it1, it4);
      TS_ASSERT_EQUALS (it2, it2);
      TS_ASSERT_DIFFERS (it2, it3);
      TS_ASSERT_DIFFERS (it2, it4);
      TS_ASSERT_EQUALS (it3, it3);
      TS_ASSERT_DIFFERS (it3, it4);
      TS_ASSERT_EQUALS (it4, it4);
    }

    void test_all_different ()
    {
      int i = 1, j = 2, k = 3, l = 4;

      _IteratorPtrTester<int, cgt::base::iterator::_TpCommon> it1 (&i);
      _IteratorPtrTester<int, cgt::base::iterator::_TpCommon> it2 (&j);
      _IteratorPtrTester<int, cgt::base::iterator::_TpConst> it3 (&k);
      _IteratorPtrTester<int, cgt::base::iterator::_TpConst> it4 (&l);

      TS_ASSERT_EQUALS (it1, it1);
      TS_ASSERT_DIFFERS (it1, it2);
      TS_ASSERT_DIFFERS (it1, it3);
      TS_ASSERT_DIFFERS (it1, it4);
      TS_ASSERT_EQUALS (it2, it2);
      TS_ASSERT_DIFFERS (it2, it3);
      TS_ASSERT_DIFFERS (it2, it4);
      TS_ASSERT_EQUALS (it3, it3);
      TS_ASSERT_DIFFERS (it3, it4);
      TS_ASSERT_EQUALS (it4, it4);
    }

    void test_constructor_copy ()
    {
      int i = 1, j = 2;

      _IteratorPtrTester<int, cgt::base::iterator::_TpCommon> it1 (&i);
      _IteratorPtrTester<int, cgt::base::iterator::_TpCommon> it2 = it1;
      _IteratorPtrTester<int, cgt::base::iterator::_TpConst> it3 (&j);
      _IteratorPtrTester<int, cgt::base::iterator::_TpConst> it4 = it3;

      TS_ASSERT_EQUALS (it1, it1);
      TS_ASSERT_EQUALS (it1, it2);
      TS_ASSERT_DIFFERS (it1, it3);
      TS_ASSERT_DIFFERS (it1, it4);
      TS_ASSERT_EQUALS (it2, it2);
      TS_ASSERT_DIFFERS (it2, it3);
      TS_ASSERT_DIFFERS (it2, it4);
      TS_ASSERT_EQUALS (it3, it3);
      TS_ASSERT_EQUALS (it3, it4);
      TS_ASSERT_EQUALS (it4, it4);
    }

    void test_constructor_copy_const ()
    {
      int i = 1, j = 2;

      _IteratorPtrTester<int, cgt::base::iterator::_TpCommon> it1 (&i);
      _IteratorPtrTester<int, cgt::base::iterator::_TpCommon> it2 (&j);
      _IteratorPtrTester<int, cgt::base::iterator::_TpConst> it3 = it1;
      _IteratorPtrTester<int, cgt::base::iterator::_TpConst> it4 = it2;

      TS_ASSERT_EQUALS (it1, it1);
      TS_ASSERT_DIFFERS (it1, it2);
      TS_ASSERT_EQUALS (it1, it3);
      TS_ASSERT_DIFFERS (it1, it4);
      TS_ASSERT_EQUALS (it2, it2);
      TS_ASSERT_DIFFERS (it2, it3);
      TS_ASSERT_EQUALS (it2, it4);
      TS_ASSERT_EQUALS (it3, it3);
      TS_ASSERT_DIFFERS (it3, it4);
      TS_ASSERT_EQUALS (it4, it4);
    }
};

#endif // __CGTL__CXXTEST_CGT_BASE_ITERATOR_ITERATOR_PTR_CXX_H_
