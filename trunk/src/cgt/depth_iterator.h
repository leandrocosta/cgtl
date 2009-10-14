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

  template<typename _TpVertex, typename _TpEdge>
    class _DepthIterator
    {
      private:
        typedef _DepthIterator<_TpVertex, _TpEdge>                  _Self;
        typedef _GraphNode<_TpVertex, _TpEdge>                      _Node;
        typedef _ListIterator<_GraphNode<_TpVertex, _TpEdge> >      _NodeIterator;
        typedef _ListConstIterator<_Adjacency<_TpVertex, _TpEdge> > _AdjIterator;

      private:

        /*
         * keep informations about each visited node like
         * color, parent, discovery time, finish time, etc.
         */

        class _DepthInfo
        {
          public:
            typedef enum { WHITE, GRAY, BLACK } _color_t;

          public:
            _DepthInfo (const _Node *_ptr_n) : _ptr_node (_ptr_n), _ptr_parent (NULL), _color (WHITE), _discovery (0), _finish (0) { }
            _DepthInfo (const _Node *_ptr_n, const _color_t &_c, const unsigned long &_d) : _ptr_node (_ptr_n), _ptr_parent (NULL), _color (_c), _discovery (_d), _finish (0) { }

          public:
            const _Node*  _ptr_node;
            const _Node*  _ptr_parent;
            _color_t      _color;
            unsigned long _discovery;
            unsigned long _finish;
        };

      private:
        /*
         * keep informations about the algorithm's cycles
         * stored in a stack, one object for each tree's level
         */

        class _DepthState
        {
          public:
            _DepthState (const _Node* const _ptr_n, const _AdjIterator &_it_a, const _AdjIterator &_it_adj_e) : _ptr_node (_ptr_n), _it_adj (_it_a), _it_adj_end (_it_adj_e) { };

          public:
            const _Node* const  _ptr_node;
            _AdjIterator        _it_adj;
            const _AdjIterator  _it_adj_end;
        };
        
      public:
        _DepthIterator () : _ptr_node (NULL), _it_node (NULL), _it_node_end (NULL), _global_time (0) { }
        _DepthIterator (_Node* const _ptr_n, const _NodeIterator& _it_begin, const _NodeIterator& _it_end) : _ptr_node (_ptr_n), _it_node (_it_begin), _it_node_end (_it_end), _global_time (0)
        {
          _init ();
        }

      private:
        void _init ();
        void _update_depth_info (const _Node* _ptr_node, const _Node *_ptr_parent, const typename _DepthInfo::_color_t &_color);
        void _update_depth_info (const _Node* _ptr_node, const typename _DepthInfo::_color_t &_color);
        const bool _has_color (const _Node* _ptr_node, const typename _DepthInfo::_color_t &_color) const;

      public:
        _Node& operator*() const;
        _Node* operator->() const;
        _Self& operator++();
        const bool operator==(const _Self &_other) const;
        const bool operator!=(const _Self &_other) const;

      private:
        _Node*              _ptr_node;
        _NodeIterator       _it_node;
        _NodeIterator       _it_node_end;
        _Stack<_DepthState> _DepthStateStack;
        _List<_DepthInfo>   _DepthInfoList;

        unsigned long       _global_time;
    };


  template<typename _TpVertex, typename _TpEdge>
    void _DepthIterator<_TpVertex, _TpEdge>::_init ()
    {

      /*
       * paint the first node (_ptr_node) with GRAY;
       * put it on the stack;
       * turn it the current node (actualy, it already is the current node);
       * paint all the others with WHITE.
       */

      _NodeIterator it;
      _NodeIterator itEnd = _it_node_end;

      for (it = _it_node; it != itEnd; ++it)
      {
        if (&(*it) == _ptr_node)
        {
          _DepthInfoList.insert (_DepthInfo (&(*it), _DepthInfo::GRAY, ++_global_time));
          _DepthStateStack.push (_DepthState (&(*it), it->adj_list ().begin (), it->adj_list ().end ()));
        }
        else
          _DepthInfoList.insert (_DepthInfo (&(*it)));
      }
    }

  template<typename _TpVertex, typename _TpEdge>
    void _DepthIterator<_TpVertex, _TpEdge>::_update_depth_info (const _Node* _ptr_node, const _Node *_ptr_parent, const typename _DepthInfo::_color_t &_color)
    {
      _ListIterator<_DepthInfo> it;
      _ListIterator<_DepthInfo> itEnd = _DepthInfoList.end ();

      for (it = _DepthInfoList.begin (); it != itEnd; ++it)
      {
        if (it->_ptr_node == _ptr_node)
        {
          it->_ptr_parent = _ptr_parent;
          it->_color      = _color;
          break;
        }
      }
    }

  template<typename _TpVertex, typename _TpEdge>
    void _DepthIterator<_TpVertex, _TpEdge>::_update_depth_info (const _Node* _ptr_node, const typename _DepthInfo::_color_t &_color)
    {
      _ListIterator<_DepthInfo> it;
      _ListIterator<_DepthInfo> itEnd = _DepthInfoList.end ();

      for (it = _DepthInfoList.begin (); it != itEnd; ++it)
      {
        if (it->_ptr_node == _ptr_node)
        {
          it->_color = _color;
          break;
        }
      }
    }

  template<typename _TpVertex, typename _TpEdge>
    const bool _DepthIterator<_TpVertex, _TpEdge>::_has_color (const _Node* _ptr_node, const typename _DepthInfo::_color_t &_color) const
    {
      bool bRet = false;

      _ListConstIterator<_DepthInfo> it;
      _ListConstIterator<_DepthInfo> itEnd = _DepthInfoList.end ();

      for (it = _DepthInfoList.begin (); it != itEnd; ++it)
      {
        if (it->_ptr_node == _ptr_node)
        {
          bRet = (it->_color == _color);
          break;
        }
      }

      return bRet;
    }

  template<typename _TpVertex, typename _TpEdge>
    _GraphNode<_TpVertex, _TpEdge>& _DepthIterator<_TpVertex, _TpEdge>::operator*() const
    {
      return *_ptr_node;
    }

  template<typename _TpVertex, typename _TpEdge>
    _GraphNode<_TpVertex, _TpEdge>* _DepthIterator<_TpVertex, _TpEdge>::operator->() const
    {
      return _ptr_node;
    }

  template<typename _TpVertex, typename _TpEdge>
    _DepthIterator<_TpVertex, _TpEdge>& _DepthIterator<_TpVertex, _TpEdge>::operator++()
    {
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

      while (! _DepthStateStack.empty ())
      {
        _DepthState *_ptr_state  = _DepthStateStack.top ();

        if (_ptr_state->_it_adj != _ptr_state->_it_adj_end && _has_color (_ptr_state->_it_adj->node (), _DepthInfo::WHITE))
        {
          _ptr_node = _ptr_state->_it_adj->node ();
          ++_ptr_state->_it_adj;
          _DepthStateStack.push (_DepthState (_ptr_node, _ptr_node->adj_list ().begin (), _ptr_node->adj_list ().end ()));
          _update_depth_info (_ptr_node, _ptr_state->_ptr_node, _DepthInfo::GRAY);
          break;
        }
        else
        {
          _DepthState *_ptr = _DepthStateStack.pop ();
          _update_depth_info (_ptr->_ptr_node, _DepthInfo::BLACK);
          delete _ptr;
        }
      }

      if (_DepthStateStack.empty ())
      {
        while (_it_node != _it_node_end && ! _has_color (&(*_it_node), _DepthInfo::WHITE))
          ++_it_node;

        if (_it_node == _it_node_end)
        {
          _ptr_node = NULL;
        }
        else
        {
          _ptr_node = &(*_it_node);
          _DepthInfoList.insert (_DepthInfo (&(*_it_node), _DepthInfo::GRAY, ++_global_time));
          _DepthStateStack.push (_DepthState (&(*_it_node), _it_node->adj_list ().begin (), _it_node->adj_list ().end ()));
        }
      }

      return *this;
    }

  template<typename _TpVertex, typename _TpEdge>
    const bool _DepthIterator<_TpVertex, _TpEdge>::operator==(const _Self &_other) const
    {
      return _ptr_node == _other._ptr_node;
    }

  template<typename _TpVertex, typename _TpEdge>
    const bool _DepthIterator<_TpVertex, _TpEdge>::operator!=(const _Self &_other) const
    {
      return ! (*this == _other);
    }
}

#endif
