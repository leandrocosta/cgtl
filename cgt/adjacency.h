#ifndef _ADJACENCY_H_
#define _ADJACENCY_H_


template<typename _TpVertice, typename _TpEdge>
class _Adjacency
{
  public:
    _Adjacency (const _TpEdge &_e, _Vertice<_TpVertice> &_v1, _Vertice<_TpVertice> &_v2) : _edge (_e, _v1, _v2), _vertice (_v2)  { }

  public:
    const _Edge<_TpVertice, _TpEdge> &  get_edge () const { return _edge; }
    const _Vertice<_TpVertice>& get_vertice () const { return _vertice; }

  private:
    _Edge<_TpVertice, _TpEdge>  _edge;
    _Vertice<_TpVertice>&       _vertice;
};

#endif
