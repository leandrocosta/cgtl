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
        typedef typename _Base::iterator          _InfoIterator;

      private:
        using _Base::begin;
        using _Base::end;
        using _Base::empty;

      public:
        _Info* get_by_node (const _Node* const _ptr_node);
        _Info* get_closest ();
        void relax (const _Node* const _ptr_node, const _TpEdge& _distance, const _Edge& _edge, _Node* const _ptr_prev);
    };

  template<typename _TpVertex, typename _TpEdge>
    _DijkstraInfo<_TpVertex, _TpEdge>* _DijkstraInfoList<_TpVertex, _TpEdge>::get_by_node (const _Node* const _ptr_node)
    {
      _Info* _ptr = NULL;

      _InfoIterator it;
      _InfoIterator itEnd = end ();

      for (it = begin (); it != itEnd; ++it)
      {
        if (it->node ().vertex () == _ptr_node->vertex ())
        {
          _ptr = &(*it);
          break;
        }
      }

      return _ptr;
    }

  template<typename _TpVertex, typename _TpEdge>
    _DijkstraInfo<_TpVertex, _TpEdge>* _DijkstraInfoList<_TpVertex, _TpEdge>::get_closest ()
    {
      _Info* _ptr = NULL;

      _InfoIterator it    = begin ();
      _InfoIterator itEnd = end ();

      if (! empty ())
      {
        _ptr = &(*it);

        for (++it; it != itEnd; ++it)
        {
          if (! it->inf_distance ())
          {
            if (*it < *_ptr)
              _ptr = &(*it);
          }
        }
      }

      return _ptr;
    }

  template<typename _TpVertex, typename _TpEdge>
    void _DijkstraInfoList<_TpVertex, _TpEdge>::relax (const _Node* const _ptr_node, const _TpEdge& _distance, const _Edge& _edge, _Node* const _ptr_prev)
    {
      _Info *_ptr_i = get_by_node (_ptr_node);

      if (_ptr_i)
      {
        _TpEdge new_distance = _distance + _edge.value ();

        if (_ptr_i->inf_distance () || _ptr_i->distance () > new_distance)
        {
          _ptr_i->_set_distance (new_distance);
          _ptr_i->_set_previous (_ptr_prev);
        }
      }
    }
}


#endif
