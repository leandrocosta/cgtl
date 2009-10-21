#ifndef _DIJKSTRA_ITERATOR_H_
#define _DIJKSTRA_ITERATOR_H_


namespace cgt
{
  template<typename, _TpVertex, typename _TpEdge, template<typename> class _TpIterator = _TpCommon>
    class _DijkstraIterator
    {
      private:
        typedef _DijkstraIterator<_TpVertex, _TpEdge, _TpIterator>  _Self;
        typedef _DijkstraIterator<_TpVertex, _TpEdge, _TpCommon>    _SelfCommon;

      private:
        class _DijkstraInfo
        {
          private:
            typedef _GraphNode<_TpVertex, _TpEdge> _Node;

          public:
            _DijkstraInfo (const _Node& _n) : _node (_n), _distance (-1) { }

          private:
            const _Node&  _node;
            long          _distance;
        };

      public:
        _DijkstraIterator () { }
        /*
         * The constructors need to insert all nodes (except _ptr_n) in _InfoList with distance == -1,
         * and after that, calculate distance for the nodes from adjacency list of _ptr_n.
         */
        _DijkstraIterator (_Node* const _ptr_n, const _NodeIterator& _it_begin, const _NodeIterator& _it_end) : _Base (_ptr_n, _it_begin, _it_end) { }
        _DijkstraIterator (const _NodeIterator& _it, const _NodeIterator& _it_begin, const _NodeIterator& _it_end) : _Base (&(*_it), _it_begin, _it_end) { }
        _DijkstraIterator (const _SelfCommon& _it) { }

      public:
        _Node& operator*() const;
        _Node* operator->() const;
        /*
         * The operator++() needs to remove the node with lowest distance from _InfoList
         * and recalculate distances for the adjacency list of the choosed node.
         */
        _Self& operator++();

      private:
        _Node*                _ptr_node;
        _List<_DijkstraInfo>  _InfoList;
    };
}

#endif
