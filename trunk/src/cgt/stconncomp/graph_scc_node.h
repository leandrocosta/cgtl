#ifndef _GRAPH_SCC_NODE_H_
#define _GRAPH_SCC_NODE_H_

#include "../graph_node.h"
#include "../graph_adjlist.h"


namespace cgt
{
  namespace stconncomp
  {
    template<typename _TpVertex, typename _TpEdge>
      class _GraphSCCNode
      {
        private:
          typedef _GraphVertex<_TpVertex>           _Vertex;
          typedef _GraphNode<_TpVertex, _TpEdge>    _Node;
          typedef _GraphEdge<_TpVertex, _TpEdge>    _Edge;
          typedef _GraphAdjList<_TpVertex, _TpEdge> _AdjList;

        public:
          _GraphSCCNode (_Node& _n) : _node (_n) { }

        public:
          void _insert (const _Edge& _e, _Node& _n) { _adjList._insert (_e, _n); }

        public:
          _Node& node () const { return _node; }
          const _Vertex& vertex () const { return _node.vertex (); }
          const _AdjList& adjlist () const { return _adjList; }

        private:
          _Node&    _node;
          _AdjList  _adjList;
      };
  }
}

#endif
