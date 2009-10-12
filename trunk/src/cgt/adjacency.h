#ifndef _ADJACENCY_H_
#define _ADJACENCY_H_


namespace cgt
{
  template<typename _TpVertice, typename _TpEdge>
    class _GraphNode;


  template<typename _TpVertice, typename _TpEdge>
    class _Adjacency
    {
      private:
        typedef _GraphNode<_TpVertice, _TpEdge> _Node;

      public:
        _Adjacency (const _Edge<_TpVertice, _TpEdge>& _e, _Vertice<_TpVertice> &_v, const _GraphNode<_TpVertice, _TpEdge> *_ptr_n) : _edge (_e), _vertice (_v), _ptr_node (_ptr_n)  { }

      public:
        const _Edge<_TpVertice, _TpEdge>&  get_edge () const;
        const _Vertice<_TpVertice>& get_vertice () const;
        const _Node* node () const;

      private:
        const _Edge<_TpVertice, _TpEdge>& _edge;
        _Vertice<_TpVertice>&             _vertice;
        const _Node*                      _ptr_node;
    };

  template<typename _TpVertice, typename _TpEdge>
    const _Edge<_TpVertice, _TpEdge>& _Adjacency<_TpVertice, _TpEdge>::get_edge () const
    {
      return _edge;
    }

  template<typename _TpVertice, typename _TpEdge>
    const _Vertice<_TpVertice>& _Adjacency<_TpVertice, _TpEdge>::get_vertice () const
    {
      return _vertice;
    }

  template<typename _TpVertice, typename _TpEdge>
    const _GraphNode<_TpVertice, _TpEdge>* _Adjacency<_TpVertice, _TpEdge>::node () const
    {
      return _ptr_node;
    }
}

#endif
