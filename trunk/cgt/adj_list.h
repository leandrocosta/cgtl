#ifndef _ADJ_LIST_H_
#define _ADJ_LIST_H_

template<typename _TpItem>
class _List;

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
    void insert (const _TpEdge &_e, _Vertice<_TpVertice> &_v1, _Vertice<_TpVertice> &_v2)
    {
      _Base::insert (_Adjacency<_TpVertice, _TpEdge> (_e, _v1, _v2));
    }
};

#endif
