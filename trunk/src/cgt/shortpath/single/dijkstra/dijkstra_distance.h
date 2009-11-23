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
 * \file cgt/shortpath/single/dijkstra/dijkstra_distance.h
 * \brief [brief description]
 * \author Leandro Costa
 * \date 2009
 *
 * $LastChangedDate$
 * $LastChangedBy$
 * $Revision$
 */

#ifndef __CGTL__CGT_SHORTPATH_SINGLE_DIJKSTRA_DIJKSTRA_DISTANCE_H_
#define __CGTL__CGT_SHORTPATH_SINGLE_DIJKSTRA_DIJKSTRA_DISTANCE_H_

#include "../../../graph_node.h"


namespace cgt
{
  namespace shortpath
  {
    namespace single
    {
      namespace dijkstra
      {
        template<typename _TpEdge>
          class _DijkstraDistance
          {
            public:
              _DijkstraDistance () : _inf (true) { }

            public:
              void _set_distance (const _TpEdge &_d) { _distance = _d; _inf = false; }
              const _TpEdge& distance () const { return _distance; }
              const bool &inf_distance () const { return _inf; }

            private:
              _TpEdge _distance;
              bool    _inf;
          };

        template<> _DijkstraDistance<char>::_DijkstraDistance ()            : _distance (0), _inf (true) { }
        template<> _DijkstraDistance<unsigned char>::_DijkstraDistance ()   : _distance (0), _inf (true) { }
        template<> _DijkstraDistance<short>::_DijkstraDistance ()           : _distance (0), _inf (true) { }
        template<> _DijkstraDistance<unsigned short>::_DijkstraDistance ()  : _distance (0), _inf (true) { }
        template<> _DijkstraDistance<int>::_DijkstraDistance ()             : _distance (0), _inf (true) { }
        template<> _DijkstraDistance<unsigned int>::_DijkstraDistance ()    : _distance (0), _inf (true) { }
        template<> _DijkstraDistance<long>::_DijkstraDistance ()            : _distance (0), _inf (true) { }
        template<> _DijkstraDistance<unsigned long>::_DijkstraDistance ()   : _distance (0), _inf (true) { }
        template<> _DijkstraDistance<string>::_DijkstraDistance ()          : _distance (""),_inf (true) { }

        // TODO: define constructors for all primitive types
      }
    }
  }
}

#endif // __CGTL__CGT_SHORTPATH_SINGLE_DIJKSTRA_DIJKSTRA_DISTANCE_H_
