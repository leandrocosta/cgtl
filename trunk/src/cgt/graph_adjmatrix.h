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
 * \file cgt/graph_adjmatrix.h
 * \brief Contains the definition of an adjacency matrix represented graph
 */

#ifndef __CGTL__CGT_GRAPH_ADJMATRIX_H_
#define __CGTL__CGT_GRAPH_ADJMATRIX_H_

#include "cgt/graph_type.h"
#include "cgt/graph_node.h"
#include "cgt/graph_vertex.h"
#include "cgt/base/list.h"
#include "cgt/misc/debug.h"


namespace cgt
{
  template<typename _TpVertex, typename _TpEdge, typename _TpGraphType>
    class graph;


  /*!
   * \class _GraphAdjMatrix
   * \brief The adjacency matrix representation of a graph.
   *
   * An adjacency matrix is a list of nodes. Each node has a vertex
   * and a list of adjacencies. Each adjacency is represented by
   * a pair: an edge and a reference to the other node.
   */

  template<typename _TpVertex, typename _TpEdge, typename _TpGraphType>
    class _GraphAdjMatrix : private cgt::base::list<_GraphNode<_TpVertex, _TpEdge> >
  {
    private:
      friend class graph<_TpVertex, _TpEdge, _TpGraphType>;

    private:
      typedef _GraphAdjMatrix<_TpVertex, _TpEdge, _TpGraphType> _Self;

    private:
      typedef _GraphNode<_TpVertex, _TpEdge>  _Node;
      typedef _GraphEdge<_TpVertex, _TpEdge>  _Edge;
      typedef _GraphVertex<_TpVertex>         _Vertex;
      typedef cgt::base::list<_Node>          _Base;

    private:
      /**
       * A method to get a node pointer by its vertex.
       * @param _vertex a reference to the vertex.
       * @return A pointer to the node (NULL if the vertex is not found in graph).
       */
      _Node* _get_node (const _TpVertex &_vertex);

      typename _Base::iterator _find (const _TpVertex &_vertex);

    private:
      void _insert_node (const _TpVertex &_vertex);
      void _insert_vertex (const _TpVertex &_vertex);
      void _insert_edge (const _TpEdge &_e, const _TpVertex &_v1, const _TpVertex &_v2);
      void _insert_edge (_Node& _n1, _Node& _n2, _Vertex& _v1, _Vertex& _v2, _Edge& _e);

    private:
      void _invert ();

    private:
      const bool _is_directed () const;
      const bool _is_undirected () const;

    private:
      _TpGraphType  _type; /** < directed or undirected */

      /*
       * We need a list of edges for two reasons:
       *  - first, that's an easy way to create the edge_iterator,
       *    since we only need to export a list iterator to users;
       *  - second, we use a reference to these edges in the 
       *    adjacency matrix. This way we can create only one
       *    edge and use it twice in undirected graphs.
       */

      cgt::base::list<_Edge>  _edge_list;
  };


  template<typename _TpVertex, typename _TpEdge, typename _TpGraphType>
    _GraphNode<_TpVertex, _TpEdge>* _GraphAdjMatrix<_TpVertex, _TpEdge, _TpGraphType>::_get_node (const _TpVertex &_vertex)
    {
      _Node *_ptr_node = NULL;

      typename _Base::iterator it;
      typename _Base::iterator itEnd = _Base::end ();

      for (it = _Base::begin (); it != itEnd; ++it)
      {
        if (it->vertex () == _vertex)
        {
          _ptr_node = &(*it);
          break;
        }
      }

      return _ptr_node;
    }

  template<typename _TpVertex, typename _TpEdge, typename _TpGraphType>
    typename cgt::base::list<_GraphNode<_TpVertex, _TpEdge> >::iterator _GraphAdjMatrix<_TpVertex, _TpEdge, _TpGraphType>::_find (const _TpVertex &_vertex)
    {
      typename _Base::iterator it    = _Base::begin ();
      typename _Base::iterator itEnd = _Base::end ();

      while (it != itEnd && it->vertex () != _vertex)
        it++;
     
      return it;
    }

  template<typename _TpVertex, typename _TpEdge, typename _TpGraphType>
    void _GraphAdjMatrix<_TpVertex, _TpEdge, _TpGraphType>::_insert_node (const _TpVertex &_vertex)
    {
      insert (_GraphNode<_TpVertex, _TpEdge> (_vertex));
    }

  template<typename _TpVertex, typename _TpEdge, typename _TpGraphType>
    void _GraphAdjMatrix<_TpVertex, _TpEdge, _TpGraphType>::_insert_vertex (const _TpVertex &_vertex)
    {
      _Node *_ptr = _get_node (_vertex);

      if (! _ptr)
        _insert_node (_vertex);
      else
        _brk ();
    }

  template<typename _TpVertex, typename _TpEdge, typename _TpGraphType>
    void _GraphAdjMatrix<_TpVertex, _TpEdge, _TpGraphType>::_insert_edge (const _TpEdge &_e, const _TpVertex &_v1, const _TpVertex &_v2)
    {
      _Node *_ptr_n1 = _get_node (_v1);

      if (_ptr_n1)
      {
        _Node *_ptr_n2 = _get_node (_v2);

        if (_ptr_n2)
        {
          _Vertex& _vertex2 = _ptr_n2->vertex ();

          if (! _ptr_n1->_get_edge (_vertex2))
          {
            _Vertex& _vertex1 = _ptr_n1->vertex ();
            _Edge &_edge = _edge_list.insert (_Edge (_e, _vertex1, _vertex2));
            _insert_edge (*_ptr_n1, *_ptr_n2, _vertex1, _vertex2, _edge);
          }
        }
      }
    }

  template<typename _TpVertex, typename _TpEdge, typename _TpGraphType>
    void _GraphAdjMatrix<_TpVertex, _TpEdge, _TpGraphType>::_insert_edge (_Node& _n1, _Node& _n2, _Vertex& _v1, _Vertex& _v2, _Edge& _e)
    {
      _n1._insert (_e, _n2);

      if (! _type._directed && ! _n2._get_edge (_v1))
        _n2._insert (_e, _n1);
    }

  template<typename _TpVertex, typename _TpEdge, typename _TpGraphType>
    void _GraphAdjMatrix<_TpVertex, _TpEdge, _TpGraphType>::_invert ()
    {
      /*
       * for each node, call _invert_edges ()
       */

      typename _Base::iterator it;
      typename _Base::iterator itEnd = _Base::end ();

      for (it = _Base::begin (); it != itEnd; ++it)
        it->_invert_edges ();
    }

  template<typename _TpVertex, typename _TpEdge, typename _TpGraphType>
    const bool _GraphAdjMatrix<_TpVertex, _TpEdge, _TpGraphType>::_is_directed () const
    {
      return _type._directed;
    }

  template<typename _TpVertex, typename _TpEdge, typename _TpGraphType>
    const bool _GraphAdjMatrix<_TpVertex, _TpEdge, _TpGraphType>::_is_undirected () const
    {
      return (! _is_directed ());
    }
}

#endif
