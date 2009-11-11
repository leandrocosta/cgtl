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
      class _SCCIterator
      {
        private:
          typedef _SCCIterator<_TpVertex, _TpEdge>            _Self;
          typedef _SCCIterator<_TpVertex, _TpEdge, _TpCommon> _SelfCommon;

        private:
          typedef _GraphSCCComponent<_TpVertex, _TpEdge>  _Component;
          typedef _GraphNode<_TpVertex, _TpEdge>          _Node;
          typedef typename _List<_Node>::iterator         _NodeIterator;

          typedef _DepthIterator<_TpVertex, _TpEdge, _TpConst>                _DFSIterator;
          typedef typename _DFSIterator::_DepthInfo                           _DFSInfo;
          typedef typename _List<typename _DFSIterator::_DepthInfo>::iterator _DFSInfoIterator;

          class _SCC_DFSInfo
          {
            public:
              _SCC_DFSInfo (const _DFSInfo& _i) : _info (_i) { }

            public:
              const bool operator<(const _SCC_DFSInfo& _b){ return _info.finish () >= _b._info.finish (); }

            private:
              const _DFSInfo& _info;
          };

        public:
          _SCCIterator () : _ptr_component (NULL) { }
          _SCCIterator (const _NodeIterator& _it_begin, const _NodeIterator& _it_end) : _ptr_component (NULL), _it_node_begin (_it_begin), _it_node_end (_it_end), _it_bfs (_it_node_begin, _it_node_begin, _it_node_end) { _init (); }
          _SCCIterator (const _SelfCommon& _it) : _ptr_component (_it._ptr_component), _it_node_begin (_it._it_node_begin), _it_node_end (_it._it_node_end) { }

        private:
          void _init ()
          {
            for (_NodeIterator _it = _it_node_begin; _it != _it_node_end; ++_it)
              _it->_invert_edges ();

            _DFSIterator  _it_bfs_end (NULL, _it_node_begin, _it_node_end);

            while (_it_bfs != _it_bfs_end)
              ++_it_bfs;

            for (_NodeIterator _it = _it_node_begin; _it != _it_node_end; ++_it)
              _it->_invert_edges ();

            /*
             * Now we have the result of DFS (1) in _it_bfs.
             * We need to make a heap with it and then,
             * iterate by the strongly connected components.
             */

            _DFSInfoIterator _it_end (_it_bfs.info_end ());
            for (_DFSInfoIterator _it (_it_bfs.info_begin ()); _it != _it_end; ++_it)
              _bfsHeap.push (_SCC_DFSInfo (*_it));

            _SCC_DFSInfo* pDFSInfo = _bfsHeap.pop ();

            if (pDFSInfo)
            {
              /*
               * We need to put this node and all nodes reachable from it
               * in the strongly connected component that will be returned
               * by this iteration. We need to execute part of the algorithm
               * implemented in depth first search.
               */

              /*
               * TODO: _SCCIterator needs execute as the same code
               * we implemented in _DepthIterator::operator++().
               */
            }
          }

        public:
          const bool operator!=(const _Self& _other) const { return false; }
          _Self& operator++() { return *this; }

        private:
          _Component*   _ptr_component;
          _NodeIterator _it_node_begin;
          _NodeIterator _it_node_end;

          _DFSIterator    _it_bfs;
          /*
           * _Heap uses the operator< to identify priority:
           *  i[n] is always <= i[2n] and i[2n+1]
           * So, we need a structure to encapsulate DFSInfo and
           * implement operator< correctly.
           */

          _Heap<_SCC_DFSInfo> _bfsHeap;
      };
  }
}

#endif
