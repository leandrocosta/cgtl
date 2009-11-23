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
 * \file cgt/graph_edge.h
 * \brief [brief description]
 * \author Leandro Costa
 * \date 2009
 *
 * $LastChangedDate$
 * $LastChangedBy$
 * $Revision$
 */

#ifndef __CGTL__CGT_GRAPH_EDGE_H_
#define __CGTL__CGT_GRAPH_EDGE_H_


namespace cgt
{
  template<typename _TpVertex, typename _TpEdge>
    class _GraphEdge
    {
      private:
        typedef _GraphVertex<_TpVertex> _Vertex;

      public:
        _GraphEdge (const _TpEdge& _e, _Vertex& _v1, _Vertex& _v2) : _value (_e), _vertex1 (_v1), _vertex2 (_v2) { }

      public:
        const _TpEdge& value () const { return _value; }
        _Vertex& v1 () const { return _vertex1; }
        _Vertex& v2 () const { return _vertex2; }

        const string to_string () const
        {
          ostringstream s;
          s << "(" << _value << ", " << _vertex1.value () << ", " << _vertex2.value () << ")";
          return s.str ();
        }

      private:
        _TpEdge   _value;
        _Vertex&  _vertex1;
        _Vertex&  _vertex2;
    };
}

#endif // __CGTL__CGT_GRAPH_EDGE_H_
