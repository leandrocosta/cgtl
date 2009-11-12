#ifndef _SCC_ITERATOR_H_
#define _SCC_ITERATOR_H_

#include "graph_scc_component.h"
#include "../base/heap/heap.h"

#include "../base/iterator/iterator_type.h"
using namespace cgt::base::iterator;

#include "../search/depth/depth_iterator.h"
using namespace cgt::search::depth;


/*
 * invert graph
 * run DFS (1)
 * invert graph again
 * create heap with DFS (1)
 * while (! end)
 *  - pop n1 from heap and push in the stack
 *  - run DFS (2) with n1 until finish the SCC
 */

namespace cgt
{
  namespace stconncomp
  {
    template<typename _TpVertex, typename _TpEdge, template<typename> class _TpIterator = _TpCommon>
      class _SCCIterator
      {
        private:
          class _SCC_DFSInfo;

        private:
          typedef _SCCIterator<_TpVertex, _TpEdge>              _Self;
          typedef _SCCIterator<_TpVertex, _TpEdge, _TpCommon>   _SelfCommon;

        private:
          typedef _GraphSCCComponent<_TpVertex, _TpEdge>  _Component;
          typedef _GraphNode<_TpVertex, _TpEdge>          _Node;
          typedef typename _List<_Node>::iterator         _NodeIterator;
          typedef _GraphSCCNode<_TpVertex, _TpEdge>       _SCCNode;

          typedef _DepthIterator<_TpVertex, _TpEdge, _TpConst>  _DFSIterator;
          typedef typename _DFSIterator::_DepthInfo             _DFSInfo;
          typedef _List<_DFSInfo>                               _DFSInfoList;
          typedef typename _DFSInfoList::iterator               _DFSInfoIterator;
          typedef typename _DFSInfoList::const_iterator         _DFSInfoCIterator;
          typedef typename _DFSInfo::_color_t                   _DFSColor;
          typedef typename _DFSIterator::_DepthState            _DFSState;
          typedef _Stack<_DFSState>                             _DFSStateStack;

          typedef cgt::base::heap::_Heap<_SCC_DFSInfo>      _SCC_DFSInfoHeap;
          typedef typename _SCC_DFSInfoHeap::const_iterator _SCC_DFSInfoHeapIterator;

          class _SCC_DFSInfo
          {
            public:
              _SCC_DFSInfo (const _DFSInfo& _i) : _info (_i) { }

            public:
              const _DFSInfo& info () const { return _info; }
              const _Node& node () const { return _info.node (); }

            public:
              const bool operator<(const _SCC_DFSInfo& _b){ return _info.finish () >= _b._info.finish (); }

            private:
              const _DFSInfo& _info;
          };

        public:
          _SCCIterator () : _ptr_component (NULL) { }
          _SCCIterator (const _NodeIterator& _it_begin, const _NodeIterator& _it_end) : _ptr_component (NULL), _it_node_begin (_it_begin), _it_node_end (_it_end) { _init (); }
          _SCCIterator (const _SelfCommon& _it) { *this = _it; }

        _Self& operator=(const _Self& _it)
        {
          _it_node_begin  = _it._it_node_begin;
          _it_node_end    = _it._it_node_end;
          _it_dfs         = _it._it_dfs;
          _component_list = _it._component_list;
          _dfsHeap        = _it._dfsHeap;
          _dfsInfoList    = _it._dfsInfoList;
          _dfsStateStack  = _it._dfsStateStack;

          if (_it._ptr_component)
            _ptr_component  = _component_list.back ();

          return *this;
        }

