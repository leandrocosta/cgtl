#ifndef _DIJKSTRA_ITERATOR_H_
#define _DIJKSTRA_ITERATOR_H_

//#include "dijkstra_info.h"
#include "dijkstra_info_list.h"
#include "dijkstra_info_heap.h"

namespace cgt
{
  template<typename _TpVertex, typename _TpEdge, template<typename> class _TpIterator = _TpCommon>
    class _DijkstraIterator
    {
      private:
        typedef _DijkstraIterator<_TpVertex, _TpEdge, _TpIterator>  _Self;
        typedef _DijkstraIterator<_TpVertex, _TpEdge, _TpCommon>    _SelfCommon;

      private:
        typedef _DijkstraInfo<_TpVertex, _TpEdge>     _Info;
        typedef _DijkstraInfoList<_TpVertex, _TpEdge> _InfoList;
        typedef _DijkstraInfoHeap<_TpVertex, _TpEdge> _InfoHeap;
        typedef _GraphNode<_TpVertex, _TpEdge>        _Node;
        typedef _GraphAdjList<_TpVertex, _TpEdge>     _AdjList;
        typedef typename _List<_Node>::iterator       _NodeIterator;
        typedef typename _List<_Info>::iterator       _InfoIterator;
        typedef typename _AdjList::const_iterator     _AdjListIterator;

      public:
        typedef _DijkstraInfo<_TpVertex, _TpEdge> _DijkstraInfo;

      public:
        _DijkstraIterator () { }
        /*
         * The constructors need to insert all nodes (except _ptr_n) in _notVisitedInfoList with distance == infinite,
         * and after that, calculate distance for the nodes from adjacency list of _ptr_n.
         */
        _DijkstraIterator (_Node* const _ptr_n, const _NodeIterator& _it_begin, const _NodeIterator& _it_end) : _ptr_node (_ptr_n), _it_node (_it_begin), _it_node_end (_it_end)
        {
          if (_ptr_node)
            _init ();
        }
        _DijkstraIterator (const _NodeIterator& _it, const _NodeIterator& _it_begin, const _NodeIterator& _it_end) : _ptr_node (&(*_it)), _it_node (_it_begin), _it_node_end (_it_end)
        {
          if (_ptr_node)
            _init ();
        }
        _DijkstraIterator (const _SelfCommon& _it) : _ptr_node ( _it._ptr_node), _it_node (_it._it_node), _it_node_end (_it._it_node_end), _infoList (_it._infoList), _notVisitedInfoList (_it._notVisitedInfoList) { }

      private:
        void _init ();
        const _Info* const _get_info_by_node (const _Node* const _ptr_node);

      public:
        _Node& operator*() const;
        _Node* operator->() const;
        const bool operator==(const _Self& _other) const;
        const bool operator!=(const _Self& _other) const;
        _Self& operator++();

      public:
        const _Info* const info (const _Node* const _ptr_node) { return _get_info_by_node (_ptr_node); }
        const _Info* const info (const _Node& _node) { return _get_info_by_node (&_node); }

        _InfoIterator info_begin () { return _infoList.begin (); }
        _InfoIterator info_end () { return _infoList.end (); }

      private:
        _Node*        _ptr_node;
        _NodeIterator _it_node;
        _NodeIterator _it_node_end;
        _InfoList     _infoList;
        _InfoHeap     _notVisitedInfoList;
    };

