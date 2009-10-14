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
    class _VertexIterator : public _ListIterator<_GraphNode<_TpVertex, _TpEdge> >
    {
      private:
        typedef _ListIterator<_GraphNode<_TpVertex, _TpEdge> > _Base;
        typedef _VertexIterator<_TpVertex, _TpEdge>          _Self;

      public:
        _VertexIterator () { }
        _VertexIterator (const _ListIterator<_GraphNode<_TpVertex, _TpEdge> > &_iterator) : _ListIterator<_GraphNode<_TpVertex, _TpEdge> > (_iterator) { }

      public:
        _GraphVertex<_TpVertex>& operator*() const;
    };


  template<typename _TpVertex, typename _TpEdge>
    _GraphVertex<_TpVertex>& _VertexIterator<_TpVertex, _TpEdge>::operator*() const
    {
      return _Base::operator*().vertex ();
    }
}

#endif