        private:
          void _init ()
          {
            for (_NodeIterator _it = _it_node_begin; _it != _it_node_end; ++_it)
              _it->_invert_edges ();

            _it_dfs = _DFSIterator (_it_node_begin, _it_node_begin, _it_node_end);
            _DFSIterator  _it_dfs_end (NULL, _it_node_begin, _it_node_end);

            while (_it_dfs != _it_dfs_end)
              ++_it_dfs;

            for (_NodeIterator _it = _it_node_begin; _it != _it_node_end; ++_it)
              _it->_invert_edges ();

            /*
             * Now we have the result of DFS (1) in _it_dfs.
             * We need to make a heap with it and then,
             * iterate by the strongly connected components.
             */

            _DFSInfoIterator _it_end (_it_dfs.info_end ());
            for (_DFSInfoIterator _it (_it_dfs.info_begin ()); _it != _it_end; ++_it)
              _dfsHeap.push (_SCC_DFSInfo (*_it));

            _SCC_DFSInfoHeapIterator _it;
            _SCC_DFSInfoHeapIterator _itEnd = _dfsHeap.end ();

            for (_it = _dfsHeap.begin (); _it != _itEnd; ++_it)
              _dfsInfoList.insert (_DFSInfo (_it->node ()));

            _SCC_DFSInfo* pDFSInfo = _dfsHeap.pop ();

            if (pDFSInfo)
            {
              _dfsStateStack.insert (_DFSState (pDFSInfo->node ()));
              _discover_node (pDFSInfo->node (), NULL);


              /*
               * create SCC, add pDFSInfo to it and add SCC to component list
               */
              _component_list.insert (_Component (_SCCNode (pDFSInfo->node ().vertex ())));
              _ptr_component = _component_list.back ();

              /*
               * add all reachable nodes from pDFSInfo to the SCC
               */

              _Node* _ptr_node = NULL;

              while (! _dfsStateStack.empty ())
              {
                _DFSState *_ptr_state  = _dfsStateStack.top ();

                while (! _ptr_state->adj_finished ())
                {
                  if (_has_color (_ptr_state->_adj_node (), _DFSInfo::WHITE))
                  {
                    _ptr_node = &(_ptr_state->_adj_node ());
                    _ptr_state->adj_incr ();
                    _dfsStateStack.push (_DFSState (*_ptr_node));
                    _discover_node (*_ptr_node, &(_ptr_state->node ()));
                    break;
                  }
                  else
                    _ptr_state->adj_incr ();
                }

                if (_ptr_node)
                {
                  _component_list.back ()->insert (_SCCNode (_ptr_node->vertex ()));
                  delete _ptr_node;
                  _ptr_node = NULL;
                }
                else
                {
                  _DFSState *_ptr = _dfsStateStack.pop ();
                  _finish_node (_ptr->node ());
                  delete _ptr;
                }
              }

              delete pDFSInfo;
            }
          }

        private:
          void _discover_node (const _Node& _node, const _Node* const _ptr_parent);
          void _finish_node (const _Node& _node);
          const bool _has_color (const _Node& _node, const _DFSColor &_color) const;
          _DFSInfo* _get_depth_info_by_node (const _Node& _node);

