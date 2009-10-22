#ifndef _DIJKSTRA_INFO_H_
#define _DIJKSTRA_INFO_H_

#include "../graph_node.h"
using namespace cgt;


namespace cgt
{
  /*
   * keep informations about dijkstra algorithm nodes
   * like distance.
   */

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

  template<typename _TpVertex, typename _TpEdge>
    class _DijkstraInfo
    {
      private:
        typedef _GraphNode<_TpVertex, _TpEdge>  _Node;
        typedef _DijkstraDistance<_TpEdge>      _Distance;

      public:
        _DijkstraInfo (_Node& _n) : _node (_n) { }

      public:
        const bool operator==(const _DijkstraInfo& _other) { return (_node.vertex () == _other._node.vertex ()); }

      public:
        _Node& node () const { return _node; }
        void _set_distance (const _TpEdge &_d) { _distance._set_distance (_d); }
        const _TpEdge& distance () const { return _distance.distance (); }
        const bool &inf_distance () const { return _distance.inf_distance (); }

      private:
        _Node&    _node;
        _Distance _distance;
    };

  template<>
    _DijkstraDistance<int>::_DijkstraDistance () : _distance (0), _inf (true) { }
}

#endif
