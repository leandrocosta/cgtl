#ifndef _ADJ_MATRIX_ITEM_H_
#define _ADJ_MATRIX_ITEM_H_


template<typename _TpVertex, typename _TpEdge>
class _AdjMatrixItem : protected _ListItem<_GraphNode<_TpVertex, _TpEdge> >
{
  public:
    _AdjMatrixItem (const _TpVertex &_v) : _ListItem<_GraphNode<_TpVertex, _TpEdge> > (_GraphNode<_TpVertex, _TpEdge> (_v)) { }

  public:
    _GraphVertex<_TpVertex>&      get_vertex () { return _get_data ()._vertex; }
    _AdjMatrixItem<_TpVertex, _TpEdge>*  get_next () const { return static_cast<_AdjMatrixItem<_TpVertex, _TpEdge> *> (_get_next ()); }

    _AdjList<_TpVertex, _TpEdge>&  get_list () { return _get_data ()._adjList; }

    _GraphVertex<_TpVertex>* get_vertex_ptr ()
    {
      return &_get_data ()._vertex;
    }

    /*
    _GraphEdge<_TpVertex, _TpEdge>* get_edge (const _TpEdge &_e, const _TpVertex &_v1, const _TpVertex &_v2) const
    {
      _GraphEdge<_TpVertex, _TpEdge> *_ptr = NULL;

      if (_get_data ()._vertex == _v1)
        _ptr = _get_data ()._adjList.get_edge (_e, _v2);

      return _ptr;
    }
    */

    void set_next (_AdjMatrixItem<_TpVertex, _TpEdge> *_n) { _set_next (_n); };

    void insert_edge (const _TpEdge &_e, _GraphVertex<_TpVertex> &_v1, _GraphVertex<_TpVertex> &_v2)
    {
      _get_data ()._adjList.insert_edge (_e, _v1, _v2);
    }
};

#endif
