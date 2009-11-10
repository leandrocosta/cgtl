#ifndef _GRAPH_NODE_H_
#define _GRAPH_NODE_H_

#include "graph_vertex.h"
#include "graph_adjlist.h"

namespace cgt
{
  template<typename _TpVertex, typename _TpEdge>
    class _GraphNode
    {
      private:
        typedef _GraphNode<_TpVertex, _TpEdge>    _Self;
        typedef _GraphVertex<_TpVertex>           _Vertex;
        typedef _GraphAdjList<_TpVertex, _TpEdge> _AdjList;

      public:
        _GraphNode (const _TpVertex &_v) : _vertex (_v) { };

      public:
        _Vertex& vertex ()  { return _vertex; }
        const _Vertex& vertex () const  { return _vertex; }
        _AdjList&  adjlist () { return _adjList; }
        const _AdjList&  adjlist () const { return _adjList; }

      public:
        const _GraphEdge<_TpVertex, _TpEdge>* _get_edge (const _Vertex &_v) const;

      public:
        void _insert (const _GraphEdge<_TpVertex, _TpEdge>& _e, _Self& _n);

      private:
        _Vertex   _vertex;
        _AdjList  _adjList;
    };

  template<typename _TpVertex, typename _TpEdge>
    const _GraphEdge<_TpVertex, _TpEdge>* _GraphNode<_TpVertex, _TpEdge>::_get_edge (const _GraphVertex<_TpVertex> &_v) const
    {
      return _adjList._get_edge (_v);
    }

  template<typename _TpVertex, typename _TpEdge>
    void _GraphNode<_TpVertex, _TpEdge>::_insert (const _GraphEdge<_TpVertex, _TpEdge>& _e, _Self& _n)
    {
      _adjList._insert (_e, _n);
    }
}

#endif
