#ifndef _GRAPH_H_
#define _GRAPH_H_

#include "list/list.h"
#include "graph_vertex.h"
#include "graph_edge.h"
#include "graph_adjacency.h"
#include "graph_node.h"
#include "adj_list.h"
#include "adj_matrix.h"
#include "vertex_iterator.h"
#include "depth_iterator.h"
#include "breadth_iterator.h"
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

      typedef typename _Base::iterator                      iterator;
      typedef typename _Base::const_iterator                const_iterator;

      typedef _VertexIterator<_TpVertex, _TpEdge>           viterator;
      typedef _VertexIterator<_TpVertex, _TpEdge, _TpConst> const_viterator;

      typedef typename _List<edge>::iterator                eiterator;
      typedef typename _List<edge>::const_iterator          const_eiterator;

      typedef _DepthIterator<_TpVertex, _TpEdge>            diterator;
      typedef _DepthIterator<_TpVertex, _TpEdge, _TpConst>  const_diterator;

      typedef typename _List<typename diterator::_DepthInfo>::iterator       diiterator;
      typedef typename _List<typename diterator::_DepthInfo>::const_iterator const_diiterator;

      typedef _BreadthIterator<_TpVertex, _TpEdge>            biterator;
      typedef _BreadthIterator<_TpVertex, _TpEdge, _TpConst>  const_biterator;

      typedef typename _List<typename biterator::_BreadthInfo>::iterator       biiterator;
      typedef typename _List<typename biterator::_BreadthInfo>::const_iterator const_biiterator;

      typedef typename diterator::_DepthInfo                depth_info;
      typedef typename biterator::_BreadthInfo                breadth_info;

    public:
      void insert_vertex (const _TpVertex &_vertex) { _insert_vertex (_vertex); }
      void insert_edge (const _TpEdge &_e, const _TpVertex &_v1, const _TpVertex &_v2) { _insert_edge (_e, _v1, _v2); }

    public:
      const node* get_node (const _TpVertex &_vertex) { return _Base::_get_node (_vertex); }
      iterator find (const _TpVertex &_vertex) { return _Base::_find (_vertex); }

    public:
      const bool is_directed () const { return _Base::_is_directed (); }
      const bool is_undirected () const { return _Base::_is_undirected (); }

    public:
      iterator begin () { return _Base::begin (); }
      iterator end () { return _Base::end (); }
      const_iterator begin () const { return _Base::begin (); }
      const_iterator end () const { return _Base::end (); }

      eiterator edge_begin () { return eiterator (_Base::_edge_list.begin ()); }
      eiterator edge_end () { return eiterator (_Base::_edge_list.end ()); }
      const_eiterator edge_begin () const { return const_eiterator (_Base::_edge_list.begin ()); }
      const_eiterator edge_end () const { return const_eiterator (_Base::_edge_list.end ()); }

      viterator vertex_begin () { return viterator (_Base::begin ()); }
      viterator vertex_end () { return viterator (_Base::end ()); }
      const_viterator vertex_begin () const { return const_viterator (_Base::begin ()); }
      const_viterator vertex_end () const { return const_viterator (_Base::end ()); }

      diterator depth_begin () { return diterator (_Base::begin (), _Base::begin (), _Base::end ()); }
      diterator depth_begin (const iterator& _it) { return diterator (_it, _Base::begin (), _Base::end ()); }
      diterator depth_end () { return diterator (NULL, _Base::begin (), _Base::end ()); }
      const_diterator depth_begin () const { return const_diterator (_Base::begin (), _Base::begin (), _Base::end ()); }
      const_diterator depth_begin (const iterator& _it) const { return const_diterator (_it, _Base::begin (), _Base::end ()); }
      const_diterator depth_end () const { return const_diterator (NULL, _Base::begin (), _Base::end ()); }

      diiterator depth_info_begin (diterator &_it) { return diiterator (_it.info_begin ()); }
      diiterator depth_info_end (diterator &_it) { return diiterator (_it.info_end ()); }
      const_diiterator depth_info_begin (diterator &_it) const { return const_diiterator (_it.info_begin ()); }
      const_diiterator depth_info_end (diterator &_it) const { return const_diiterator (_it.info_end ()); }

      biterator breadth_begin () { return biterator (_Base::begin (), _Base::begin (), _Base::end ()); }
      biterator breadth_begin (const iterator& _it) { return biterator (_it, _Base::begin (), _Base::end ()); }
      biterator breadth_end () { return biterator (NULL, _Base::begin (), _Base::end ()); }
      const_biterator breadth_begin () const { return const_biterator (_Base::begin (), _Base::begin (), _Base::end ()); }
      const_biterator breadth_begin (const iterator& _it) const { return const_biterator (_it, _Base::begin (), _Base::end ()); }
      const_biterator breadth_end () const { return const_biterator (NULL, _Base::begin (), _Base::end ()); }

      biiterator breadth_info_begin (biterator &_it) { return biiterator (_it.info_begin ()); }
      biiterator breadth_info_end (biterator &_it) { return biiterator (_it.info_end ()); }
      const_biiterator breadth_info_begin (biterator &_it) const { return const_biiterator (_it.info_begin ()); }
      const_biiterator breadth_info_end (biterator &_it) const { return const_biiterator (_it.info_end ()); }
  };
}

#endif
