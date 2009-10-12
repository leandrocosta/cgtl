#ifndef _EDGE_ITERATOR_H_
#define _EDGE_ITERATOR_H_


namespace cgt
{
  namespace list
  {
    template<typename _TpItem>
      class _ListIterator;
  }

//  template<typename _TpVertice, typename _TpEdge, typename _TpGraphType>
//    class _AdjMatrix;


  template<typename _TpVertice, typename _TpEdge>
    class _edge_iterator : public _ListIterator<_Edge<_TpVertice, _TpEdge> >
    {
      private:
        typedef _ListIterator<_Edge<_TpVertice, _TpEdge> > _Base;
        typedef _edge_iterator<_TpVertice, _TpEdge>        _Self;

      public:
        _edge_iterator () { }
        _edge_iterator (const _ListIterator<_Edge<_TpVertice, _TpEdge> > &_iterator) : _ListIterator<_Edge<_TpVertice, _TpEdge> > (_iterator) { }

      public:
        _Edge<_TpVertice, _TpEdge>& operator*() const;
        _Edge<_TpVertice, _TpEdge>* operator->() const;
/*
        _edge_iterator<_TpVertice, _TpEdge>& operator++();
        const bool operator!=(_edge_iterator<_TpVertice, _TpEdge> &_other) const;

      private:
        _AdjMatrixItem<_TpVertice, _TpEdge>*  _ptr_adj;
        _AdjListItem<_TpVertice, _TpEdge>*    _ptr;
*/
      private:
//        _AdjMatrix<_TpVertice, _TpEdge>::iterator _it_adj_matrix;
    };

     template<typename _TpVertice, typename _TpEdge>
     _Edge<_TpVertice, _TpEdge>& _edge_iterator<_TpVertice, _TpEdge>::operator*() const
     {
       return _Base::operator*().value ();
     }

//     template<typename _TpVertice, typename _TpEdge>
//     _Edge<_TpVertice, _TpEdge>* _edge_iterator<_TpVertice, _TpEdge>::operator->() const
//     {
//       return &(operator*());
//     }

  /*
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
