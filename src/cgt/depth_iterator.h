#ifndef _DEPTH_ITERATOR_H_
#define _DEPTH_ITERATOR_H_

#include "list/list_iterator.h"
using namespace cgt::list;

#include "stack/stack.h"
using namespace cgt::stack;


namespace cgt
{
  template<typename _TpVertex, typename _TpEdge>
    class _GraphAdjacency;

//  template<typename _TpVertex, typename _TpEdge, template<typename> class _TpIterator>
//    class _DepthInfoIterator;

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
    class _DepthIterator
    {
//      private:
//        friend class _DepthInfoIterator<_TpVertex, _TpEdge, _TpIterator>;

      public:
        class _DepthInfo;

      private:
        typedef _DepthIterator<_TpVertex, _TpEdge, _TpIterator> _Self;
        typedef _DepthIterator<_TpVertex, _TpEdge, _TpCommon>   _SelfCommon;
        typedef _GraphNode<_TpVertex, _TpEdge>                  _Node;
        typedef _GraphAdjacency<_TpVertex, _TpEdge>             _Adjacency;
        typedef typename _List<_Node>::iterator                 _NodeIterator;
        typedef typename _List<_Adjacency>::const_iterator      _AdjIterator;
        typedef typename _List<_DepthInfo>::iterator            _DIIterator;

      public:

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
            const _Node* const node () const { return _ptr_node; }
            const _Node* const parent () const { return _ptr_parent; }
            const _color_t& color () const { return _color; }
            const unsigned long& discovery () const { return _discovery; }
            const unsigned long& finish () const { return _finish; }

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
            _DepthState (const _Node& _n, const _AdjIterator &_it_a, const _AdjIterator &_it_adj_e) : _node (_n), _it_adj (_it_a), _it_adj_end (_it_adj_e) { };

          public:
            const _Node&        _node;
            _AdjIterator        _it_adj;
            const _AdjIterator  _it_adj_end;
        };
        
      public:
        _DepthIterator () : _ptr_node (NULL), _it_node (NULL), _it_node_end (NULL), _global_time (0) { }
        _DepthIterator (_Node* const _ptr_n, const _NodeIterator& _it_begin, const _NodeIterator& _it_end) : _ptr_node (_ptr_n), _it_node (_it_begin), _it_node_end (_it_end), _global_time (0)
        {
          _init ();
        }
        _DepthIterator (const _NodeIterator& _it, const _NodeIterator& _it_begin, const _NodeIterator& _it_end) : _ptr_node (&(*_it)), _it_node (_it_begin), _it_node_end (_it_end), _global_time (0)
        {
          _init ();
        }
        _DepthIterator (const _SelfCommon& _it) : _ptr_node (_it._ptr_node), _it_node (_it._it_node), _it_node_end (_it._it_node_end), _global_time (_it._global_time)
        {
          _DepthInfoList = _it._DepthInfoList;
        }

      private:
        void _init ();
        _DepthInfo* _get_depth_info_by_node (const _Node* const _ptr_node)
        {
          _DepthInfo *_ptr = NULL;

          _DIIterator it;
          _DIIterator itEnd = _DepthInfoList.end ();

          for (it = _DepthInfoList.begin (); it != itEnd; ++it)
          {
            if (it->_ptr_node == _ptr_node)
            {
              _ptr = &(*it);
              break;
            }
          }

          return _ptr;
        }

        void _discover_node (const _Node* const _ptr_node, const _Node* const _ptr_parent, const unsigned long& _d);
        void _finish_node (const _Node* const _ptr_node, const unsigned long& _f);
        const bool _has_color (const _Node* const _ptr_node, const typename _DepthInfo::_color_t &_color) const;

      public:
        _Node& operator*() const;
        _Node* operator->() const;
        _Self& operator++();
        const _Self operator++(int);
        const bool operator==(const _Self &_other) const;
        const bool operator!=(const _Self &_other) const;

      public:
        const _DepthInfo* const info (const _Node* const _ptr_node) { return _get_depth_info_by_node (_ptr_node); }
        const _DepthInfo* const info (const _Node& _node) { return _get_depth_info_by_node (&_node); }

        typename _List<_DepthInfo>::iterator info_begin () { return _DepthInfoList.begin (); }
        typename _List<_DepthInfo>::iterator info_end () { return _DepthInfoList.end (); }

      private:
        _Node*              _ptr_node;
        _NodeIterator       _it_node;
        _NodeIterator       _it_node_end;
        _Stack<_DepthState> _DepthStateStack;
        _List<_DepthInfo>   _DepthInfoList;

