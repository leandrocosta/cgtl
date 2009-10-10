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
//      void _insert (const _TpEdge &_e, _Vertice<_TpVertice> &_v1, _Vertice<_TpVertice> &_v2);
      void _insert (const _Edge<_TpVertice, _TpEdge>* _ptr_e, _Vertice<_TpVertice> &_v);
  };

  template<typename _TpVertice, typename _TpEdge>
    const _Edge<_TpVertice, _TpEdge>* _AdjList<_TpVertice, _TpEdge>::_get_edge (const _Vertice<_TpVertice> &_v) const
    {
      _Edge<_TpVertice, _TpEdge> *_ptr_edge = NULL;

      typename _Base::iterator it;
      typename _Base::iterator itEnd = _Base::end ();

      for (it = _Base::begin (); it != itEnd; ++it)
      {
        if (it->vertice () == _v)
        {
          _ptr_edge = &(*it);
          break;
        }
      }

      return _ptr_edge;
    }

  template<typename _TpVertice, typename _TpEdge>
//    void _AdjList<_TpVertice, _TpEdge>::_insert (const _TpEdge &_e, _Vertice<_TpVertice> &_v1, _Vertice<_TpVertice> &_v2)
    void _AdjList<_TpVertice, _TpEdge>::_insert (const _Edge<_TpVertice, _TpEdge>* _ptr_e, _Vertice<_TpVertice> &_v)
    {
//      _List<_Adjacency<_TpVertice, _TpEdge> >::insert (_Adjacency<_TpVertice, _TpEdge> (_e, _v1, _v2));
      _List<_Adjacency<_TpVertice, _TpEdge> >::insert (_Adjacency<_TpVertice, _TpEdge> (_ptr_e, _v));
    }
}

#endif
