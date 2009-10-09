#ifndef _ADJ_MATRIX_ITEM_H_
#define _ADJ_MATRIX_ITEM_H_


template<typename _TpVertice, typename _TpEdge>
class _AdjMatrixItem : protected _ListItem<_GraphNode<_TpVertice, _TpEdge> >
{
  public:
    _AdjMatrixItem (const _TpVertice &_v) : _ListItem<_GraphNode<_TpVertice, _TpEdge> > (_GraphNode<_TpVertice, _TpEdge> (_v)) { }

  public:
    _Vertice<_TpVertice>&      get_vertice () { return _get_data ()._vertice; }
    _AdjMatrixItem<_TpVertice, _TpEdge>*  get_next () const { return static_cast<_AdjMatrixItem<_TpVertice, _TpEdge> *> (_get_next ()); }

    _AdjList<_TpVertice, _TpEdge>&  get_list () { return _get_data ()._adjList; }

    _Vertice<_TpVertice>* get_vertice_ptr ()
    {
      return &_get_data ()._vertice;
    }

    /*
    _Edge<_TpVertice, _TpEdge>* get_edge (const _TpEdge &_e, const _TpVertice &_v1, const _TpVertice &_v2) const
    {
      _Edge<_TpVertice, _TpEdge> *_ptr = NULL;

      if (_get_data ()._vertice == _v1)
        _ptr = _get_data ()._adjList.get_edge (_e, _v2);

      return _ptr;
    }
    */

    void set_next (_AdjMatrixItem<_TpVertice, _TpEdge> *_n) { _set_next (_n); };

    void insert_edge (const _TpEdge &_e, _Vertice<_TpVertice> &_v1, _Vertice<_TpVertice> &_v2)
    {
      _get_data ()._adjList.insert_edge (_e, _v1, _v2);
    }
};

#endif
