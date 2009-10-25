#ifndef _DIJKSTRA_ITERATOR_H_
#define _DIJKSTRA_ITERATOR_H_

#include "dijkstra_info.h"


namespace cgt
{
  template<typename _TpVertex, typename _TpEdge, template<typename> class _TpIterator = _TpCommon>
    class _DijkstraIterator
    {
      private:
        typedef _DijkstraIterator<_TpVertex, _TpEdge, _TpIterator>  _Self;
        typedef _DijkstraIterator<_TpVertex, _TpEdge, _TpCommon>    _SelfCommon;

      private:
        typedef _DijkstraInfo<_TpVertex, _TpEdge> _Info;
        typedef _GraphNode<_TpVertex, _TpEdge>    _Node;
        typedef _GraphAdjList<_TpVertex, _TpEdge> _AdjList;
        typedef typename _List<_Node>::iterator   _NodeIterator;
        typedef typename _List<_Info>::iterator   _InfoIterator;
        typedef typename _AdjList::const_iterator _AdjListIterator;

      public:
        typedef _DijkstraInfo<_TpVertex, _TpEdge> _DijkstraInfo;

      public:
        _DijkstraIterator () { }
        /*
         * The constructors need to insert all nodes (except _ptr_n) in _NotVisitedInfoList with distance == infinite,
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
        _DijkstraIterator (const _SelfCommon& _it) : _ptr_node ( _it._ptr_node), _it_node (_it._it_node), _it_node_end (_it._it_node_end), _InfoList (_it._InfoList), _NotVisitedInfoList (_it._NotVisitedInfoList) { }

      private:
        void _init ();
        _Info* _get_info_by_node (const _Node* const _ptr_node);
        _Info* _get_info_by_visited_node (const _Node* const _ptr_node);
        _Info* _get_info_by_not_visited_node (const _Node* const _ptr_node);

      public:
        _Node& operator*() const;
        _Node* operator->() const;
        const bool operator==(const _Self& _other) const;
        const bool operator!=(const _Self& _other) const;
        _Self& operator++();

      public:
        const _Info* const info (const _Node* const _ptr_node) { return _get_info_by_node (_ptr_node); }
        const _Info* const info (const _Node& _node) { return _get_info_by_node (&_node); }

        _InfoIterator info_begin () { return _InfoList.begin (); }
        _InfoIterator info_end () { return _InfoList.end (); }

      private:
        _Node*        _ptr_node;
        _NodeIterator _it_node;
        _NodeIterator _it_node_end;
        _List<_Info>  _InfoList;
        _List<_Info>  _NotVisitedInfoList;
    };

  template<typename _TpVertex, typename _TpEdge, template<typename> class _TpIterator>
    void _DijkstraIterator<_TpVertex, _TpEdge, _TpIterator>::_init ()
    {
      /*
       * Insert all nodes (except _ptr_node) in _NotVisitedInfoList with distance == infinite,
       * calculate distance for the nodes from adjacency list of _ptr_n.
       */

      _NodeIterator it;

      for (it = _it_node; it != _it_node_end; ++it)
      {
        if (&(*it) == _ptr_node)
          _InfoList.insert (_Info (*it));
        else
          _NotVisitedInfoList.insert (_Info (*it));
      }

      const _AdjList &adjList = _ptr_node->adjlist ();
      _AdjListIterator itA = adjList.begin ();
      _AdjListIterator itAEnd = adjList.end ();

      for (itA = adjList.begin (); itA != itAEnd; ++itA)
      {
        const _Node* const _ptr_n = itA->node ();
        _Info *_ptr_i = _get_info_by_not_visited_node (_ptr_n);

        if (_ptr_i)
        {
          _ptr_i->_set_distance (itA->edge ().value ());
          _ptr_i->_set_previous (&(_InfoList.back ()->node ()));
        }
      }
    }

  template<typename _TpVertex, typename _TpEdge, template<typename> class _TpIterator>
    _DijkstraInfo<_TpVertex, _TpEdge>* _DijkstraIterator<_TpVertex, _TpEdge, _TpIterator>::_get_info_by_node (const _Node* const _ptr_node)
    {
      _Info *_ptr = _get_info_by_visited_node (_ptr_node);

      if (! _ptr)
        _ptr = _get_info_by_not_visited_node (_ptr_node);

      return _ptr;
    }

  template<typename _TpVertex, typename _TpEdge, template<typename> class _TpIterator>
    _DijkstraInfo<_TpVertex, _TpEdge>* _DijkstraIterator<_TpVertex, _TpEdge, _TpIterator>::_get_info_by_visited_node (const _Node* const _ptr_node)
    {
      _Info *_ptr = NULL;

      _InfoIterator it;
      _InfoIterator itEnd = _InfoList.end ();

        for (it = _InfoList.begin (); it != itEnd; ++it)
      {
        if (it->node ().vertex () == _ptr_node->vertex ())
        {
          _ptr = &(*it);
          break;
        }
      }

      return _ptr;
    }


  template<typename _TpVertex, typename _TpEdge, template<typename> class _TpIterator>
    _DijkstraInfo<_TpVertex, _TpEdge>* _DijkstraIterator<_TpVertex, _TpEdge, _TpIterator>::_get_info_by_not_visited_node (const _Node* const _ptr_node)
    {
      _Info *_ptr = NULL;

      _InfoIterator it;
      _InfoIterator itEnd = _NotVisitedInfoList.end ();

      for (it = _NotVisitedInfoList.begin (); it != itEnd; ++it)
      {
        if (it->node ().vertex () == _ptr_node->vertex ())
        {
          _ptr = &(*it);
          break;
        }
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
       * Remove the node with lowest distance from _NotVisitedInfoList
       * and recalculate distances for the adjacency list of the chosen node.
       */

      _ptr_node = NULL;

      if (! _NotVisitedInfoList.empty ())
      {
        _InfoIterator it    = _NotVisitedInfoList.begin ();
        _InfoIterator itEnd = _NotVisitedInfoList.end ();

        _Info* pInfo = &(*it);

        for (++it; it != itEnd; ++it)
        {
          if (! it->inf_distance ())
          {
            if (pInfo->inf_distance () || it->distance () < pInfo->distance ())
              pInfo = &(*it);
          }
        }

        if (! pInfo->inf_distance ())
        {
          _ptr_node = &(pInfo->node ());
          _InfoList.insert (*pInfo);
          _NotVisitedInfoList.remove (*pInfo);

          const _AdjList &adjList = pInfo->node ().adjlist ();
          _AdjListIterator itA = adjList.begin ();
          _AdjListIterator itAEnd = adjList.end ();

          for (itA = adjList.begin (); itA != itAEnd; ++itA)
          {
            const _Node* const _ptr_n = itA->node ();
            _Info *_ptr_i = _get_info_by_not_visited_node (_ptr_n);

            if (_ptr_i)
            {
              _TpEdge new_distance = pInfo->distance () + itA->edge ().value ();

              if (_ptr_i->inf_distance () || _ptr_i->distance () > new_distance)
              {
                _ptr_i->_set_distance (new_distance);
                _ptr_i->_set_previous (&(_InfoList.back ()->node ()));
              }
            }
          }
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
