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
 * \file tests/cgt/base/hash_cxx.h
 * \brief Contains unit tests for class cgt::base::hash.
 * \author Leandro Costa
 * \date 2009
 *
 * $LastChangedDate: 2009-11-24 22:12:23 -0200 (Tue, 24 Nov 2009) $
 * $LastChangedBy: leandro.costa $
 * $Revision: 83 $
 */

#ifndef __CGTL__CXXTEST_CGT_BASE_HASH_CXX_H_
#define __CGTL__CXXTEST_CGT_BASE_HASH_CXX_H_

#include <cxxtest/TestSuite.h>

#include <string>

#include "cgt/misc/cxxtest_defs.h"
#include "cgt/base/hash.h"


class hash_cxx : public CxxTest::TestSuite
{
  public:
    void setUp () { }
    void tearDown () { } 

  public:
    void test_basic ()
    {
      cgt::base::hash<int, std::string> h;
      TS_ASSERT_EQUALS (h.size (), static_cast<size_t>(0));
      TS_ASSERT_EQUALS (h.empty (), true);
    }

    void test_insert ()
    {
      cgt::base::hash<int, std::string> h;
      h.insert (1, "one");
      TS_ASSERT_EQUALS (*(h[1]), "one");
      TS_ASSERT_EQUALS (h[2], static_cast<std::string *>(NULL));
    }

    void test_iterator ()
    {
      cgt::base::hash<int, std::string> h;
      cgt::base::hash<int, std::string>::iterator it = h.begin ();
      TS_ASSERT_EQUALS (it, h.end ());

      h.insert (1, "one");
      it = h.begin ();
      TS_ASSERT_EQUALS (it->first, 1);
      TS_ASSERT_EQUALS (it->second, "one");
      TS_ASSERT_DIFFERS (it, h.end ());
      it++;
      TS_ASSERT_EQUALS (it, h.end ());

      h.insert (2, "two");
      h.insert (3, "three");
      it = h.begin ();
      ++it;
      it++;
      ++it;
      TS_ASSERT_EQUALS (it, h.end ());
    }

    void test_constructor_copy ()
    {
      cgt::base::hash<int, std::string> h1;
      h1.insert (1, "one");
      h1.insert (2, "two");
      h1.insert (3, "three");

      cgt::base::hash<int, std::string> h2 (h1);

      TS_ASSERT_EQUALS (h1.size (), h2.size ());

      cgt::base::hash<int, std::string>::const_iterator it1 = h1.begin ();
      cgt::base::hash<int, std::string>::const_iterator it2 = h2.begin ();

      TS_ASSERT_DIFFERS (it1, it2);
      TS_ASSERT_EQUALS (it1->first, it2->first);
      TS_ASSERT_DIFFERS (&(it1->first), &(it2->first));
      TS_ASSERT_EQUALS (it1->second, it2->second);
      TS_ASSERT_DIFFERS (&(it1->second), &(it2->second));

      it1++;
      it2++;

      TS_ASSERT_DIFFERS (it1, it2);
      TS_ASSERT_EQUALS (it1->first, it2->first);
      TS_ASSERT_DIFFERS (&(it1->first), &(it2->first));
      TS_ASSERT_EQUALS (it1->second, it2->second);
      TS_ASSERT_DIFFERS (&(it1->second), &(it2->second));

      ++it1;
      ++it2;

      TS_ASSERT_DIFFERS (it1, it2);
      TS_ASSERT_EQUALS (it1->first, it2->first);
      TS_ASSERT_DIFFERS (&(it1->first), &(it2->first));
      TS_ASSERT_EQUALS (it1->second, it2->second);
      TS_ASSERT_DIFFERS (&(it1->second), &(it2->second));

      it1++;
      it2++;

      TS_ASSERT_EQUALS (it1, it2);
      TS_ASSERT_EQUALS (it1, h1.end ());
      TS_ASSERT_EQUALS (it2, h2.end ());
    }

    void test_operator_assign ()
    {
      cgt::base::hash<int, std::string> h1;
      h1.insert (1, "one");
      h1.insert (2, "two");
      h1.insert (3, "three");

      cgt::base::hash<int, std::string> h2 (h1);

      TS_ASSERT_EQUALS (h1.size (), h2.size ());

      cgt::base::hash<int, std::string>::const_iterator it1 = h1.begin ();
      cgt::base::hash<int, std::string>::const_iterator it2 = h2.begin ();

      TS_ASSERT_DIFFERS (it1, it2);
      TS_ASSERT_EQUALS (it1->first, it2->first);
      TS_ASSERT_DIFFERS (&(it1->first), &(it2->first));
      TS_ASSERT_EQUALS (it1->second, it2->second);
      TS_ASSERT_DIFFERS (&(it1->second), &(it2->second));

      it1++;
      it2++;

      TS_ASSERT_DIFFERS (it1, it2);
      TS_ASSERT_EQUALS (it1->first, it2->first);
      TS_ASSERT_DIFFERS (&(it1->first), &(it2->first));
      TS_ASSERT_EQUALS (it1->second, it2->second);
      TS_ASSERT_DIFFERS (&(it1->second), &(it2->second));

      ++it1;
      ++it2;

      TS_ASSERT_DIFFERS (it1, it2);
      TS_ASSERT_EQUALS (it1->first, it2->first);
      TS_ASSERT_DIFFERS (&(it1->first), &(it2->first));
      TS_ASSERT_EQUALS (it1->second, it2->second);
      TS_ASSERT_DIFFERS (&(it1->second), &(it2->second));

      it1++;
      it2++;

      TS_ASSERT_EQUALS (it1, it2);
      TS_ASSERT_EQUALS (it1, h1.end ());
      TS_ASSERT_EQUALS (it2, h2.end ());
    }
};

#endif // __CGTL__CXXTEST_CGT_BASE_HASH_CXX_H_
