#ifndef _SEARCH_STATE_H_
#define _SEARCH_STATE_H_

#include "../base/list/list_iterator.h"
using namespace cgt::base::list;

#include "../graph_node.h"
#include "../graph_adjacency.h"


namespace cgt
{
  namespace search
  {
    /*
     * keep informations about depth-first search and breadth-first search cycles
     * used by _DepthIterator and _BreadthIterator
     */

    template<typename _TpVertex, typename _TpEdge>
      class _SearchState
      {
        private:
          typedef _GraphNode<_TpVertex, _TpEdge>             _Node;
          typedef _GraphAdjacency<_TpVertex, _TpEdge>        _Adjacency;
          typedef typename _List<_Adjacency>::const_iterator _AdjIterator;

        public:
          _SearchState (const _Node& _n) : _node (_n), _it_adj (_node.adjlist ().begin ()), _it_adj_end (_node.adjlist ().end ()) { };

        public:
          const _Node& node () { return _node; }
          const bool adj_finished () const { return (_it_adj == _it_adj_end); }
          void adj_incr () { ++_it_adj; }
          _Node* const adj_node () { return _it_adj->node (); }

        private:
          const _Node&       _node;
          _AdjIterator       _it_adj;
          const _AdjIterator _it_adj_end;
      };
  }
}

#endif
