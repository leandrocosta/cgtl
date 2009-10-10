#ifndef _ADJACENCY_H_
#define _ADJACENCY_H_


namespace cgt
{
  template<typename _TpVertice, typename _TpEdge>
    class _Adjacency
    {
      public:
//        _Adjacency (const _TpEdge &_e, _Vertice<_TpVertice> &_v1, _Vertice<_TpVertice> &_v2) : _edge (_e, _v1, _v2), _vertice (_v2)  { }
        _Adjacency (const _Edge<_TpVertice, _TpEdge>* _ptr_e, _Vertice<_TpVertice> &_v) : _ptr_edge (_ptr_e), _vertice (_v)  { }

      public:
        const _Edge<_TpVertice, _TpEdge> &  get_edge () const;
        const _Vertice<_TpVertice>& get_vertice () const;

      private:
//        _Edge<_TpVertice, _TpEdge>  _edge;
        const _Edge<_TpVertice, _TpEdge>*  _ptr_edge;
        _Vertice<_TpVertice>&       _vertice;
    };

  template<typename _TpVertice, typename _TpEdge>
    const _Edge<_TpVertice, _TpEdge>& _Adjacency<_TpVertice, _TpEdge>::get_edge () const
    {
      return *_ptr_edge;
    }

  template<typename _TpVertice, typename _TpEdge>
    const _Vertice<_TpVertice>& _Adjacency<_TpVertice, _TpEdge>::get_vertice () const
    {
      return _vertice;
    }
}

#endif
