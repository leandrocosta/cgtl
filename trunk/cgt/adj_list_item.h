#ifndef _ADJ_LIST_ITEM_H_
#define _ADJ_LIST_ITEM_H_


template<typename _TpVertice, typename _TpEdge>
class _AdjListItem : protected _ListItem<_Adjacency<_TpVertice, _TpEdge> >
{
  public:
    _AdjListItem (const _TpEdge &_e, _Vertice<_TpVertice> &_v1, _Vertice<_TpVertice> &_v2) : _ListItem<_Adjacency<_TpVertice, _TpEdge> > (_Adjacency<_TpVertice, _TpEdge> (_e, _v1, _v2)) { }

  public:
    const _Vertice<_TpVertice>& get_vertice () const { return _get_data ()._vertice; }
    _Edge<_TpVertice, _TpEdge>& get_edge () { return _get_data ()._edge; }
    _AdjListItem<_TpVertice, _TpEdge>* get_next () const { return static_cast<_AdjListItem<_TpVertice, _TpEdge> *> (_get_next ()); }

    void  set_next (_AdjListItem<_TpVertice, _TpEdge> *_n) { _set_next (_n); };
};

#endif
