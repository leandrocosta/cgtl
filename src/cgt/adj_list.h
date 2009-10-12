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

  template<typename _TpVertice>
    class _Vertice;

  template<typename _TpVertice, typename _TpEdge>
    class _Adjacency;


  template<typename _TpVertice, typename _TpEdge>
    class _AdjList : public _List<_Adjacency<_TpVertice, _TpEdge> >
  {
    private:
      typedef _List<_Adjacency<_TpVertice, _TpEdge> > _Base;

    public:
      const _Edge<_TpVertice, _TpEdge>* _get_edge (const _Vertice<_TpVertice> &_v) const;

    public:
      void _insert (const _Edge<_TpVertice, _TpEdge>& _e, _Vertice<_TpVertice> &_v, const _GraphNode<_TpVertice, _TpEdge> *_ptr_n);
  };

  template<typename _TpVertice, typename _TpEdge>
    const _Edge<_TpVertice, _TpEdge>* _AdjList<_TpVertice, _TpEdge>::_get_edge (const _Vertice<_TpVertice> &_v) const
    {
      const _Edge<_TpVertice, _TpEdge> *_ptr_edge = NULL;

      typename _Base::const_iterator it;
      typename _Base::const_iterator itEnd = _Base::end ();

      for (it = _Base::begin (); it != itEnd; ++it)
      {
        if (it->get_vertice () == _v)
        {
          _ptr_edge = &(it->get_edge ());
          break;
        }
      }

      return _ptr_edge;
    }

  template<typename _TpVertice, typename _TpEdge>
    void _AdjList<_TpVertice, _TpEdge>::_insert (const _Edge<_TpVertice, _TpEdge>& _e, _Vertice<_TpVertice> &_v, const _GraphNode<_TpVertice, _TpEdge> *_ptr_n)
    {
      _List<_Adjacency<_TpVertice, _TpEdge> >::insert (_Adjacency<_TpVertice, _TpEdge> (_e, _v, _ptr_n));
    }
}

#endif
