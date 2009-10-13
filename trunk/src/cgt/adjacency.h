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
        _Adjacency (const _Edge<_TpVertex, _TpEdge>& _e, _Vertex<_TpVertex> &_v, const _GraphNode<_TpVertex, _TpEdge> *_ptr_n) : _edge (_e), _vertex (_v), _ptr_node (_ptr_n)  { }

      public:
        const _Edge<_TpVertex, _TpEdge>&  get_edge () const;
        const _Vertex<_TpVertex>& get_vertex () const;
        const _Node* node () const;

      private:
        const _Edge<_TpVertex, _TpEdge>& _edge;
        _Vertex<_TpVertex>&             _vertex;
        const _Node*                      _ptr_node;
    };

  template<typename _TpVertex, typename _TpEdge>
    const _Edge<_TpVertex, _TpEdge>& _Adjacency<_TpVertex, _TpEdge>::get_edge () const
    {
      return _edge;
    }

  template<typename _TpVertex, typename _TpEdge>
    const _Vertex<_TpVertex>& _Adjacency<_TpVertex, _TpEdge>::get_vertex () const
    {
      return _vertex;
    }

  template<typename _TpVertex, typename _TpEdge>
    const _GraphNode<_TpVertex, _TpEdge>* _Adjacency<_TpVertex, _TpEdge>::node () const
    {
      return _ptr_node;
    }
}

#endif
