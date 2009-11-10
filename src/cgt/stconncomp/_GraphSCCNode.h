#ifndef _GRAPH_SCC_NODE_H_
#define _GRAPH_SCC_NODE_H_

#include "../graph_vertex.h"
#include "../graph_adjlist.h"


namespace cgt
{
  namespace stconncomp
  {
    template<typename _TpVertex, typename _TpEdge>
      class _GraphSCNode
      {
        private:
          typedef _GraphVertex<_TpVertex>           _Vertex;
          typedef _GraphAdjList<_TpVertex, _TpEdge> _AdjList;

        private:
          _Vertex& _vertex;
          _AdjList _adjList;
      }
  }
}

#endif
