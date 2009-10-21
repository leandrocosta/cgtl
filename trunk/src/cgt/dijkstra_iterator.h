#ifndef _DIJKSTRA_ITERATOR_H_
#define _DIJKSTRA_ITERATOR_H_


namespace cgt
{
  template<typename _TpVertex, typename _TpEdge, template<typename> class _TpIterator = _TpCommon>
    class _DijkstraIterator
    {
      private:
        typedef _DijkstraIterator<_TpVertex, _TpEdge, _TpIterator>  _Self;
        typedef _DijkstraIterator<_TpVertex, _TpEdge, _TpCommon>    _SelfCommon;

      private:
        typedef _GraphNode<_TpVertex, _TpEdge>  _Node;
        typedef typename _List<_Node>::iterator _NodeIterator;

      public:
        class _DijkstraInfo
        {
          public:
            _DijkstraInfo (_Node& _n) : _node (_n), _distance (-1) { }
            _DijkstraInfo (_Node& _n, const long &_d) : _node (_n), _distance (_d) { }

          public:
            const bool operator==(const _DijkstraInfo& _other) { return (_node.vertex () == _other._node.vertex ()); }

          public:
            void _set_distance (const long &_d) { _distance = _d; }
            void _incr_distance (const long &_d) { _distance += _d; }
            const long& distance () const { return _distance; }
            _Node& node () const { return _node; }

          private:
            _Node&  _node;
            long    _distance;
        };

      public:
        _DijkstraIterator () { }
        /*
         * The constructors need to insert all nodes (except _ptr_n) in _NotVisitedInfoList with distance == -1,
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
        _DijkstraInfo* _get_info_by_node (const _Node* const _ptr_node);
        _DijkstraInfo* _get_info_by_visited_node (const _Node* const _ptr_node);
        _DijkstraInfo* _get_info_by_not_visited_node (const _Node* const _ptr_node);

      public:
        _Node& operator*() const;
        _Node* operator->() const;
        const bool operator==(const _Self &_other) const;
        const bool operator!=(const _Self &_other) const;
        _Self& operator++();

      public:
        const _DijkstraInfo* const info (const _Node* const _ptr_node) { return _get_info_by_node (_ptr_node); }
        const _DijkstraInfo* const info (const _Node& _node) { return _get_info_by_node (&_node); }

        typename _List<_DijkstraInfo>::iterator info_begin () { return _InfoList.begin (); }
        typename _List<_DijkstraInfo>::iterator info_end () { return _InfoList.end (); }

      private:
        _Node*               _ptr_node;
        _NodeIterator        _it_node;
        _NodeIterator        _it_node_end;
        _List<_DijkstraInfo> _InfoList;
        _List<_DijkstraInfo> _NotVisitedInfoList;
    };

  template<typename _TpVertex, typename _TpEdge, template<typename> class _TpIterator>
    void _DijkstraIterator<_TpVertex, _TpEdge, _TpIterator>::_init ()
    {
      /*
       * Insert all nodes (except _ptr_node) in _NotVisitedInfoList with distance == -1,
       * calculate distance for the nodes from adjacency list of _ptr_n.
       */

      _NodeIterator it;

      for (it = _it_node; it != _it_node_end; ++it)
      {
        if (&(*it) == _ptr_node)
        {
          _InfoList.insert (_DijkstraInfo (*it, 0));
        }
        else
          _NotVisitedInfoList.insert (_DijkstraInfo (*it));
      }

      const _AdjList<_TpVertex, _TpEdge> &adjList = _ptr_node->adjlist ();
      typename _AdjList<_TpVertex, _TpEdge>::const_iterator itA = adjList.begin ();
      typename _AdjList<_TpVertex, _TpEdge>::const_iterator itAEnd = adjList.end ();

      for (itA = adjList.begin (); itA != itAEnd; ++itA)
      {
        const _Node* const _ptr_n = itA->node ();
        _DijkstraInfo *_ptr_i = _get_info_by_not_visited_node (_ptr_n);

        if (_ptr_i)
          _ptr_i->_set_distance (itA->edge ().value ());
      }
    }