        public:
          _Component& operator*() const { return *_ptr_component; }
          _Component* operator->() const { return _ptr_component; }
          const bool operator==(const _Self& _other) const { return (_ptr_component == _other._ptr_component); }
          const bool operator!=(const _Self& _other) const { return !(*this == _other); }
          _Self& operator++()
          {
            _ptr_component = NULL;

            /*
             * get the next node to create a new SCC
             */

            _SCC_DFSInfo* pDFSInfo = _dfsHeap.pop ();

            while (pDFSInfo && ! _has_color (pDFSInfo->node (), _DFSInfo::WHITE))
            {
              delete pDFSInfo;
              pDFSInfo = _dfsHeap.pop ();
            }

            if (pDFSInfo)
            {
              _dfsStateStack.insert (_DFSState (pDFSInfo->node ()));
              _discover_node (pDFSInfo->node (), NULL);


              /*
               * add pDFSInfo to the SCC
               */
              _component_list.insert (_Component (_SCCNode (pDFSInfo->node ().vertex ())));
              _ptr_component = _component_list.back ();

              /*
               * add all reachable nodes from pDFSInfo to the SCC
               */

              _Node* _ptr_node = NULL;

              while (! _dfsStateStack.empty ())
              {
                _DFSState *_ptr_state  = _dfsStateStack.top ();

                while (! _ptr_state->adj_finished ())
                {
                  if (_has_color (_ptr_state->_adj_node (), _DFSInfo::WHITE))
                  {
                    _ptr_node = &(_ptr_state->_adj_node ());
                    _ptr_state->adj_incr ();
                    _dfsStateStack.push (_DFSState (*_ptr_node));
                    _discover_node (*_ptr_node, &(_ptr_state->node ()));
                    break;
                  }
                  else
                    _ptr_state->adj_incr ();
                }

                if (_ptr_node)
                {
                  _component_list.back ()->insert (_SCCNode (_ptr_node->vertex ()));
//                  delete _ptr_node;
                  _ptr_node = NULL;
                }
                else
                {
                  _DFSState *_ptr = _dfsStateStack.pop ();
                  _finish_node (_ptr->node ());
                  delete _ptr;
                }
              }

              delete pDFSInfo;
            }

            return *this;
          }

        private:
          _Component*       _ptr_component;
          _List<_Component> _component_list;

          _NodeIterator _it_node_begin;
          _NodeIterator _it_node_end;

          _DFSIterator    _it_dfs;

          /*
           * _Heap uses the operator< to identify priority:
           *  i[n] is always <= i[2n] and i[2n+1]
           * So, we need a structure to encapsulate DFSInfo and
           * implement operator< correctly.
           */

          _SCC_DFSInfoHeap  _dfsHeap;
          _DFSInfoList      _dfsInfoList;
          _DFSStateStack    _dfsStateStack;
      };

    template<typename _TpVertex, typename _TpEdge, template<typename> class _TpIterator>
      void _SCCIterator<_TpVertex, _TpEdge, _TpIterator>::_discover_node (const _Node& _node, const _Node* const _ptr_parent)
      {
        _DFSInfo *_ptr = _get_depth_info_by_node (_node);

        if (_ptr)
        {
          _ptr->set_parent (_ptr_parent);
          _ptr->set_color (_DFSInfo::GRAY);
        }
      }

    template<typename _TpVertex, typename _TpEdge, template<typename> class _TpIterator>
      void _SCCIterator<_TpVertex, _TpEdge, _TpIterator>::_finish_node (const _Node& _node)
      {
        _DFSInfo *_ptr = _get_depth_info_by_node (_node);

        if (_ptr)
          _ptr->set_color (_DFSInfo::BLACK);
      }

    template<typename _TpVertex, typename _TpEdge, template<typename> class _TpIterator>
      const bool _SCCIterator<_TpVertex, _TpEdge, _TpIterator>::_has_color (const _Node& _node, const _DFSColor &_color) const
      {
        bool bRet = false;

        _DFSInfoCIterator itEnd = _dfsInfoList.end ();

        for (_DFSInfoCIterator it = _dfsInfoList.begin (); it != itEnd; ++it)
        {
          if (it->node ().vertex () == _node.vertex ())
          {
            bRet = (it->color () == _color);
            break;
          }
        }

        return bRet;
      }

    template<typename _TpVertex, typename _TpEdge, template<typename> class _TpIterator>
      typename _DepthIterator<_TpVertex, _TpEdge, _TpConst>::_DepthInfo* _SCCIterator<_TpVertex, _TpEdge, _TpIterator>::_get_depth_info_by_node (const _Node& _node)
      {
        _DFSInfo *_ptr = NULL;

        _DFSInfoIterator itEnd = _dfsInfoList.end ();

        for (_DFSInfoIterator it = _dfsInfoList.begin (); it != itEnd; ++it)
        {
          if (it->node ().vertex () == _node.vertex ())
          {
            _ptr = &(*it);
            break;
          }
        }

        return _ptr;
      }
  }
}

#endif
