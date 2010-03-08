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
 * \file cgt/toposort/toposort_iterator.h
 * \brief Contains definition of an iterator that implements topological sort algorithm.
 * \author Leandro Costa
 * \date 2009
 *
 * $LastChangedDate$
 * $LastChangedBy$
 * $Revision$
 */

#ifndef __CGTL__CGT_TOPOSORT_TOPOSORT_ITERATOR_H_
#define __CGTL__CGT_TOPOSORT_TOPOSORT_ITERATOR_H_


namespace cgt
{
    /*!
     * \namespace cgt::toposort
     * \brief Where are defined structures related to topological sort algorithms.
     * \author Leandro Costa
     * \date 2009
     */

  namespace toposort
  {
    /*!
     * \class _ToposortIterator
     * \brief An iterator that implements topological sort algorithm.
     * \author Leandro Costa
     * \date 2009
     *
     * This iterator executes topological sort algorithm and returns nodes
     * in the order found by the algorithm.
     */

    template<typename _TpVertex, typename _TpEdge, template<typename> class _TpIterator = cgt::base::iterator::_TpCommon>
      class _ToposortIterator
      {
        private:
          friend class _ToposortIterator<_TpVertex, _TpEdge, cgt::base::iterator::_TpConst>;

        private:
          typedef _ToposortIterator<_TpVertex, _TpEdge, _TpIterator>  _Self;
          typedef _ToposortIterator<_TpVertex, _TpEdge, cgt::base::iterator::_TpCommon>    _SelfCommon;

        public:
          _ToposortIterator () { }
      };
    }
  }
}

#endif // __CGTL__CGT_TOPOSORT_TOPOSORT_ITERATOR_H_
