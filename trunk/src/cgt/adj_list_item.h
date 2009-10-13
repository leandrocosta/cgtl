#ifndef _ADJ_LIST_ITEM_H_
#define _ADJ_LIST_ITEM_H_


template<typename _TpVertex, typename _TpEdge>
class _AdjListItem : protected _ListItem<_Adjacency<_TpVertex, _TpEdge> >
{
  public:
    _AdjListItem (const _TpEdge &_e, _Vertex<_TpVertex> &_v1, _Vertex<_TpVertex> &_v2) : _ListItem<_Adjacency<_TpVertex, _TpEdge> > (_Adjacency<_TpVertex, _TpEdge> (_e, _v1, _v2)) { }

  public:
    const _Vertex<_TpVertex>& get_vertex () const { return _get_data ()._vertex; }
    _Edge<_TpVertex, _TpEdge>& get_edge () { return _get_data ()._edge; }
    _AdjListItem<_TpVertex, _TpEdge>* get_next () const { return static_cast<_AdjListItem<_TpVertex, _TpEdge> *> (_get_next ()); }

    void  set_next (_AdjListItem<_TpVertex, _TpEdge> *_n) { _set_next (_n); };
};

#endif
