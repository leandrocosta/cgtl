#ifndef _GRAPH_SCC_COMPONENT_H_
#define _GRAPH_SCC_COMPONENT_H_

#include "graph_scc_node.h"
#include "../base/list.h"


namespace cgt
{
  namespace stconncomp
  {
    template<typename _TpVertex, typename _TpEdge>
      class _GraphSCCComponent : public cgt::base::list<_GraphSCCNode<_TpVertex, _TpEdge> >
      {
        private:
          typedef cgt::base::list<_GraphSCCNode<_TpVertex, _TpEdge> > _Base;
          typedef typename _Base::iterator                  _Iterator;

        private:
          typedef _GraphSCCNode<_TpVertex, _TpEdge> _SCCNode;
          typedef _GraphNode<_TpVertex, _TpEdge>    _Node;
          typedef _GraphEdge<_TpVertex, _TpEdge>    _Edge;

        private:
          using _Base::back;
          using _Base::begin;
          using _Base::end;

        public:
          void insert (const _SCCNode& _n);

        public:
          _GraphSCCComponent (const _SCCNode& _n) { _Base::insert (_n); }
      };


    template<typename _TpVertex, typename _TpEdge>
      void _GraphSCCComponent<_TpVertex, _TpEdge>::insert (const _SCCNode& _n)
      {
        _Base::insert (_n);

        /*
         * We need to add adjacencies between nodes that are linked in the
         * same SCC. In order to do it, we need to visit all nodes of the
         * SCC and ask for edges linking _n and these nodes. If we find some,
         * we insert it in the SCC node at the end of the list.
         *
         * _SCCNode can have a reference to _Node, but it's impossible
         * to use references to _Adjacencies. So, we reuse only the edges.
         */

        _Edge* _ptr_edge = NULL;
        _SCCNode* _ptr_node = back ();
        _Node& _n1 = _ptr_node->node ();

        _Iterator _itEnd = end ();

        for (_Iterator _it = begin (); _it != _itEnd; ++_it)
        {
          _Node& _n2 = _it->node ();

          if ((_ptr_edge = _n1._get_edge (_n2.vertex ())))
            _ptr_node->_insert (*_ptr_edge, _n2);

          if ((_ptr_edge = _n2._get_edge (_n1.vertex ())))
            _it->_insert (*_ptr_edge, _n1);
        }
      }
  }
}

#endif