        unsigned long       _global_time;
    };


  template<typename _TpVertex, typename _TpEdge, template<typename> class _TpIterator>
    void _DepthIterator<_TpVertex, _TpEdge, _TpIterator>::_init ()
    {

      /*
       * paint the first node (_ptr_node) with GRAY;
       * put it on the stack;
       * turn it the current node (actualy, it already is the current node);
       * paint all the others with WHITE.
       */

      _NodeIterator it;

      for (it = _it_node; it != _it_node_end; ++it)
      {
        if (&(*it) == _ptr_node)
        {
          _DepthInfoList.insert (_DepthInfo (&(*it), _DepthInfo::GRAY, ++_global_time));
          _DepthStateStack.push (_DepthState (*it, it->adj_list ().begin (), it->adj_list ().end ()));
        }
        else
          _DepthInfoList.insert (_DepthInfo (&(*it)));
      }
    }

  template<typename _TpVertex, typename _TpEdge, template<typename> class _TpIterator>
    void _DepthIterator<_TpVertex, _TpEdge, _TpIterator>::_discover_node (const _Node* const _ptr_node, const _Node* const _ptr_parent, const unsigned long& _d)
    {
      _DepthInfo *_ptr = _get_depth_info_by_node (_ptr_node);

      if (_ptr)
      {
        _ptr->_ptr_parent = _ptr_parent;
        _ptr->_color      = _DepthInfo::GRAY;
        _ptr->_discovery  = _d;
      }
    }

  template<typename _TpVertex, typename _TpEdge, template<typename> class _TpIterator>
    void _DepthIterator<_TpVertex, _TpEdge, _TpIterator>::_finish_node (const _Node* const _ptr_node, const unsigned long& _f)
    {
      _DepthInfo *_ptr = _get_depth_info_by_node (_ptr_node);

      if (_ptr)
      {
        _ptr->_color      = _DepthInfo::BLACK;
        _ptr->_finish     = _f;
      }
    }

  template<typename _TpVertex, typename _TpEdge, template<typename> class _TpIterator>
    const bool _DepthIterator<_TpVertex, _TpEdge, _TpIterator>::_has_color (const _Node* _ptr_node, const typename _DepthInfo::_color_t &_color) const
    {
      bool bRet = false;

      _ListIterator<_DepthInfo, _TpConst> it;
      _ListIterator<_DepthInfo, _TpConst> itEnd = _DepthInfoList.end ();

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

  template<typename _TpVertex, typename _TpEdge, template<typename> class _TpIterator>
    _GraphNode<_TpVertex, _TpEdge>& _DepthIterator<_TpVertex, _TpEdge, _TpIterator>::operator*() const
    {
      return *_ptr_node;
    }

  template<typename _TpVertex, typename _TpEdge, template<typename> class _TpIterator>
    _GraphNode<_TpVertex, _TpEdge>* _DepthIterator<_TpVertex, _TpEdge, _TpIterator>::operator->() const
    {
      return _ptr_node;
    }

  template<typename _TpVertex, typename _TpEdge, template<typename> class _TpIterator>
    _DepthIterator<_TpVertex, _TpEdge, _TpIterator>& _DepthIterator<_TpVertex, _TpEdge, _TpIterator>::operator++()
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

        if (_ptr_state->_it_adj != _ptr_state->_it_adj_end)
        {
          if (_has_color (_ptr_state->_it_adj->node (), _DepthInfo::WHITE))
          {
            _ptr_node = _ptr_state->_it_adj->node ();
            ++_ptr_state->_it_adj;
            _DepthStateStack.push (_DepthState (*_ptr_node, _ptr_node->adj_list ().begin (), _ptr_node->adj_list ().end ()));
            _discover_node (_ptr_node, &(_ptr_state->_node), ++_global_time);
            break;
          }
          else
            ++_ptr_state->_it_adj;
        }
        else
        {
          _DepthState *_ptr = _DepthStateStack.pop ();
          _finish_node (&(_ptr->_node), ++_global_time);
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
//          _DepthInfoList.insert (_DepthInfo (&(*_it_node), _DepthInfo::GRAY, ++_global_time));
          _DepthStateStack.push (_DepthState (*_it_node, _it_node->adj_list ().begin (), _it_node->adj_list ().end ()));
          _discover_node (&(*_it_node), NULL, ++_global_time);
        }
      }

      return *this;
    }

  template<typename _TpVertex, typename _TpEdge, template<typename> class _TpIterator>
    const _DepthIterator<_TpVertex, _TpEdge, _TpIterator> _DepthIterator<_TpVertex, _TpEdge, _TpIterator>::operator++(int)
    {
      _Self _it = *this;
      operator++();
      return _it;
    }

  template<typename _TpVertex, typename _TpEdge, template<typename> class _TpIterator>
    const bool _DepthIterator<_TpVertex, _TpEdge, _TpIterator>::operator==(const _Self &_other) const
    {
      return _ptr_node == _other._ptr_node;
    }

  template<typename _TpVertex, typename _TpEdge, template<typename> class _TpIterator>
    const bool _DepthIterator<_TpVertex, _TpEdge, _TpIterator>::operator!=(const _Self &_other) const
    {
      return !(*this == _other);
    }
}

#endif
