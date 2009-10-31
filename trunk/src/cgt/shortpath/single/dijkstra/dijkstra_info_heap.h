#ifndef _DIJKSTRA_INFO_HEAP_H_
#define _DIJKSTRA_INFO_HEAP_H_

#include "../../../graph_node.h"
#include "dijkstra_info.h"
#include "../../../base/heap/heap.h"
using namespace cgt::base::heap;


namespace cgt
{
  namespace shortpath
  {
    namespace single
    {
      namespace dijkstra
      {
        template<typename _TpVertex, typename _TpEdge>
          class _DijkstraInfoHeap : public _Heap<_DijkstraInfo<_TpVertex, _TpEdge> >
        {
          private:
            typedef _DijkstraInfoHeap<_TpVertex, _TpEdge>     _Self;
            typedef _Heap<_DijkstraInfo<_TpVertex, _TpEdge> > _Base;

          private:
            typedef _DijkstraInfo<_TpVertex, _TpEdge> _Info;
            typedef _GraphNode<_TpVertex, _TpEdge>    _Node;
            typedef _GraphEdge<_TpVertex, _TpEdge>    _Edge;
            typedef typename _Base::const_iterator    _ConstIterator;

          private:
            using _Base::begin;
            using _Base::end;
            using _Base::empty;
            using _Base::modify_by;

          public:
            static void _set_previous (_Info& _info, const _Node* const _previous) { _info._set_previous (_previous); }
            static void _set_distance (_Info& _info, const _TpEdge& _distance) { _info._set_distance (_distance); }

          private:
            static const bool _has_node (const _Info& _info, const _Node& _node) { return (_info.node ().vertex () == _node.vertex ()); }

          public:
            _ConstIterator get_by_node (const _Node* const _ptr_node);
            _ConstIterator get_closest ();
            void relax (const _Node* const _ptr_node, const _TpEdge& _distance, const _Edge& _edge, _Node* const _ptr_prev);
        };

        template<typename _TpVertex, typename _TpEdge>
          typename _DijkstraInfoHeap<_TpVertex, _TpEdge>::_ConstIterator _DijkstraInfoHeap<_TpVertex, _TpEdge>::get_by_node (const _Node* const _ptr_node)
          {
            return find_if (begin (), end (), _has_node, *_ptr_node);
          }

        template<typename _TpVertex, typename _TpEdge>
          typename _DijkstraInfoHeap<_TpVertex, _TpEdge>::_ConstIterator _DijkstraInfoHeap<_TpVertex, _TpEdge>::get_closest ()
          {
            return begin ();
          }

        template<typename _TpVertex, typename _TpEdge>
          void _DijkstraInfoHeap<_TpVertex, _TpEdge>::relax (const _Node* const _ptr_node, const _TpEdge& _distance, const _Edge& _edge, _Node* const _ptr_prev)
          {
            _ConstIterator it = get_by_node (_ptr_node);

            if (it != end ())
            {
              _TpEdge _new_distance = _distance + _edge.value ();

              if (it->inf_distance () || it->distance () > _new_distance)
              {
                modify_by (it, _set_distance, _new_distance);
                modify_by (it, _set_previous, _ptr_prev);
              }
            }
          }
      }
    }
  }
}


#endif