  template<typename _TpVertex, typename _TpEdge, template<typename> class _TpIterator>
    typename _DijkstraIterator<_TpVertex, _TpEdge, _TpIterator>::_DijkstraInfo* _DijkstraIterator<_TpVertex, _TpEdge, _TpIterator>::_get_info_by_node (const _Node* const _ptr_node)
    {
      _DijkstraInfo *_ptr = _get_info_by_visited_node (_ptr_node);

      if (! _ptr)
        _ptr = _get_info_by_not_visited_node (_ptr_node);

      return _ptr;
    }

  template<typename _TpVertex, typename _TpEdge, template<typename> class _TpIterator>
    typename _DijkstraIterator<_TpVertex, _TpEdge, _TpIterator>::_DijkstraInfo* _DijkstraIterator<_TpVertex, _TpEdge, _TpIterator>::_get_info_by_visited_node (const _Node* const _ptr_node)
    {
      _DijkstraInfo *_ptr = NULL;

      typename _List<_DijkstraInfo>::iterator it;
      typename _List<_DijkstraInfo>::iterator itEnd = _InfoList.end ();

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
    typename _DijkstraIterator<_TpVertex, _TpEdge, _TpIterator>::_DijkstraInfo* _DijkstraIterator<_TpVertex, _TpEdge, _TpIterator>::_get_info_by_not_visited_node (const _Node* const _ptr_node)
    {
      _DijkstraInfo *_ptr = NULL;

      typename _List<_DijkstraInfo>::iterator it;
      typename _List<_DijkstraInfo>::iterator itEnd = _NotVisitedInfoList.end ();

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
       * The operator++() needs to remove the node with lowest distance from _NotVisitedInfoList
       * and recalculate distances for the adjacency list of the choosed node.
       */

      _ptr_node = NULL;

      if (! _NotVisitedInfoList.empty ())
      {
        typename _List<_DijkstraInfo>::iterator it = _NotVisitedInfoList.begin ();
        typename _List<_DijkstraInfo>::iterator itEnd = _NotVisitedInfoList.end ();

        _DijkstraInfo* pInfo = &(*it);

        for (++it; it != itEnd; ++it)
        {
          if (it->distance () != -1)
          {
            if (pInfo->distance () == -1 || it->distance () < pInfo->distance ())
              pInfo = &(*it);
          }
        }

        if (pInfo->distance () != -1)
        {
          _ptr_node = &(pInfo->node ());
          _InfoList.insert (*pInfo);
          _NotVisitedInfoList.remove (*pInfo);

          const _AdjList<_TpVertex, _TpEdge> &adjList = pInfo->node ().adjlist ();
          typename _AdjList<_TpVertex, _TpEdge>::const_iterator itA = adjList.begin ();
          typename _AdjList<_TpVertex, _TpEdge>::const_iterator itAEnd = adjList.end ();

          for (itA = adjList.begin (); itA != itAEnd; ++itA)
          {
            const _Node* const _ptr_n = itA->node ();
            _DijkstraInfo *_ptr_i = _get_info_by_not_visited_node (_ptr_n);

            if (_ptr_i)
            {
              long new_distance = pInfo->distance () + itA->edge ().value ();

              if (_ptr_i->distance () == -1 || _ptr_i->distance () > new_distance)
                _ptr_i->_set_distance (new_distance);

            }
          }
        }
      }

      return *this;
    }

  template<typename _TpVertex, typename _TpEdge, template<typename> class _TpIterator>
    const bool _DijkstraIterator<_TpVertex, _TpEdge, _TpIterator>::operator==(const _Self &_other) const
    {
      return _ptr_node == _other._ptr_node;
    }

  template<typename _TpVertex, typename _TpEdge, template<typename> class _TpIterator>
    const bool _DijkstraIterator<_TpVertex, _TpEdge, _TpIterator>::operator!=(const _Self &_other) const
    {
      return !(*this == _other);
    }
}

#endif
