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
 * \file cgt/graph_adjlist.h
 * \brief Contains definition of an adjacency's list.
 * \author Leandro Costa
 * \date 2009
 *
 * $LastChangedDate$
 * $LastChangedBy$
 * $Revision$
 */

#ifndef __CGTL__CGT_GRAPH_ADJLIST_H_
#define __CGTL__CGT_GRAPH_ADJLIST_H_

#include "cgt/graph_adjacency.h"
#include "cgt/graph_vertex.h"
#include "cgt/base/list.h"


namespace cgt
{
  /*!
   * \class _GraphAdjList
   * \brief The _GraphAdjList class template.
   * \author Leandro Costa
   * \date 2009
   *
   * A \b _GraphAdjList is a list of objects from type _GraphAdjacency.
   * Each \b _GraphNode has a list of adjacencies, and from this list
   * it is possible to visit all nodes that are linked to the node
   * to which the adjacency list belongs.
   */

  template<typename _TpVertex, typename _TpEdge>
    class _GraphAdjList : public cgt::base::list<_GraphAdjacency<_TpVertex, _TpEdge> >
  {
    private:
      typedef _GraphAdjList<_TpVertex, _TpEdge>   _Self;
      typedef _GraphNode<_TpVertex, _TpEdge>      _Node;
      typedef _GraphEdge<_TpVertex, _TpEdge>      _Edge;
      typedef _GraphVertex<_TpVertex>             _Vertex;
      typedef _GraphAdjacency<_TpVertex, _TpEdge> _Adjacency;
      typedef cgt::base::list<_Adjacency>         _Base;
      typedef typename _Base::const_iterator      _Iterator;

    public:
      _Edge* _get_edge (const _Vertex& _v) const;

    public:
      void _insert (_Edge& _e, _Node& _n);
  };

  template<typename _TpVertex, typename _TpEdge>
    _GraphEdge<_TpVertex, _TpEdge>* _GraphAdjList<_TpVertex, _TpEdge>::_get_edge (const _Vertex& _v) const
    {
      _Edge *_ptr_edge = NULL;

      _Iterator it;
      _Iterator itEnd = _Base::end ();

      for (it = _Base::begin (); it != itEnd; ++it)
      {
        if (it->vertex () == _v)
        {
          _ptr_edge = &(it->edge ());
          break;
        }
      }

      return _ptr_edge;
    }

  template<typename _TpVertex, typename _TpEdge>
    void _GraphAdjList<_TpVertex, _TpEdge>::_insert (_Edge& _e, _Node& _n)
    {
      _Base::insert (_Adjacency (_e, _n));
    }
}

#endif // __CGTL__CGT_GRAPH_ADJLIST_H_
