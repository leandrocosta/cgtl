#ifndef _GRAPH_H_
#define _GRAPH_H_

//#include "list/list_item_base.h"
//#include "list/list_item.h"
#include "list/list.h"
//#include "list/list_iterator_base.h"
//#include "list/list_iterator.h"
//#include "list/list_const_iterator.h"
#include "graph_vertex.h"
#include "graph_edge.h"
#include "adjacency.h"
#include "graph_node.h"
#include "adj_list.h"
#include "adj_matrix.h"
#include "vertex_iterator.h"
#include "depth_iterator.h"
#include "graph_type.h"


namespace cgt
{
  template<typename _TpVertex, typename _TpEdge, typename _TpGraphType = _Directed>
    class graph : private _AdjMatrix<_TpVertex, _TpEdge, _TpGraphType>
  {
    private:
      typedef _AdjMatrix<_TpVertex, _TpEdge, _TpGraphType> _Base;

    public:
      typedef _GraphVertex<_TpVertex>         vertex;
      typedef _GraphEdge<_TpVertex, _TpEdge>  edge;
      typedef _GraphNode<_TpVertex, _TpEdge>  node;
      typedef _AdjList<_TpVertex, _TpEdge>    adjlist;

      typedef typename _Base::iterator                        iterator;
      typedef typename _Base::const_iterator                  const_iterator;

      typedef _VertexIterator<_TpVertex, _TpEdge>             vertex_iterator;
      typedef _ListIterator<_GraphEdge<_TpVertex, _TpEdge> >  edge_iterator;

      typedef _DepthIterator<_TpVertex, _TpEdge>              depth_iterator;

    public:
      void insert_vertex (const _TpVertex &_vertex) { _insert_vertex (_vertex); }
      void insert_edge (const _TpEdge &_e, const _TpVertex &_v1, const _TpVertex &_v2) { _insert_edge (_e, _v1, _v2); }

    public:
      const node* get_node (const _TpVertex &_vertex) { return _Base::_get_node (_vertex); }

    public:
      const bool is_directed () const { return _Base::_is_directed (); }
      const bool is_undirected () const { return _Base::_is_undirected (); }

    public:
      iterator begin () { return _Base::begin (); }
      iterator end () { return _Base::end (); }
      const_iterator begin () const { return _Base::begin (); }
      const_iterator end () const { return _Base::end (); }
      edge_iterator edge_begin () { return edge_iterator (_Base::_edge_list.begin ()); }
      edge_iterator edge_end () { return edge_iterator (_Base::_edge_list.end ()); }
      vertex_iterator vertex_begin () { return vertex_iterator (_Base::begin ()); }
      vertex_iterator vertex_end () { return vertex_iterator (_Base::end ()); }
      depth_iterator depth_begin () { return depth_iterator (&(*_Base::begin ()), _Base::begin (), _Base::end ()); }
//      depth_iterator depth_begin (const iterator _it = _Base::begin ()) { return depth_iterator (_Base::begin ()); }
//      depth_iterator depth_begin (const iterator _it = _Base::begin ()) { return depth_iterator (_it); }
      depth_iterator depth_end () { return depth_iterator (NULL, _Base::begin (), _Base::end ()); }
  };
}

#endif
