#ifndef _VERTEX_ITERATOR_H_
#define _VERTEX_ITERATOR_H_

#include "base/list_iterator.h"


namespace cgt
{
  template<typename _TpVertex, typename _TpEdge, template<typename> class _TpIterator = _TpCommon>
    class _VertexIterator : public cgt::base::_ListIterator<_GraphNode<_TpVertex, _TpEdge>, _TpIterator>
    {
      private:
        typedef _GraphNode<_TpVertex, _TpEdge>                   _Node;
        typedef cgt::base::_ListIterator<_Node, _TpIterator>     _Base;
        typedef _VertexIterator<_TpVertex, _TpEdge, _TpCommon>   _SelfCommon;
        typedef _GraphVertex<_TpVertex>                          _Vertex;
        typedef typename _TpIterator<_Vertex>::reference         reference;

      public:
        _VertexIterator () { }
        _VertexIterator (const _Base &_iterator) : _Base (_iterator) { }
        _VertexIterator (const _SelfCommon& _it) : _Base (_it) { }

      public:
        reference operator*() const;
    };


  template<typename _TpVertex, typename _TpEdge, template<typename> class _TpIterator>
    typename _TpIterator<_GraphVertex<_TpVertex> >::reference _VertexIterator<_TpVertex, _TpEdge, _TpIterator>::operator*() const
    {
      return _Base::operator*().vertex ();
    }
}

#endif
