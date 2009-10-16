#ifndef _VERTEX_ITERATOR_H_
#define _VERTEX_ITERATOR_H_

#include "list/list_iterator.h"
using namespace cgt::list;


namespace cgt
{
  template<typename _TpVertex, typename _TpEdge, template<typename> class _TpIterator = _TpCommon>
    class _VertexIterator : public _ListIterator<_GraphNode<_TpVertex, _TpEdge>, _TpIterator>
    {
      private:
        typedef _GraphNode<_TpVertex, _TpEdge>                   _Node;
        typedef _ListIterator<_Node, _TpIterator>                _Base;
        typedef _VertexIterator<_TpVertex, _TpEdge, _TpIterator> _Self;

      public:
        _VertexIterator () { }
        _VertexIterator (const _Base &_iterator) : _Base (_iterator) { }

      public:
        _GraphVertex<_TpVertex>& operator*() const;
    };


  template<typename _TpVertex, typename _TpEdge, template<typename> class _TpIterator>
    _GraphVertex<_TpVertex>& _VertexIterator<_TpVertex, _TpEdge, _TpIterator>::operator*() const
    {
      return _Base::operator*().vertex ();
    }
}

#endif
