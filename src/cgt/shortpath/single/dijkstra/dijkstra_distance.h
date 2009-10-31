#ifndef _DIJKSTRA_DISTANCE_H_
#define _DIJKSTRA_DISTANCE_H_

#include "../../../graph_node.h"
using namespace cgt;


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

#endif