  template<typename _TpVertex, typename _TpEdge, template<typename> class _TpIterator>
    void _DijkstraIterator<_TpVertex, _TpEdge, _TpIterator>::_init ()
    {
      /*
       * Insert all nodes (except _ptr_node) in _notVisitedInfoList with distance == infinite,
       * calculate distance for the nodes from adjacency list of _ptr_n.
       */

      for (_NodeIterator it = _it_node; it != _it_node_end; ++it)
      {
        if (&(*it) == _ptr_node)
          _infoList.insert (_Info (*it));
        else
          _notVisitedInfoList.push (_Info (*it));
      }

      const _AdjList &adjList = _ptr_node->adjlist ();
      _AdjListIterator itA = adjList.begin ();
      _AdjListIterator itAEnd = adjList.end ();

      for (itA = adjList.begin (); itA != itAEnd; ++itA)
      {
        _notVisitedInfoList.relax (itA->node (), _TpEdge (), itA->edge (), &(_infoList.back ()->node ()));

        /*
        typename _InfoHeap::const_iterator it = _notVisitedInfoList.get_by_node (itA->node ());

        if (it != _notVisitedInfoList.end ())
        {
          _notVisitedInfoList.modify_by (it, _InfoHeap::_set_distance, itA->edge ().value ());
          _notVisitedInfoList.modify_by (it, _InfoHeap::_set_previous, &(_infoList.back ()->node ()));
        }
        */
      }
    }

  template<typename _TpVertex, typename _TpEdge, template<typename> class _TpIterator>
    const _DijkstraInfo<_TpVertex, _TpEdge>* const _DijkstraIterator<_TpVertex, _TpEdge, _TpIterator>::_get_info_by_node (const _Node* const _ptr_node)
    {
      const _Info* _ptr = NULL;

      typename _InfoList::const_iterator it = _infoList.get_by_node (_ptr_node);

      if (it != _infoList.end ())
        _ptr = &(*it);
      else
      {
        typename _InfoHeap::const_iterator it = _notVisitedInfoList.get_by_node (_ptr_node);

        if (it != _notVisitedInfoList.end ())
          _ptr = &(*it);
      }

      return _ptr;
    }

  template<typename _TpVertex, typename _TpEdge, template<typename> class _TpIterator>
    _GraphNode<_TpVertex, _TpEdge>& _DijkstraIterator<_TpVertex, _TpEdge, _TpIterator>::operator*() const
    {
      return *_ptr_node;
    }

  template<typename _TpVertex, typename _TpEdge, template<typename> class _TpIterator>
    _GraphNode<_TpVertex, _TpEdge>* _DijkstraIterator<_TpVertex, _TpEdge, _TpIterator>::operator->() const
    {
      return _ptr_node;
    }

  template<typename _TpVertex, typename _TpEdge, template<typename> class _TpIterator>
    _DijkstraIterator<_TpVertex, _TpEdge, _TpIterator>& _DijkstraIterator<_TpVertex, _TpEdge, _TpIterator>::operator++()
    {
      /*
       * Remove the node with lowest distance from _notVisitedInfoList
       * and recalculate distances for the adjacency list of the chosen node.
       */

      _ptr_node = NULL;

      if (! _notVisitedInfoList.empty ())
      {
        _Info* _ptr = _notVisitedInfoList.pop ();

        if (! _ptr->inf_distance ())
        {
          _ptr_node = &(_ptr->node ());
          _infoList.insert (*_ptr);

          const _AdjList &adjList = _ptr_node->adjlist ();
          _AdjListIterator itA = adjList.begin ();
          _AdjListIterator itAEnd = adjList.end ();

          for (itA = adjList.begin (); itA != itAEnd; ++itA)
            _notVisitedInfoList.relax (itA->node (), _ptr->distance (), itA->edge(), &(_infoList.back ()->node ()));
        }
      }

      return *this;
    }

  template<typename _TpVertex, typename _TpEdge, template<typename> class _TpIterator>
    const bool _DijkstraIterator<_TpVertex, _TpEdge, _TpIterator>::operator==(const _Self& _other) const
    {
      return _ptr_node == _other._ptr_node;
    }

  template<typename _TpVertex, typename _TpEdge, template<typename> class _TpIterator>
    const bool _DijkstraIterator<_TpVertex, _TpEdge, _TpIterator>::operator!=(const _Self& _other) const
    {
      return !(*this == _other);
    }
}

#endif
