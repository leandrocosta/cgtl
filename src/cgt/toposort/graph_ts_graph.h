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
 * \file cgt/toposort/graph_ts_graph.h
 * \brief Contains definition of a thin graph used by topological sort iterator.
 * \author Leandro Costa
 * \date 2009
 *
 * $LastChangedDate: 2009-12-01 21:05:33 -0200 (Ter, 01 Dez 2009) $
 * $LastChangedBy: leandro.costa $
 * $Revision: 96 $
 */

#ifndef __CGTL__CGT_STCONNCOMP__GRAPH_TS_GRAPH_H_
#define __CGTL__CGT_STCONNCOMP__GRAPH_TS_GRAPH_H_

#include "cgt/toposort/graph_ts_node.h"

namespace cgt
{
  namespace toposort
  {
    /*!
     * \class _GraphTSGraph
     * \brief The graph used by topological sort iterator. It its a list of _GraphTSNodes.
     * \author Leandro Costa
     * \date 2009
     *
     * This is the graph used by topological sort algorithm. It's a
     * list of _GraphTSNodes.
     */

    template<typename _TpVertex, typename _TpEdge>
      class _GraphTSGraph : public cgt::base::list<_GraphTSNode<_TpVertex, _TpEdge> >
      {
        private:
          typedef _GraphTSNode<_TpVertex, _TpEdge>  _TSNode;

        private:
          typedef cgt::base::list<_TSNode>  _Base;

        private:
          typedef typename _Base::iterator        _Iterator;
          typedef typename _Base::const_iterator  _CIterator;

        public:
          void remove (const _TSNode& _ts_node)
          {
            _Base::remove (_ts_node);

            _Iterator _it = _Base::begin ();
            _Iterator _itEnd = _Base::end ();

            while (_it != _itEnd)
            {
              std::cout << "node: " << _it->node ().vertex ().value () << ", remove edges from " << _ts_node.node ().vertex ().value () << std::endl;
              _it->_removeEdgesFrom (_ts_node);
              ++_it;
            }
          }
      };
  }
}

#endif // __CGTL__CGT_STCONNCOMP__GRAPH_TS_GRAPH_H_
