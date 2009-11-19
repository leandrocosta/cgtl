#ifndef _GRAPH_H_
#define _GRAPH_H_

#include "graph_type.h"
#include "graph_vertex.h"
#include "graph_edge.h"
#include "graph_adjacency.h"
#include "graph_node.h"
#include "graph_adjlist.h"
#include "graph_adjmatrix.h"
#include "vertex_iterator.h"

#include "search/depth/depth_iterator.h"
#include "search/breadth/breadth_iterator.h"
#include "shortpath/single/dijkstra/dijkstra_iterator.h"
#include "minspantree/prim/prim_iterator.h"
#include "minspantree/kruskal/kruskal_iterator.h"

#include "stconncomp/scc_iterator.h"
#include "stconncomp/graph_scc_component.h"
#include "stconncomp/graph_scc_node.h"


namespace cgt
{
  template<typename _TpVertex, typename _TpEdge, typename _TpGraphType = _Directed>
    class graph : private _GraphAdjMatrix<_TpVertex, _TpEdge, _TpGraphType>
  {
    private:
      typedef _GraphAdjMatrix<_TpVertex, _TpEdge, _TpGraphType> _Base;

    public:
      typedef _GraphVertex<_TpVertex>           vertex;
      typedef _GraphEdge<_TpVertex, _TpEdge>    edge;
      typedef _GraphNode<_TpVertex, _TpEdge>    node;
      typedef _GraphAdjList<_TpVertex, _TpEdge> adjlist;

      typedef typename _Base::iterator                      iterator;
      typedef typename _Base::const_iterator                const_iterator;

      typedef _VertexIterator<_TpVertex, _TpEdge>           viterator;
      typedef _VertexIterator<_TpVertex, _TpEdge, _TpConst> const_viterator;

      typedef typename cgt::base::list<edge>::iterator                eiterator;
      typedef typename cgt::base::list<edge>::const_iterator          const_eiterator;

      typedef _DepthIterator<_TpVertex, _TpEdge>            diterator;
      typedef _DepthIterator<_TpVertex, _TpEdge, _TpConst>  const_diterator;

      typedef typename cgt::base::list<typename diterator::_DepthInfo>::iterator       diiterator;
      typedef typename cgt::base::list<typename diterator::_DepthInfo>::const_iterator const_diiterator;

      typedef cgt::search::breadth::_BreadthIterator<_TpVertex, _TpEdge>            biterator;
      typedef cgt::search::breadth::_BreadthIterator<_TpVertex, _TpEdge, _TpConst>  const_biterator;

      typedef typename cgt::base::list<typename biterator::_BreadthInfo>::iterator       biiterator;
      typedef typename cgt::base::list<typename biterator::_BreadthInfo>::const_iterator const_biiterator;

      typedef typename diterator::_DepthInfo    depth_info;
      typedef typename biterator::_BreadthInfo  breadth_info;

      typedef cgt::shortpath::single::dijkstra::_DijkstraIterator<_TpVertex, _TpEdge>           djiterator;
      typedef cgt::shortpath::single::dijkstra::_DijkstraIterator<_TpVertex, _TpEdge, _TpConst> const_djiterator;

      typedef typename cgt::base::list<typename djiterator::_DijkstraInfo>::iterator       djiiterator;
      typedef typename cgt::base::list<typename djiterator::_DijkstraInfo>::const_iterator const_djiiterator;

      typedef typename djiterator::_DijkstraInfo  dijkstra_info;

      typedef cgt::stconncomp::_SCCIterator<_TpVertex, _TpEdge>           scciterator;
      typedef cgt::stconncomp::_SCCIterator<_TpVertex, _TpEdge, _TpConst> const_scciterator;

      typedef cgt::stconncomp::_GraphSCCComponent<_TpVertex, _TpEdge>  scc;
      typedef cgt::stconncomp::_GraphSCCNode<_TpVertex, _TpEdge>       sccnode;

      typedef cgt::minspantree::prim::_PrimIterator<_TpVertex, _TpEdge>           piterator;
      typedef cgt::minspantree::prim::_PrimIterator<_TpVertex, _TpEdge, _TpConst> const_piterator;

      typedef cgt::minspantree::kruskal::_KruskalIterator<_TpVertex, _TpEdge>           kiterator;
      typedef cgt::minspantree::kruskal::_KruskalIterator<_TpVertex, _TpEdge, _TpConst> const_kiterator;

    public:
      void insert_vertex (const _TpVertex &_vertex) { _insert_vertex (_vertex); }
      void insert_edge (const _TpEdge &_e, const _TpVertex &_v1, const _TpVertex &_v2) { _insert_edge (_e, _v1, _v2); }

    public:
      const node* get_node (const _TpVertex &_vertex) { return _Base::_get_node (_vertex); }
      iterator find (const _TpVertex &_vertex) { return _Base::_find (_vertex); }

