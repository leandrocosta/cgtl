#ifndef _SEARCH_ITERATOR_H_
#define _SEARCH_ITERATOR_H_

#include "../graph_node.h"
#include "search_state.h"
#include "search_info.h"

#include "../stack/stack.h"
using namespace cgt::stack;


namespace cgt
{
  template<typename _TpVertex, typename _TpEdge, template<typename> class _TpStateContainer, template<typename> class _TpIterator = _TpCommon>
    class _SearchIterator
    {
      private:
        typedef _SearchIterator<_TpVertex, _TpEdge, _TpStateContainer, _TpIterator> _Self;
        typedef _SearchIterator<_TpVertex, _TpEdge, _TpStateContainer, _TpCommon>   _SelfCommon;

      private:
        typedef _SearchInfo<_TpVertex, _TpEdge> _Info;
        typedef typename _List<_Info>::iterator _InfoIterator;

      protected:
        typedef _GraphNode<_TpVertex, _TpEdge>    _Node;
        typedef typename _List<_Node>::iterator   _NodeIterator;
        typedef _SearchState<_TpVertex, _TpEdge>  _State;

      protected:
        _SearchIterator () : _ptr_node (NULL), _it_node (NULL), _it_node_end (NULL), _global_time (0) { }
        _SearchIterator (_Node* const _ptr_n, const _NodeIterator& _it_begin, const _NodeIterator& _it_end) : _ptr_node (_ptr_n), _it_node (_it_begin), _it_node_end (_it_end), _global_time (0)
        {
          if (_ptr_node)
            _init ();
        }
        _SearchIterator (const _SelfCommon& _it) : _ptr_node (_it._ptr_node), _it_node (_it._it_node), _it_node_end (_it._it_node_end), _global_time (_it._global_time), _InfoList (_it._InfoList) { }
        virtual ~_SearchIterator () { }

      private:
        void _init ();

      protected:
        _Info* _get_depth_info_by_node (const _Node* const _ptr_node);

      protected:
        void _discover_node (const _Node* const _ptr_node, const _Node* const _ptr_parent, const unsigned long& _d);
        void _finish_node (const _Node* const _ptr_node, const unsigned long& _f);
        const bool _has_color (const _Node* const _ptr_node, const typename _Info::_color_t &_color) const;

      public:
        _Node& operator*() const;
        _Node* operator->() const;
        const bool operator==(const _Self &_other) const;
        const bool operator!=(const _Self &_other) const;
        const _Self operator++(int);

      protected:
        _Node*                    _ptr_node;
        _NodeIterator             _it_node;
        _NodeIterator             _it_node_end;
        _List<_Info>              _InfoList;
        _TpStateContainer<_State> _StateContainer;

        unsigned long             _global_time;
    };

  template<typename _TpVertex, typename _TpEdge, template<typename> class _TpStateContainer, template<typename> class _TpIterator>
    void _SearchIterator<_TpVertex, _TpEdge, _TpStateContainer, _TpIterator>::_init ()
    {
      /*
       * paint the first node (_ptr_node) with GRAY;
       * put it on the state container;
       * turn it the current node (actualy, it already is the current node);
       * paint all the others with WHITE.
       */

      _NodeIterator it;

      for (it = _it_node; it != _it_node_end; ++it)
      {
        if (&(*it) == _ptr_node)
        {
          _InfoList.insert (_Info (*it, _Info::GRAY, ++_global_time));
          _StateContainer.insert (_State (*it));
        }
        else
          _InfoList.insert (_Info (*it));
      }
    }

  template<typename _TpVertex, typename _TpEdge, template<typename> class _TpStateContainer, template<typename> class _TpIterator>
    typename _SearchIterator<_TpVertex, _TpEdge, _TpStateContainer, _TpIterator>::_Info* _SearchIterator<_TpVertex, _TpEdge, _TpStateContainer, _TpIterator>::_get_depth_info_by_node (const _Node* const _ptr_node)
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

  template<typename _TpVertex, typename _TpEdge, template<typename> class _TpStateContainer, template<typename> class _TpIterator>
    void _SearchIterator<_TpVertex, _TpEdge, _TpStateContainer, _TpIterator>::_discover_node (const _Node* const _ptr_node, const _Node* const _ptr_parent, const unsigned long& _d)
    {
      _Info *_ptr = _get_depth_info_by_node (_ptr_node);

      if (_ptr)
      {
        _ptr->set_parent (_ptr_parent);
        _ptr->set_color (_Info::GRAY);
        _ptr->set_discovery (_d);
      }
    }

  template<typename _TpVertex, typename _TpEdge, template<typename> class _TpStateContainer, template<typename> class _TpIterator>
    void _SearchIterator<_TpVertex, _TpEdge, _TpStateContainer, _TpIterator>::_finish_node (const _Node* const _ptr_node, const unsigned long& _f)
    {
      _Info *_ptr = _get_depth_info_by_node (_ptr_node);

      if (_ptr)
      {
        _ptr->set_color (_Info::BLACK);
        _ptr->set_finish (_f);
      }
    }

  template<typename _TpVertex, typename _TpEdge, template<typename> class _TpStateContainer, template<typename> class _TpIterator>
    const bool _SearchIterator<_TpVertex, _TpEdge, _TpStateContainer, _TpIterator>::_has_color (const _Node* _ptr_node, const typename _Info::_color_t &_color) const
    {
      bool bRet = false;

      _ListIterator<_Info, _TpConst> it;
      _ListIterator<_Info, _TpConst> itEnd = _InfoList.end ();

      for (it = _InfoList.begin (); it != itEnd; ++it)
      {
        if (it->node ().vertex () == _ptr_node->vertex ())
        {
          bRet = (it->color () == _color);
          break;
        }
      }

      return bRet;
    }

  template<typename _TpVertex, typename _TpEdge, template<typename> class _TpStateContainer, template<typename> class _TpIterator>
    _GraphNode<_TpVertex, _TpEdge>& _SearchIterator<_TpVertex, _TpEdge, _TpStateContainer, _TpIterator>::operator*() const
    {
      return *_ptr_node;
    }

  template<typename _TpVertex, typename _TpEdge, template<typename> class _TpStateContainer, template<typename> class _TpIterator>
    _GraphNode<_TpVertex, _TpEdge>* _SearchIterator<_TpVertex, _TpEdge, _TpStateContainer, _TpIterator>::operator->() const
    {
      return _ptr_node;
    }

  template<typename _TpVertex, typename _TpEdge, template<typename> class _TpStateContainer, template<typename> class _TpIterator>
    const bool _SearchIterator<_TpVertex, _TpEdge, _TpStateContainer, _TpIterator>::operator==(const _Self &_other) const
    {
      return _ptr_node == _other._ptr_node;
    }

  template<typename _TpVertex, typename _TpEdge, template<typename> class _TpStateContainer, template<typename> class _TpIterator>
    const bool _SearchIterator<_TpVertex, _TpEdge, _TpStateContainer, _TpIterator>::operator!=(const _Self &_other) const
    {
      return !(*this == _other);
    }

  template<typename _TpVertex, typename _TpEdge, template<typename> class _TpStateContainer, template<typename> class _TpIterator>
    const _SearchIterator<_TpVertex, _TpEdge, _TpStateContainer, _TpIterator> _SearchIterator<_TpVertex, _TpEdge, _TpStateContainer, _TpIterator>::operator++(int)
    {
      _Self _it = *this;
      operator++();
      return _it;
    }
}

#endif
