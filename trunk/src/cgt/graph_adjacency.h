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
        _GraphAdjacency (const _Edge& _e, const _Vertex& _v, _Node* const _ptr_n) : _edge (_e), _vertex (_v), _ptr_node (_ptr_n)  { }

      public:
        const _Edge&  edge () const;
        const _Vertex& vertex () const;
        _Node* node () const;

      private:
        const _Edge&   _edge;
        const _Vertex& _vertex;
        _Node* const   _ptr_node;
    };

  template<typename _TpVertex, typename _TpEdge>
    const _GraphEdge<_TpVertex, _TpEdge>& _GraphAdjacency<_TpVertex, _TpEdge>::edge () const
    {
      return _edge;
    }

  template<typename _TpVertex, typename _TpEdge>
    const _GraphVertex<_TpVertex>& _GraphAdjacency<_TpVertex, _TpEdge>::vertex () const
    {
      return _vertex;
    }

  template<typename _TpVertex, typename _TpEdge>
    _GraphNode<_TpVertex, _TpEdge>* _GraphAdjacency<_TpVertex, _TpEdge>::node () const
    {
      return _ptr_node;
    }
}

#endif
