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

#ifndef __CGTL__CGT_TOPOSORT__TOPOSORT_ITERATOR_H_
#define __CGTL__CGT_TOPOSORT__TOPOSORT_ITERATOR_H_

#include "cgt/toposort/graph_ts_graph.h"

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
     *
     *
     * Algorithm (Kahn) [source: http://en.wikipedia.org/wiki/Topological_sorting]:
     *
     * L ← Empty list that will contain the sorted elements
     * S ← Set of all nodes with no incoming edges
     * while S is non-empty do
     *   remove a node n from S
     *   insert n into L
     *   for each node m with an edge e from n to m do
     *     remove edge e from the graph
     *     if m has no other incoming edges then
     *       insert m into S
     * if graph has edges then
     *   output error message (graph has at least one cycle)
     * else 
     *   output message (proposed topologically sorted order: L)
     */

    template<typename _TpVertex, typename _TpEdge, template<typename> class _TpIterator = cgt::base::iterator::_TpCommon>
      class _ToposortIterator
      {
        private:
          friend class _ToposortIterator<_TpVertex, _TpEdge, cgt::base::iterator::_TpConst>;

        private:
          typedef _ToposortIterator<_TpVertex, _TpEdge, _TpIterator>  _Self;
          typedef _ToposortIterator<_TpVertex, _TpEdge, cgt::base::iterator::_TpCommon>    _SelfCommon;

          typedef _GraphNode<_TpVertex, _TpEdge>            _Node;
          typedef typename cgt::base::list<_Node>::iterator _NodeIterator;
          typedef _GraphEdge<_TpVertex, _TpEdge>            _Edge;

          typedef _GraphTSNode<_TpVertex, _TpEdge>    _TSNode;
          typedef _GraphTSGraph<_TpVertex, _TpEdge>   _TSGraph;

          typedef typename _TSGraph::iterator        _TSGraphIterator;
          typedef typename _TSGraph::const_iterator  _TSGraphCIterator;

        private:
          typedef typename _TpIterator<_Node>::pointer    pointer;
          typedef typename _TpIterator<_Node>::reference  reference;

        public:
          _ToposortIterator () : _ptr_node (NULL) { }

          _ToposortIterator (const _NodeIterator& _it_begin, const _NodeIterator& _it_end)
            : _ptr_node (NULL)
          {
            _init (_it_begin, _it_end);
          }

          _ToposortIterator (const _SelfCommon& _it)
          { *this = _it; }

        public:
          const _Self& operator=(const _SelfCommon& _it)
          {
            _ptr_node     = _it._ptr_node;
            _auxGraph     = _it._auxGraph;
            _auxGraphNoIn = _it._auxGraphNoIn;
            _it_auxgraph  = _it._it_auxgraph;

            return *this;
          }

        private:
          void _init (const _NodeIterator& _it_begin, const _NodeIterator& _it_end);

        public:
          reference operator*() const { return *_ptr_node; }
          pointer operator->() const { return _ptr_node; }
          const bool operator==(const _Self& _other) const { return _ptr_node == _other._ptr_node; }
          const bool operator!=(const _Self& _other) const { return !(*this == _other); }
          _Self& operator++();
          const _Self operator++(int);

        private:
          _Node*            _ptr_node;
          _TSGraph          _auxGraph;      /*!< set of all nodes, initialized by _init () */
          _TSGraph          _auxGraphNoIn;  /*!< set of all nodes with no incoming edges */
          _TSGraphIterator  _it_auxgraph;
      };

    template<typename _TpVertex, typename _TpEdge, template<typename> class _TpIterator>
      void _ToposortIterator<_TpVertex, _TpEdge, _TpIterator>::_init (const _NodeIterator& _it_begin, const _NodeIterator& _it_end)
      {
        _NodeIterator _it = _it_begin;

        /*! insert all nodes into auxiliary graph */
        while (_it != _it_end)
        {
          _auxGraph.insert (_TSNode (*_it));
          ++_it;
        }

        _TSGraphIterator _it1 = _auxGraph.begin ();
        _TSGraphIterator _itEnd = _auxGraph.end ();
        _Edge* _ptr_edge = NULL;

        /*! insert all edges into auxiliary graph */
        while (_it1 != _itEnd)
        {
          _TSNode& _tsn1 = *_it1;
          _TSGraphIterator _it2 = _it1;
          ++_it2;

          while (_it2 != _itEnd)
          {
            _TSNode& _tsn2 = *_it2;

            /*! if there is an edge between _ts1 and _ts2, insert edge to auxiliary graph */
            if ((_ptr_edge = _tsn1.node ()._get_edge (_tsn2.node ().vertex ())))
              _tsn2._insert_inverse (*_ptr_edge, _tsn1.node ());

            ++_it2;
          }

          ++_it1;
        }

        _TSGraphIterator _itAux = _auxGraph.begin ();
        _TSGraphIterator _itAuxEnd = _auxGraph.end ();

        while (_itAux != _itAuxEnd)
        {
          _TSNode& _ts_node = *_itAux;

          /*! if there's no edge arriving into _ts_node, insert _ts_node into _auxGraphNoIn */
          if (_ts_node.iadjlist ().empty ())
          {
            std::cout << "insert into _auxGraphNoIn: " << _ts_node.node ().vertex ().value () << std::endl;
            _auxGraphNoIn.insert (_ts_node);
          }

          ++_itAux;
        }

        _itAux = _auxGraphNoIn.begin ();
        _itAuxEnd = _auxGraphNoIn.end ();

        while (_itAux != _itAuxEnd)
        {
          /*! remove these nodes from _auxGraph */
            std::cout << "remove from _auxGraph: " << _itAux->node ().vertex ().value () << std::endl;
          _auxGraph.remove (*_itAux);
          ++_itAux;
        }
      }

    template<typename _TpVertex, typename _TpEdge, template<typename> class _TpIterator>
      _ToposortIterator<_TpVertex, _TpEdge, _TpIterator>& _ToposortIterator<_TpVertex, _TpEdge, _TpIterator>::operator++ ()
      {
        std::cout << "operator++ () - begin" << std::endl;

        if (_it_auxgraph != _auxGraph.end ())
        {
          _ptr_node = &(_it_auxgraph->node ());
          ++_it_auxgraph;
          std::cout << "operator++ () - node: " << _ptr_node->vertex ().value () << std::endl;
          if (_it_auxgraph != _auxGraph.end ())
            std::cout << "operator () - next: " << _it_auxgraph->node ().vertex ().value () << std::endl;
        }
        else
        {
          std::cout << "operator++ () - _it_auxgraph == _auxGraph.end ()" << std::endl;
          _ptr_node = NULL;
        }

        return *this;
      }

    template<typename _TpVertex, typename _TpEdge, template<typename> class _TpIterator>
      const _ToposortIterator<_TpVertex, _TpEdge, _TpIterator> _ToposortIterator<_TpVertex, _TpEdge, _TpIterator>::operator++(int)
      {
        _Self _it = *this;
        operator++();
        return _it;
      }

  }
}

#endif // __CGTL__CGT_TOPOSORT__TOPOSORT_ITERATOR_H_
