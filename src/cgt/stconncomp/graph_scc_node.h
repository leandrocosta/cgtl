#ifndef _GRAPH_SCC_NODE_H_
#define _GRAPH_SCC_NODE_H_

#include "../graph_vertex.h"
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
          typedef _GraphAdjList<_TpVertex, _TpEdge> _AdjList;

        public:
          _GraphSCCNode (const _Vertex& _v) : _vertex (_v) { }

        public:
          const _Vertex& vertex () const { return _vertex; }

        private:
          const _Vertex& _vertex;
          _AdjList _adjList;
      };
  }
}

#endif
