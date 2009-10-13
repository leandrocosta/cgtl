#ifndef _DEPTH_ITERATOR_H_
#define _DEPTH_ITERATOR_H_

#include "stack/stack.h"
using namespace cgt::stack;


namespace cgt
{
  namespace list
  {
    template<typename _TpItem>
      class _ListIterator;
  }

  template<typename _TpVertex, typename _TpEdge>
    class _Adjacency;


  /*
   * depth-first algorithm
   *
   * Is it really necessary to inherit from _ListIterator?
   *  - we can create an attribute _ptr_node, and implement operator() as 'return _ptr_node'.
   *
   * we need a pointer to the first graph node (when we get to the end of current tree, it'll be used to find the next one);
   *  - OK, now we have _it_begin and _it_end to mark the first node and the end of the node list.
   * we need a stack with the state of each iteration (used to implement a non-recursive algorithm);
   *  - We have _DepthStateStack (_Stack<_DepthState>), we need to use it in operator++;
   * we need a struct to retain informations of each node (color, discovery finish time, parent, etc.)
   *  - OK, now we have _DepthInfo and _List<_DepthInfo>.
   */

  template<typename _TpVertex, typename _TpEdge>
    class _depth_iterator : public _ListIterator<_GraphNode<_TpVertex, _TpEdge> >
    {
      private:
        typedef _ListIterator<_GraphNode<_TpVertex, _TpEdge> >      _Base;
        typedef _depth_iterator<_TpVertex, _TpEdge>                 _Self;
        typedef _GraphNode<_TpVertex, _TpEdge>                      _Node;
        typedef _ListIterator<_GraphNode<_TpVertex, _TpEdge> >      _NodeIterator;
        typedef _ListConstIterator<_Adjacency<_TpVertex, _TpEdge> > _AdjIterator;

      private:
        class _DepthState
        {
          public:
            _DepthState (const _Node *_ptr_n, const _AdjIterator &_it_a, const _AdjIterator &_it_adj_e) : _ptr_node (_ptr_n), _it_adj (_it_a), _it_adj_end (_it_adj_e) { };

          public:
            _AdjIterator& it_adj () { return _it_adj; }
            const _AdjIterator& it_adj_end () const { return _it_adj_end; }
            const _Node* ptr_node () const { return _ptr_node; }

          private:
            const _Node*        _ptr_node;
            _AdjIterator        _it_adj;
            const _AdjIterator  _it_adj_end;
        };

        class _DepthInfo
        {
          public:
            typedef enum { WHITE, GRAY, BLACK } _color_t;

          public:
            _DepthInfo (const _Node *_ptr_n, const _Node *_ptr_p) : _ptr_node (_ptr_n), _ptr_parent (_ptr_p), _color (WHITE), _discovery (0), _finish (0) { }
            _DepthInfo (const _Node *_ptr_n, const _color_t &_c) : _ptr_node (_ptr_n), _ptr_parent (NULL), _color (_c), _discovery (0), _finish (0) { }
            _DepthInfo (const _Node *_ptr_n, const _color_t &_c, const unsigned long &_d) : _ptr_node (_ptr_n), _ptr_parent (NULL), _color (_c), _discovery (_d), _finish (0) { }
            _DepthInfo (const _Node *_ptr_n, const _Node *_ptr_p, const _color_t &_c) : _ptr_node (_ptr_n), _ptr_parent (_ptr_p), _color (_c), _discovery (0), _finish (0) { }

          private:
            const _Node*  _ptr_node;
            const _Node*  _ptr_parent;
            _color_t      _color;
            unsigned long _discovery;
            unsigned long _finish;
        };

      public:
        _depth_iterator () : _it_begin (NULL), _it_end (NULL), _global_time (0) { }
        /*
        _depth_iterator (const _ListIterator<_Node> &_iterator) : _ListIterator<_Node> (_iterator), _ptr_n (_Base::operator->()), _adj_list (_ptr_n->get_adj_list ())
        {
          _reg_list.insert (_DepthReg (_ptr_n, NULL, _DepthReg::GRAY));
          _adj_iterator = _adj_list.begin ();
        }
        */
        _depth_iterator (const _NodeIterator &_it, const _NodeIterator &_it_b, const _NodeIterator &_it_e) : _Base (_it), _it_begin (_it_b), _it_end (_it_e), _global_time (0)
        {
          /*
           * paint all nodes with WHITE, and initialize parent, discovery, finish.
           * paint _it with GRAY:
           *  put in the stack:
           *    - the node pointed by _it (what is the best choice, pushd _NodeIterator, _Node& or _Node* ?);
           *    - an _AdjIterator pointing to the adjacency list's first element of the node right pushed.
           */

          _NodeIterator it = _it_begin;
          _NodeIterator itEnd = _it_end;

          for (; it != itEnd; ++it)
          {
            if (&(*it) == &(*_it))
            {
              _DepthInfoList.insert (_DepthInfo (&(*it), _DepthInfo::GRAY, +_global_time));
              _DepthStateStack.push (_DepthState (&(*it), it->adj_list ().begin (), it->adj_list ().end ()));
            }
            else
              _DepthInfoList.insert (_DepthInfo (&(*it), _DepthInfo::WHITE));
          }
        }

      public:
        _Self& operator++();

      private:
        _NodeIterator       _it_begin;
        _NodeIterator       _it_end;
        _Stack<_DepthState> _DepthStateStack;
        _List<_DepthInfo>   _DepthInfoList;

        unsigned long       _global_time;
    };


    template<typename _TpVertex, typename _TpEdge>
      _depth_iterator<_TpVertex, _TpEdge>& _depth_iterator<_TpVertex, _TpEdge>::operator++()
      {
        /*
         * while (the node on stack's top doesn't have WHITE adjacent nodes anymore):
         *  - pop from the stack.
         *
         * if there is a node on the top of the stack (and surely this node still has WHITE adjacent nodes):
         *  - paint it with GRAY:
         *    - increment the _AdjIterator on the top of the stack;
         *    - put in the stack the WHITE node right found;
         *    - put in the stack an _AdjIterator pointing to the adjacency list's first element of the node right pushed.
         *  - point this iterator (_Base::_ptr) to the node right pushed
         * else
         *  - increment the base_iterator until get a WHITE node or get the end;
         *  - if a WHITE node is found:
         *    - paint it with GRAY:
         *      - put this node in the stack;
         *      - increment the _AdjIterator on the top of the stack;
         *  - else
         *      - the end: point _ptr to end (NULL);
         */

        while (! _DepthStateStack.empty ())
        {
          _DepthState *_ptr_state  = _DepthStateStack.top ();

          if (_ptr_state->it_adj () != _ptr_state->it_adj_end ())
          {
//            _Base::_ptr = _ptr_state->it_adj ()->node ();
          }
          else
          {
            _DepthState *_ptr = _DepthStateStack.pop ();
            cout << "node already visited: " << _ptr->ptr_node ()->vertex ().value () << endl;
          }
        }
/*
        if (_adj_iterator == _adj_list.end ())
        {
          _Base::operator++();
        }
        else
        {
          _ptr_n = _adj_iterator->node ();
        }
*/

        return *this;
      }
}

#endif
