#ifndef _SCC_ITERATOR_H_
#define _SCC_ITERATOR_H_

#include "graph_scc_component.h"

#include "../base/iterator/iterator_type.h"
using namespace cgt::base::iterator;

#include "../search/depth/depth_iterator.h"
using namespace cgt::search::depth;

#include "../base/heap/heap.h"
using namespace cgt::base::heap;

/*
3) Implementar iterador de SCC com o seguinte algoritmo:
- Faz DFS1 no grafo;
- Inicializa DFS2 do grafo invertido;
- Constrói um heap com cada info do DFS1 + DFS2 para cada nodo, ordenado pelo tempo de finalização do DFS1;
- A cada iteração:
 - Obtém o próximo elemento ainda não vistiado do heap;
  - Realiza DFS2++ adicionando os nodos no SCComponent até que a visita deste elemento finalize;
   - Retorna o SCComponent.
   4) SCComponent é uma lista de SCNodos. Cada SCNodo é um nodo que possui um ponteiro para o seu Vertex + uma lista de adjacências. Esta lista possui ponteiros apenas para os Edges que fazem parte deste SCComponent.
*/

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
//      class _SCCIterator : private _DepthIterator<_TpVertex, _TpEdge, _TpConst>
      class _SCCIterator
      {
        private:
          typedef _SCCIterator<_TpVertex, _TpEdge>              _Self;
          typedef _SCCIterator<_TpVertex, _TpEdge, _TpCommon>   _SelfCommon;
//          typedef _DepthIterator<_TpVertex, _TpEdge, _TpConst>  _Base;

        private:
          typedef _GraphSCCComponent<_TpVertex, _TpEdge>  _Component;
          typedef _GraphNode<_TpVertex, _TpEdge>          _Node;
          typedef typename _List<_Node>::iterator         _NodeIterator;
          typedef _GraphSCCNode<_TpVertex, _TpEdge>       _SCCNode;

          typedef _DepthIterator<_TpVertex, _TpEdge, _TpConst>                _DFSIterator;
          typedef typename _DFSIterator::_DepthInfo                           _DFSInfo;
          typedef _List<typename _DFSIterator::_DepthInfo>                    _DFSInfoList;
          typedef typename _List<typename _DFSIterator::_DepthInfo>::iterator _DFSInfoIterator;
          typedef typename _DFSIterator::_DepthState                          _DFSState;
          typedef _Stack<typename _DFSIterator::_DepthState>                  _DFSStateStack;

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
          _SCCIterator (const _NodeIterator& _it_begin, const _NodeIterator& _it_end) : _ptr_component (NULL), _it_node_begin (_it_begin), _it_node_end (_it_end), _it_dfs (_it_node_begin, _it_node_begin, _it_node_end) { _init (); }
          _SCCIterator (const _SelfCommon& _it) { *this = _it; }

        _Self& operator=(const _Self& _it)
        {
          _it_node_begin  = _it._it_node_begin;
          _it_node_end    = _it._it_node_end;
          _it_dfs         = _it._it_dfs;
          _component_list = _it._component_list;
          _ptr_component  = _component_list.front ();
          _dfsHeap        = _it._dfsHeap;
          _dfsInfoList    = _it._dfsInfoList;
          _dfsStateStack  = _it._dfsStateStack;

          return *this;
        }

        private:
          void _init ()
          {
            for (_NodeIterator _it = _it_node_begin; _it != _it_node_end; ++_it)
              _it->_invert_edges ();

            _DFSIterator  _it_dfs_end (NULL, _it_node_begin, _it_node_end);

            if (_it_dfs != _it_dfs_end)
              cout << "first dfs: " << _it_dfs->vertex ().value ();

            ++_it_dfs;

            while (_it_dfs != _it_dfs_end)
            {
              cout << ", " << _it_dfs->vertex ().value ();
              ++_it_dfs;
            }

            cout << endl;

            typename _DFSInfoList::iterator itA (_it_dfs.info_begin ());
            typename _DFSInfoList::iterator itAEnd (_it_dfs.info_end ());

            for (; itA != itAEnd; ++itA)
              cout << "first dfs - node: " << itA->node ().vertex ().value () << ", finish: " << setw (2) << itA->finish () << endl;

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

            _SCC_DFSInfo* pDFSInfo = _dfsHeap.pop ();

            if (pDFSInfo)
            {
              cout << "first element of first SCC: " << pDFSInfo->node ().vertex ().value () << endl;

              _dfsStateStack.insert (_DFSState (pDFSInfo->node ()));

              typename _Heap<_SCC_DFSInfo>::const_iterator _it;
              typename _Heap<_SCC_DFSInfo>::const_iterator _itEnd = _dfsHeap.end ();

              for (_it = _dfsHeap.begin (); _it != _itEnd; ++_it)
                _dfsInfoList.insert (_DFSInfo (_it->node ()));

              /*
               * create SCC, add pDFSInfo to it and add SCC to component list
               */
              _component_list.push_back (_Component (_SCCNode (pDFSInfo->node ().vertex ())));
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
                  cout << "add element of first SCC: " << _ptr_node->vertex ().value () << endl;

                  _component_list.back ()->push_back (_SCCNode (_ptr_node->vertex ()));
                  delete _ptr_node;
                  _ptr_node = NULL;
                }
                else
                {
                  _DFSState *_ptr = _dfsStateStack.pop ();
                  _finish_node (_ptr->node ());
                  cout << "finishing element: " << _ptr->node ().vertex ().value () << endl;
                  delete _ptr;
                }
              }

              cout << "DFS finished, component [" << _ptr_component << "], front [" << _ptr_component->front () << "] : " << _ptr_component->front ()->vertex ().value () << endl;

              delete pDFSInfo;
            }
          }

        private:
          void _discover_node (const _Node& _node, const _Node* const _ptr_parent);
          void _finish_node (const _Node& _node);
          const bool _has_color (const _Node& _node, const typename _DFSInfo::_color_t &_color) const;
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
              cout << "node already visited: " << pDFSInfo->node ().vertex ().value () << endl;
              delete pDFSInfo;
              pDFSInfo = _dfsHeap.pop ();
            }

            if (pDFSInfo)
            {
              cout << "first element of SCC: " << pDFSInfo->node ().vertex ().value () << endl;
              _dfsStateStack.insert (_DFSState (pDFSInfo->node ()));

              /*
              typename _Heap<_SCC_DFSInfo>::const_iterator _it;
              typename _Heap<_SCC_DFSInfo>::const_iterator _itEnd = _dfsHeap.end ();

              for (_it = _dfsHeap.begin (); _it != _itEnd; ++_it)
                _dfsInfoList.insert (_DFSInfo (_it->node ()));
                */

              /*
               * add pDFSInfo to the SCC
               */
              _component_list.push_back (_Component (_SCCNode (pDFSInfo->node ().vertex ())));
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
                  _component_list.back ()->push_back (_SCCNode (_ptr_node->vertex ()));
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

          _Heap<_SCC_DFSInfo> _dfsHeap;
          _DFSInfoList    _dfsInfoList;
          _DFSStateStack  _dfsStateStack;
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
      const bool _SCCIterator<_TpVertex, _TpEdge, _TpIterator>::_has_color (const _Node& _node, const typename _DFSInfo::_color_t &_color) const
      {
        bool bRet = false;

        typename _List<_DFSInfo>::const_iterator it;
        typename _List<_DFSInfo>::const_iterator itEnd = _dfsInfoList.end ();

        for (it = _dfsInfoList.begin (); it != itEnd; ++it)
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

        _DFSInfoIterator it;
        _DFSInfoIterator itEnd = _dfsInfoList.end ();

        for (it = _dfsInfoList.begin (); it != itEnd; ++it)
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
