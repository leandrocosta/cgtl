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
        _AdjList&  iadjlist () { return _invAdjList; }
        const _AdjList&  iadjlist () const { return _invAdjList; }
        _TpVertex& value () { return _vertex.value (); }
        const _TpVertex& value () const { return _vertex.value (); }

      public:
        _GraphEdge<_TpVertex, _TpEdge>* _get_edge (const _Vertex &_v) const;

      public:
        void _insert (_GraphEdge<_TpVertex, _TpEdge>& _e, _Self& _n);
        void _insert_inverse (_GraphEdge<_TpVertex, _TpEdge>& _e, _Self& _n);
        void _invert_edges ();

      private:
        _Vertex   _vertex;
        _AdjList  _adjList;

        /*
         * This is a list of inverted edges: if a node n1 has an
         * inverted edge pointing to n2, it means n2 has an edge
         * pointing to n1. This way we can invert a graph in O(V),
         * just swaping the two lists: _adjList and _invAdjList.
         */

        _AdjList  _invAdjList;
    };

  template<typename _TpVertex, typename _TpEdge>
    _GraphEdge<_TpVertex, _TpEdge>* _GraphNode<_TpVertex, _TpEdge>::_get_edge (const _GraphVertex<_TpVertex> &_v) const
    {
      return _adjList._get_edge (_v);
    }

  template<typename _TpVertex, typename _TpEdge>
    void _GraphNode<_TpVertex, _TpEdge>::_insert (_GraphEdge<_TpVertex, _TpEdge>& _e, _Self& _n)
    {
      _adjList._insert (_e, _n);
      _n._insert_inverse (_e, *this);
    }

  template<typename _TpVertex, typename _TpEdge>
    void _GraphNode<_TpVertex, _TpEdge>::_insert_inverse (_GraphEdge<_TpVertex, _TpEdge>& _e, _Self& _n)
    {
      _invAdjList._insert (_e, _n);
    }

  /*
   * time complexity: O(1)
   */
  template<typename _TpVertex, typename _TpEdge>
    void _GraphNode<_TpVertex, _TpEdge>::_invert_edges ()
    {
      _AdjList::swap (_adjList, _invAdjList);
    }
}

#endif