    public:
      /*
       * time complexity: O(V)
       */
      void invert () { _Base::_invert (); }

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
      diterator depth_end () { return diterator (NULL); }
      const_diterator depth_begin () const { return const_diterator (_Base::begin (), _Base::begin (), _Base::end ()); }
      const_diterator depth_begin (const iterator& _it) const { return const_diterator (_it, _Base::begin (), _Base::end ()); }
      const_diterator depth_end () const { return const_diterator (NULL); }

      diiterator depth_info_begin (diterator &_it) { return diiterator (_it.info_begin ()); }
      diiterator depth_info_end (diterator &_it) { return diiterator (_it.info_end ()); }
      const_diiterator depth_info_begin (diterator &_it) const { return const_diiterator (_it.info_begin ()); }
      const_diiterator depth_info_end (diterator &_it) const { return const_diiterator (_it.info_end ()); }

      biterator breadth_begin () { return biterator (_Base::begin (), _Base::begin (), _Base::end ()); }
      biterator breadth_begin (const iterator& _it) { return biterator (_it, _Base::begin (), _Base::end ()); }
      biterator breadth_end () { return biterator (NULL); }
      const_biterator breadth_begin () const { return const_biterator (_Base::begin (), _Base::begin (), _Base::end ()); }
      const_biterator breadth_begin (const iterator& _it) const { return const_biterator (_it, _Base::begin (), _Base::end ()); }
      const_biterator breadth_end () const { return const_biterator (NULL); }

      biiterator breadth_info_begin (biterator &_it) { return biiterator (_it.info_begin ()); }
      biiterator breadth_info_end (biterator &_it) { return biiterator (_it.info_end ()); }
      const_biiterator breadth_info_begin (biterator &_it) const { return const_biiterator (_it.info_begin ()); }
      const_biiterator breadth_info_end (biterator &_it) const { return const_biiterator (_it.info_end ()); }

      djiterator dijkstra_begin () { return djiterator (_Base::begin (), _Base::begin (), _Base::end ()); }
      djiterator dijkstra_begin (const iterator& _it) { return djiterator (_it, _Base::begin (), _Base::end ()); }
      djiterator dijkstra_end () { return djiterator (NULL); }
      const_djiterator dijkstra_begin () const { return const_djiterator (_Base::begin (), _Base::begin (), _Base::end ()); }
      const_djiterator dijkstra_begin (const iterator& _it) const { return const_djiterator (_it, _Base::begin (), _Base::end ()); }
      const_djiterator dijkstra_end () const { return const_djiterator (NULL); }

      djiiterator dijkstra_info_begin (djiterator &_it) { return djiiterator (_it.info_begin ()); }
      djiiterator dijkstra_info_end (djiterator &_it) { return djiiterator (_it.info_end ()); }
      const_djiiterator dijkstra_info_begin (djiterator &_it) const { return const_djiiterator (_it.info_begin ()); }
      const_djiiterator dijkstra_info_end (djiterator &_it) const { return const_djiiterator (_it.info_end ()); }

      scciterator stconncomp_begin () { return scciterator (_Base::begin (), _Base::end ()); }
      scciterator stconncomp_end () { return scciterator (); }
      const_scciterator stconncomp_begin () const { return const_scciterator (_Base::begin (), _Base::end ()); }
      const_scciterator stconncomp_end () const { return const_scciterator (); }

      piterator prim_begin () { return piterator (_Base::begin ()); }
      piterator prim_begin (const iterator& _it) { return piterator (_it); }
      piterator prim_end () { return piterator (NULL); }
      const_piterator prim_begin () const { return const_piterator (_Base::begin ()); }
      const_piterator prim_begin (const iterator& _it) const { return const_piterator (_it); }
      const_piterator prim_end () const { return const_piterator (NULL); }

      kiterator kruskal_begin () { return kiterator (_Base::begin (), viterator (_Base::begin ()), viterator (_Base::end ()), _Base::_edge_list.begin (), _Base::_edge_list.end ()); }
      kiterator kruskal_begin (const iterator& _it) { return kiterator (_it, viterator (_Base::begin ()), viterator (_Base::end ()), _Base::_edge_list.begin (), _Base::_edge_list.end ()); }
      kiterator kruskal_end () { return kiterator (NULL); }
      const_kiterator kruskal_begin () const { return const_kiterator (_Base::begin (), viterator (_Base::begin ()), viterator (_Base::end ()), _Base::_edge_list.begin (), _Base::_edge_list.end ()); }
      const_kiterator kruskal_begin (const iterator& _it) const { return const_kiterator (_it, viterator (_Base::begin ()), viterator (_Base::end ()), _Base::_edge_list.begin (), _Base::_edge_list.end ()); }
      const_kiterator kruskal_end () const { return const_kiterator (NULL); }
  };
}

#endif
