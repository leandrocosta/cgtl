#ifndef _GRAPH_NODE_H_
#define _GRAPH_NODE_H_

namespace cgt
{
  template<typename _TpVertex>
    class _GraphVertex;

  template<typename _TpVertex, typename _TpEdge>
    class _AdjList;


  template<typename _TpVertex, typename _TpEdge>
    class _GraphNode
    {
      private:
        typedef _GraphNode<_TpVertex, _TpEdge> _Self;

      public:
        _GraphNode (const _TpVertex &_v) : _vertex (_v) { };

      public:
        _GraphVertex<_TpVertex>&           vertex ()  { return _vertex; }
        const _GraphVertex<_TpVertex>&     vertex () const  { return _vertex; }
        _AdjList<_TpVertex, _TpEdge>&  adj_list () { return _adjList; }
        const _AdjList<_TpVertex, _TpEdge>&  adj_list () const { return _adjList; }

      public:
        const _GraphEdge<_TpVertex, _TpEdge>* _get_edge (const _GraphVertex<_TpVertex> &_v) const;

      public:
        void _insert (const _GraphEdge<_TpVertex, _TpEdge>& _e, _GraphVertex<_TpVertex> &_v, _Self* const _ptr_n);

      private:
        _GraphVertex<_TpVertex>            _vertex;
        _AdjList<_TpVertex, _TpEdge>  _adjList;
    };

  template<typename _TpVertex, typename _TpEdge>
    const _GraphEdge<_TpVertex, _TpEdge>* _GraphNode<_TpVertex, _TpEdge>::_get_edge (const _GraphVertex<_TpVertex> &_v) const
    {
      return _adjList._get_edge (_v);
    }

  template<typename _TpVertex, typename _TpEdge>
    void _GraphNode<_TpVertex, _TpEdge>::_insert (const _GraphEdge<_TpVertex, _TpEdge>& _e, _GraphVertex<_TpVertex> &_v, _Self* const _ptr_n)
    {
      _adjList._insert (_e, _v, _ptr_n);
    }
}

#endif
