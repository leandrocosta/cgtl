#ifndef _EDGE_ITERATOR_H_
#define _EDGE_ITERATOR_H_


namespace cgt
{
  template<typename _TpVertice, typename _TpEdge>
    class _AdjMatrix;


  template<typename _TpVertice, typename _TpEdge>
    class _edge_iterator
    {
/*
      public:
        _edge_iterator () : _ptr (NULL) { }
        _edge_iterator (_AdjMatrixItem<_TpVertice, _TpEdge> *_p_adj) : _ptr_adj (_p_adj)
      {
        _ptr = (_ptr_adj ? _ptr_adj->get_list ().get_head ():NULL);
      }

      public:
        _Edge<_TpVertice, _TpEdge>& operator*();
        _edge_iterator<_TpVertice, _TpEdge>& operator++();
        const bool operator!=(_edge_iterator<_TpVertice, _TpEdge> &_other) const;

      private:
        _AdjMatrixItem<_TpVertice, _TpEdge>*  _ptr_adj;
        _AdjListItem<_TpVertice, _TpEdge>*    _ptr;
*/
      private:
//        _AdjMatrix<_TpVertice, _TpEdge>::iterator _it_adj_matrix;
    };

  /*
     template<typename _TpVertice, typename _TpEdge>
     _Edge<_TpVertice, _TpEdge>& _edge_iterator<_TpVertice, _TpEdge>::operator*()
     {
     return _ptr->get_edge ();
     }

     template<typename _TpVertice, typename _TpEdge>
     _edge_iterator<_TpVertice, _TpEdge>& _edge_iterator<_TpVertice, _TpEdge>::operator++()
     {
     assert (_ptr != NULL);
     _ptr = _ptr->get_next ();

     if (! _ptr)
     {
     assert (_ptr_adj != NULL);
     _ptr_adj = _ptr_adj->get_next ();
     _ptr = _ptr_adj->get_list ().get_head ();
     }

     return *this;
     }

     template<typename _TpVertice, typename _TpEdge>
     const bool _edge_iterator<_TpVertice, _TpEdge>::operator!=(_edge_iterator<_TpVertice, _TpEdge> &_other) const
     {
     return _ptr != _other._ptr;
     }
   */
}

#endif
