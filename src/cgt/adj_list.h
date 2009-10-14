#ifndef _ADJ_LIST_H_
#define _ADJ_LIST_H_


namespace cgt
{
  using namespace list;

  namespace list
  {
    template<typename _TpItem>
      class _List;
  }

  template<typename _TpVertex>
    class _Vertex;

  template<typename _TpVertex, typename _TpEdge>
    class _Adjacency;


  template<typename _TpVertex, typename _TpEdge>
    class _AdjList : public _List<_Adjacency<_TpVertex, _TpEdge> >
  {
    private:
      typedef _List<_Adjacency<_TpVertex, _TpEdge> > _Base;

    public:
      const _Edge<_TpVertex, _TpEdge>* _get_edge (const _Vertex<_TpVertex> &_v) const;

    public:
      void _insert (const _Edge<_TpVertex, _TpEdge>& _e, _Vertex<_TpVertex> &_v, _GraphNode<_TpVertex, _TpEdge>* const _ptr_n);
  };

  template<typename _TpVertex, typename _TpEdge>
    const _Edge<_TpVertex, _TpEdge>* _AdjList<_TpVertex, _TpEdge>::_get_edge (const _Vertex<_TpVertex> &_v) const
    {
      const _Edge<_TpVertex, _TpEdge> *_ptr_edge = NULL;

      typename _Base::const_iterator it;
      typename _Base::const_iterator itEnd = _Base::end ();

      for (it = _Base::begin (); it != itEnd; ++it)
      {
        if (it->get_vertex () == _v)
        {
          _ptr_edge = &(it->get_edge ());
          break;
        }
      }

      return _ptr_edge;
    }

  template<typename _TpVertex, typename _TpEdge>
    void _AdjList<_TpVertex, _TpEdge>::_insert (const _Edge<_TpVertex, _TpEdge>& _e, _Vertex<_TpVertex> &_v, _GraphNode<_TpVertex, _TpEdge>* const _ptr_n)
    {
      _List<_Adjacency<_TpVertex, _TpEdge> >::insert (_Adjacency<_TpVertex, _TpEdge> (_e, _v, _ptr_n));
    }
}

#endif
