#ifndef _ADJACENCY_H_
#define _ADJACENCY_H_


namespace cgt
{
  template<typename _TpVertex, typename _TpEdge>
    class _GraphNode;


  template<typename _TpVertex, typename _TpEdge>
    class _Adjacency
    {
      private:
        typedef _GraphNode<_TpVertex, _TpEdge> _Node;

      public:
        _Adjacency (const _GraphEdge<_TpVertex, _TpEdge>& _e, _GraphVertex<_TpVertex> &_v, _GraphNode<_TpVertex, _TpEdge>* const _ptr_n) : _edge (_e), _vertex (_v), _ptr_node (_ptr_n)  { }

      public:
        const _GraphEdge<_TpVertex, _TpEdge>&  get_edge () const;
        const _GraphVertex<_TpVertex>& get_vertex () const;
        _Node* node () const;

      private:
        const _GraphEdge<_TpVertex, _TpEdge>&  _edge;
        _GraphVertex<_TpVertex>&               _vertex;
        _Node* const                      _ptr_node;
    };

  template<typename _TpVertex, typename _TpEdge>
    const _GraphEdge<_TpVertex, _TpEdge>& _Adjacency<_TpVertex, _TpEdge>::get_edge () const
    {
      return _edge;
    }

  template<typename _TpVertex, typename _TpEdge>
    const _GraphVertex<_TpVertex>& _Adjacency<_TpVertex, _TpEdge>::get_vertex () const
    {
      return _vertex;
    }

  template<typename _TpVertex, typename _TpEdge>
    _GraphNode<_TpVertex, _TpEdge>* _Adjacency<_TpVertex, _TpEdge>::node () const
    {
      return _ptr_node;
    }
}

#endif
