#ifndef _DIJKSTRA_INFO_LIST_H_
#define _DIJKSTRA_INFO_LIST_H_

#include "../graph_node.h"
#include "dijkstra_info.h"
#include "../list/list.h"
using namespace cgt::list;


namespace cgt
{
  template<typename _TpVertex, typename _TpEdge>
    class _DijkstraInfoList : public _List<_DijkstraInfo<_TpVertex, _TpEdge> >
    {
      private:
        typedef _DijkstraInfoList<_TpVertex, _TpEdge>     _Self;
        typedef _List<_DijkstraInfo<_TpVertex, _TpEdge> > _Base;

      private:
        typedef _DijkstraInfo<_TpVertex, _TpEdge> _Info;
        typedef _GraphNode<_TpVertex, _TpEdge>    _Node;
        typedef _GraphEdge<_TpVertex, _TpEdge>    _Edge;
        typedef typename _Base::iterator          _Iterator;

      private:
        using _Base::begin;
        using _Base::end;
        using _Base::empty;

      private:
        static const bool _has_node (const _Info& _info, const _Node& _node) { return (_info.node ().vertex () == _node.vertex ()); }

      public:
        _Iterator get_by_node (const _Node* const _ptr_node);
        _Iterator get_closest ();
        void relax (const _Node* const _ptr_node, const _TpEdge& _distance, const _Edge& _edge, _Node* const _ptr_prev);
    };

  template<typename _TpVertex, typename _TpEdge>
    typename _DijkstraInfoList<_TpVertex, _TpEdge>::_Iterator _DijkstraInfoList<_TpVertex, _TpEdge>::get_by_node (const _Node* const _ptr_node)
    {
      return find_if (begin (), end (), _has_node, *_ptr_node);
    }

  template<typename _TpVertex, typename _TpEdge>
    typename _DijkstraInfoList<_TpVertex, _TpEdge>::_Iterator _DijkstraInfoList<_TpVertex, _TpEdge>::get_closest ()
    {
      _Iterator it_ret = begin ();

      if (! empty ())
      {
        _Iterator it = it_ret;
        _Iterator itEnd = end ();

        for (++it; it != itEnd; ++it)
        {
          if (! it->inf_distance () && *it < *it_ret)
            it_ret = it;
        }
      }

      return it_ret;
    }

  template<typename _TpVertex, typename _TpEdge>
    void _DijkstraInfoList<_TpVertex, _TpEdge>::relax (const _Node* const _ptr_node, const _TpEdge& _distance, const _Edge& _edge, _Node* const _ptr_prev)
    {
      _Iterator it = get_by_node (_ptr_node);

      if (it != end ())
      {
        _TpEdge new_distance = _distance + _edge.value ();

        if (it->inf_distance () || it->distance () > new_distance)
        {
          it->_set_distance (new_distance);
          it->_set_previous (_ptr_prev);
        }
      }
    }
}


#endif
