#ifndef _ADJACENCY_H_
#define _ADJACENCY_H_


namespace cgt
{
  template<typename _TpVertex, typename _TpEdge>
    class _GraphNode;


  template<typename _TpVertex, typename _TpEdge>
    class _GraphAdjacency
    {
      private:
        typedef _GraphNode<_TpVertex, _TpEdge> _Node;
        typedef _GraphEdge<_TpVertex, _TpEdge> _Edge;
        typedef _GraphVertex<_TpVertex>        _Vertex;

      public:
        _GraphAdjacency (const _Edge& _e, _Node& _n) : _edge (_e), _node (_n)  { }

      public:
        const _Edge&  edge () const;
        const _Vertex& vertex () const;
        _Node& node () const;

      private:
        // Reference to the edge object (stored in _GraphAdjMatrix._edge_list)
        const _Edge&   _edge;

        // Pointer to the node at the right
        _Node& _node;
    };

  template<typename _TpVertex, typename _TpEdge>
    const _GraphEdge<_TpVertex, _TpEdge>& _GraphAdjacency<_TpVertex, _TpEdge>::edge () const
    {
      return _edge;
    }

  template<typename _TpVertex, typename _TpEdge>
    const _GraphVertex<_TpVertex>& _GraphAdjacency<_TpVertex, _TpEdge>::vertex () const
    {
      return _node.vertex ();
    }

  template<typename _TpVertex, typename _TpEdge>
    _GraphNode<_TpVertex, _TpEdge>& _GraphAdjacency<_TpVertex, _TpEdge>::node () const
    {
      return _node;
    }
}

#endif
