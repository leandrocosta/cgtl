#ifndef _VERTICE_ITERATOR_H_
#define _VERTICE_ITERATOR_H_


namespace cgt
{
  namespace list
  {
    template<typename _TpItem>
      class _ListIterator;
  }


  template<typename _TpVertice, typename _TpEdge>
    class _vertice_iterator : public _ListIterator<_GraphNode<_TpVertice, _TpEdge> >
    {
      private:
        typedef _ListIterator<_GraphNode<_TpVertice, _TpEdge> > _Base;
        typedef _vertice_iterator<_TpVertice, _TpEdge>          _Self;

      public:
        _vertice_iterator () { }
        _vertice_iterator (const _ListIterator<_GraphNode<_TpVertice, _TpEdge> > &_iterator) : _ListIterator<_GraphNode<_TpVertice, _TpEdge> > (_iterator) { }

      public:
        _Vertice<_TpVertice>& operator*() const;
    };


  template<typename _TpVertice, typename _TpEdge>
    _Vertice<_TpVertice>& _vertice_iterator<_TpVertice, _TpEdge>::operator*() const
    {
      return _Base::operator*().vertice ();
    }
}

#endif
