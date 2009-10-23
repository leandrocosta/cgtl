#ifndef _DIJKSTRA_INFO_H_
#define _DIJKSTRA_INFO_H_

#include "dijkstra_distance.h"
#include "../graph_node.h"
using namespace cgt;


namespace cgt
{
  /*
   * keep informations about dijkstra algorithm nodes
   * like distance.
   */

  template<typename _TpVertex, typename _TpEdge>
    class _DijkstraInfo
    {
      private:
        typedef _DijkstraInfo<_TpVertex, _TpEdge> _Self;
        typedef _GraphNode<_TpVertex, _TpEdge>    _Node;
        typedef _DijkstraDistance<_TpEdge>        _Distance;

      public:
        _DijkstraInfo (_Node& _n) : _node (_n), _ptr_previous (NULL) { }

      public:
        const bool operator==(const _DijkstraInfo& _d) { return (_node.vertex () == _d._node.vertex ()); }
        const bool operator!=(const _DijkstraInfo& _d) { return ! (*this == _d); }

      public:
        _Node& node () const { return _node; }
        void _set_distance (const _TpEdge &_d) { _distance._set_distance (_d); }
        const _TpEdge& distance () const { return _distance.distance (); }
        const bool &inf_distance () const { return _distance.inf_distance (); }
        void _set_previous (const _Node* const _ptr) { _ptr_previous = _ptr; }
        const _Node* const previous () const { return _ptr_previous; }

      private:
        _Node&        _node;
        _Distance     _distance;
        const _Node*  _ptr_previous;
    };
}

#endif
