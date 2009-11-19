#ifndef _PRIM_ITERATOR_H_
#define _PRIM_ITERATOR_H_

#include "prim_adjacency_heap.h"
#include "../../base/iterator/iterator_ptr.h"
#include "../../base/hash/hash.h"


namespace cgt
{
  namespace minspantree
  {
    namespace prim
    {
      template<typename _TpVertex, typename _TpEdge, template<typename> class _TpIterator = cgt::base::iterator::_TpCommon>
        class _PrimIterator : public _IteratorPtr<_GraphAdjacency<_TpVertex, _TpEdge>, _TpIterator>
        {
          private:
            typedef _PrimIterator<_TpVertex, _TpEdge, _TpIterator>  _Self;
            typedef _PrimIterator<_TpVertex, _TpEdge, _TpCommon>    _SelfCommon;

          private:
            typedef _GraphVertex<_TpVertex>             _Vertex;
            typedef _GraphEdge<_TpVertex, _TpEdge>      _Edge;

            typedef _GraphNode<_TpVertex, _TpEdge>      _Node;
            typedef cgt::base::list<_Node>        _NodeList;
            typedef typename _NodeList::iterator        _NodeIterator;

            typedef _GraphAdjacency<_TpVertex, _TpEdge> _Adjacency;
            typedef cgt::base::list<_Adjacency>   _AdjacencyList;
            typedef typename _AdjacencyList::iterator   _AdjacencyIterator;

            typedef _IteratorPtr<_Adjacency, _TpIterator>    _Base;

          private:
            typedef _PrimAdjacencyHeap<_Adjacency*>  _AdjacencyHeap;
            typedef cgt::base::hash<_Vertex*, bool> _VertexHash;

          private:
            using _Base::_ptr;

          public:
            _PrimIterator () { }
            _PrimIterator (_Node* const _ptr_n)
            {
              if (_ptr_n)
                _init (*_ptr_n);
            }
            _PrimIterator (const _NodeIterator& _it) { _init (*_it); }
            _PrimIterator (const _SelfCommon& _it) { }
            virtual ~_PrimIterator () { }

          private:
            void _init (_Node& _n);
            void _incr ();

          public:
            _Edge& operator*() const { return _ptr->edge (); }
            _Edge* operator->() const { return &(_ptr->edge ()); }
            _Self& operator++();
            const _Self operator++(int);

          private:
            _AdjacencyHeap  _adjHeap;
            _VertexHash     _vertexHash;
        };


      template<typename _TpVertex, typename _TpEdge, template<typename> class _TpIterator>
        void _PrimIterator<_TpVertex, _TpEdge, _TpIterator>::_init (_Node& _n)
        {
          _AdjacencyIterator _itEnd = _n.adjlist ().end ();
          for (_AdjacencyIterator _it = _n.adjlist ().begin (); _it != _itEnd; ++_it)
            _adjHeap.push (&(*_it));

          _Adjacency** _p = _adjHeap.pop ();
          _ptr = *_p;
          delete _p;

          _vertexHash.insert (&(_ptr->edge ().v1 ()), true);
          _vertexHash.insert (&(_ptr->edge ().v2 ()), true);

          _itEnd = _ptr->node ().adjlist ().end ();
          for (_AdjacencyIterator _it = _ptr->node ().adjlist ().begin (); _it != _itEnd; ++_it)
          {
            if (! _vertexHash [&(_it->node ().vertex ())])
              _adjHeap.push (&(*_it));
          }
        }

      template<typename _TpVertex, typename _TpEdge, template<typename> class _TpIterator>
        void _PrimIterator<_TpVertex, _TpEdge, _TpIterator>::_incr ()
        {
          _ptr = NULL;

          while (! _adjHeap.empty ())
          {
            _Adjacency** _p = _adjHeap.pop ();
            _ptr = *_p;
            delete _p;

            if (! _vertexHash [&(_ptr->edge ().v1 ())] || ! _vertexHash [&(_ptr->edge ().v2 ())])
              break;
            else
              _ptr = NULL;
          }

          if (_ptr)
          {
            _AdjacencyIterator _itEnd = _ptr->node ().adjlist ().end ();
            for (_AdjacencyIterator _it = _ptr->node ().adjlist ().begin (); _it != _itEnd; ++_it)
            {
              if (! _vertexHash [&(_it->node ().vertex ())])
                _adjHeap.push (&(*_it));
            }

            if (! _vertexHash [&(_ptr->edge ().v1 ())])
              _vertexHash.insert (&(_ptr->edge ().v1 ()), true);
            if (! _vertexHash [&(_ptr->edge ().v2 ())])
              _vertexHash.insert (&(_ptr->edge ().v2 ()), true);
          }
        }

      template<typename _TpVertex, typename _TpEdge, template<typename> class _TpIterator>
        _PrimIterator<_TpVertex, _TpEdge, _TpIterator>& _PrimIterator<_TpVertex, _TpEdge, _TpIterator>::operator++()
        {
          _incr ();
          return *this;
        }

      template<typename _TpVertex, typename _TpEdge, template<typename> class _TpIterator>
        const _PrimIterator<_TpVertex, _TpEdge, _TpIterator> _PrimIterator<_TpVertex, _TpEdge, _TpIterator>::operator++(int)
        {
          _Self _it = *this;
          _incr ();
          return _it;
        }
    }
  }
}

#endif
