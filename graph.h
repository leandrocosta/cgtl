#ifndef _GRAPH_H_
#define _GRAPH_H_

#include "list_item_base.h"
#include "list_item.h"
#include "list.h"
#include "list_iterator_base.h"
#include "list_iterator.h"
#include "vertice.h"
#include "edge.h"
#include "adjacency.h"
#include "graph_node.h"
#include "adj_list.h"
#include "adj_matrix.h"


template<typename _TpVertice, typename _TpEdge>
class graph : private _AdjMatrix<_TpVertice, _TpEdge>
{
  private:
    typedef _AdjMatrix<_TpVertice, _TpEdge> _Base;

  public:
    typedef _Vertice<_TpVertice>            vertice;
    typedef _Edge<_TpVertice, _TpEdge>      edge;
    typedef _GraphNode<_TpVertice, _TpEdge> node;
    typedef _AdjList<_TpVertice, _TpEdge>   adjlist;

    typedef typename _Base::iterator        iterator;

  public:
    void insert_vertice (const _TpVertice &_vertice) { _insert_vertice (_vertice); }
    void insert_edge (const _TpEdge &_e, const _TpVertice &_v1, const _TpVertice &_v2) { _insert_edge (_e, _v1, _v2); }

  public:
    iterator begin () { return _Base::begin (); }
    iterator end () { return _Base::end (); }
};

#endif
