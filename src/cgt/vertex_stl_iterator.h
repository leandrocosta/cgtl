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
 * \file cgt/vertex_stl_iterator.h
 * \brief Contains definition of a vertex iterator.
 * \author Leandro Costa
 * \date 2009
 *
 * $LastChangedDate: 2010-04-22 06:33:26 -0300 (Qui, 22 Abr 2010) $
 * $LastChangedBy: leandro.costa $
 * $Revision: 119 $
 */

#ifndef __CGTL__CGT_VERTEX_STL_ITERATOR_H_
#define __CGTL__CGT_VERTEX_STL_ITERATOR_H_

#include <list>


namespace cgt
{
  /*!
   * \class _VertexSTLIterator
   * \brief The _VertexSTLIterator class template.
   * \author Leandro Costa
   * \date 2009
   *
   * A \b _VertexSTLIterator is an iterator of vertices. It is used when
   * we are interested only in the vertices of the graph, and not in
   * the adjacency list of each vertex.
   */

  template<typename _TpVertex, typename _TpEdge>
    class _VertexSTLIterator : public std::list<_GraphNode<_TpVertex, _TpEdge> >::iterator
    {
      private:
        typedef _GraphNode<_TpVertex, _TpEdge>	_Node;
        typedef typename std::list<_Node>::iterator		_Base;
        typedef _GraphVertex<_TpVertex>         _Vertex;

        typedef _Vertex*    pointer;
        typedef _Vertex&	reference;

      public:
        _VertexSTLIterator () { }
        _VertexSTLIterator (const _Base& _it) : _Base (_it) { }

      public:
        reference operator*() const { return _Base::operator*().vertex (); };
        pointer operator->() const { return &(operator*()); };
    };


  /*!
   * \class _VertexSTLConstIterator
   * \brief The _VertexSTLConstIterator class template.
   * \author Leandro Costa
   * \date 2009
   *
   * A \b _VertexSTLConstIterator is a const_iterator of vertices. It is used when
   * we are interested only in the vertices of the graph, and not in
   * the adjacency list of each vertex.
   */

  template<typename _TpVertex, typename _TpEdge>
    class _VertexSTLConstIterator : public std::list<_GraphNode<_TpVertex, _TpEdge> >::const_iterator
    {
        typedef _VertexSTLIterator<_TpVertex, _TpEdge> _SelfCommon;

      private:
        typedef _GraphNode<_TpVertex, _TpEdge>		_Node;
        typedef typename std::list<_Node>::const_iterator	_Base;
        typedef _GraphVertex<_TpVertex>         	_Vertex;

        typedef const _Vertex*    pointer;
        typedef const _Vertex&	reference;

      public:
        _VertexSTLConstIterator () { }
        _VertexSTLConstIterator (const _Base& _it) : _Base (_it) { }
        _VertexSTLConstIterator (const _SelfCommon& _it) : _Base (_it) { }

      public:
        reference operator*() const { return _Base::operator*().vertex (); };
        pointer operator->() const { return &(operator*()); };
    };
}

#endif // __CGTL__CGT_VERTEX_STL_ITERATOR_H_
