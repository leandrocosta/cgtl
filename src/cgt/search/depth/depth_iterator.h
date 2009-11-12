#ifndef _DEPTH_ITERATOR_H_
#define _DEPTH_ITERATOR_H_

#include "../search_iterator.h"
using namespace cgt::search;

#include "../../base/stack/stack.h"
using namespace cgt::base::stack;


namespace cgt
{
  namespace search
  {
    namespace depth
    {
      /*
       * depth-first search algorithm
       *  - _it_node: iterator pointing to the begining of the node list;
       *  - _it_node_end: iterator pointing to the end of the node list.
       *
       * initialize:
       *  - paint the first node with GRAY;
       *  - put it on the stack;
       *  - turn it the current node;
       *  - paint all the others with WHITE.
       *
       * operator++:
       *  - visit the adjacency list of the stack's top node:
       *    - if a WHITE node is found:
       *      - paint it with GRAY, put it on the stack and turn it the current node.
       *    - if there is no more WHITE nodes:
       *      - pop the stack's top node, paint it with BLACK;
       *      - continue visiting the adjacency list of the new stack's top node
       *  - if the stack is empty:
       *    - use _it_node to find the next WHITE node.
       *    - if a WHITE node is found:
       *      - paint it with GRAY, put it on the stack and turn it the current node.
       *    - if no more WIHTE nodes are found:
       *      - point the current node to NULL.
       */

      template<typename _TpVertex, typename _TpEdge, template<typename> class _TpIterator = _TpCommon>
        class _DepthIterator : public _SearchIterator<_TpVertex, _TpEdge, _Stack, _TpIterator>
      {
        public:
          typedef _SearchInfo<_TpVertex, _TpEdge>   _DepthInfo;
          typedef _SearchState<_TpVertex, _TpEdge>  _DepthState;

        private:
          typedef _DepthIterator<_TpVertex, _TpEdge, _TpIterator> _Self;
          typedef _DepthIterator<_TpVertex, _TpEdge, _TpCommon>   _SelfCommon;
          typedef _GraphNode<_TpVertex, _TpEdge>                  _Node;
          typedef typename _List<_Node>::iterator                 _NodeIterator;

        private:
          typedef _SearchIterator<_TpVertex, _TpEdge, _Stack, _TpIterator> _Base;

        private:
          using _Base::_ptr_node;
          using _Base::_it_node;
          using _Base::_it_node_end;
          using _Base::_InfoList;
          using _Base::_StateContainer;
          using _Base::_global_time;

        public:
          _DepthIterator () { }
          _DepthIterator (_Node* const _ptr_n, const _NodeIterator& _it_begin, const _NodeIterator& _it_end) : _Base (_ptr_n, _it_begin, _it_end) { }
          _DepthIterator (const _NodeIterator& _it, const _NodeIterator& _it_begin, const _NodeIterator& _it_end) : _Base (&(*_it), _it_begin, _it_end) { }
          _DepthIterator (const _SelfCommon& _it) { }

        public:
          _Self& operator++();

        public:
          const _DepthInfo* const info (const _Node* const _ptr_node) { return _get_depth_info_by_node (_ptr_node); }
          const _DepthInfo* const info (const _Node& _node) { return _get_depth_info_by_node (_node); }

          typename _List<_DepthInfo>::iterator info_begin () { return _InfoList.begin (); }
          typename _List<_DepthInfo>::iterator info_end () { return _InfoList.end (); }
      };

      template<typename _TpVertex, typename _TpEdge, template<typename> class _TpIterator>
        _DepthIterator<_TpVertex, _TpEdge, _TpIterator>& _DepthIterator<_TpVertex, _TpEdge, _TpIterator>::operator++()
        {
          _NodeIterator _it = _it_node;
          while (_it != _it_node_end)
          {
            cout << "operator++() - node color is white: " << (_has_color (*_it, _DepthInfo::WHITE) ? "true":"false") << endl;
            ++_it;
          }
          /*
           * visit the adjacency list of the stack's top node:
           *  - if a WHITE node is found:
           *    - paint it with GRAY, put it on the stack and turn it the current node.
           *  - if there is no more WHITE nodes:
           *    - pop the stack's top node, paint it with BLACK;
           *    - continue visiting the adjacency list of the new stack's top node
           * if the stack is empty:
           *  - use _it_node to find the next WHITE node.
           *  - if a WHITE node is found:
           *    - paint it with GRAY, put it on the stack and turn it the current node.
           *  - if no more WIHTE nodes are found:
           *    - point the current node to NULL.
           */

          _ptr_node = NULL;

          while (! _StateContainer.empty ())
          {
            cout << "container not empty" << endl;
            _DepthState *_ptr_state  = _StateContainer.top ();

            while (! _ptr_state->adj_finished ())
            {
              cout << "ajdacency yes" << endl;
              if (_has_color (_ptr_state->_adj_node (), _DepthInfo::WHITE))
              {
                _ptr_node = &(_ptr_state->_adj_node ());
                _ptr_state->adj_incr ();
                _StateContainer.push (_DepthState (*_ptr_node));
                _discover_node (*_ptr_node, &(_ptr_state->node ()), ++_global_time);
                break;
              }
              else
                _ptr_state->adj_incr ();
            }

            if (! _ptr_node)
            {
              cout << "finish node" << endl;
              _DepthState *_ptr = _StateContainer.pop ();
              _finish_node (_ptr->node (), ++_global_time);
              delete _ptr;
            }
            else
              break;
          }

          if (! _ptr_node)
          {
            cout << "trying another start" << endl;
            while (_it_node != _it_node_end && ! _has_color (*_it_node, _DepthInfo::WHITE))
            {
              if (_it_node == _it_node_end)
                cout << "the end" << endl;
              else
                cout << "color not WHITE" << endl;

              ++_it_node;
            }

            if (_it_node != _it_node_end)
            {
              cout << "another start yes" << endl;
              _ptr_node = &(*_it_node);
              _StateContainer.push (_DepthState (*_it_node));
              _discover_node (*_it_node, NULL, ++_global_time);
            }
          }

          return *this;
        }
    }
  }
}

#endif
