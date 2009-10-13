#ifndef _VERTEX_ITERATOR_H_
#define _VERTEX_ITERATOR_H_


namespace cgt
{
  namespace list
  {
    template<typename _TpItem>
      class _ListIterator;
  }


  template<typename _TpVertex, typename _TpEdge>
    class _vertex_iterator : public _ListIterator<_GraphNode<_TpVertex, _TpEdge> >
    {
      private:
        typedef _ListIterator<_GraphNode<_TpVertex, _TpEdge> > _Base;
        typedef _vertex_iterator<_TpVertex, _TpEdge>          _Self;

      public:
        _vertex_iterator () { }
        _vertex_iterator (const _ListIterator<_GraphNode<_TpVertex, _TpEdge> > &_iterator) : _ListIterator<_GraphNode<_TpVertex, _TpEdge> > (_iterator) { }

      public:
        _Vertex<_TpVertex>& operator*() const;
    };


  template<typename _TpVertex, typename _TpEdge>
    _Vertex<_TpVertex>& _vertex_iterator<_TpVertex, _TpEdge>::operator*() const
    {
      return _Base::operator*().vertex ();
    }
}

#endif
