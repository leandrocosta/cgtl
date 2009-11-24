/*
 * CGTL - A graph template library for C++
 * ---------------------------------------
 * Copyright (C) 2009 Leandro Costa
 *
 * This file is part of CGTL.
 *
 * CGTL is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as
 * published by the Free Software Foundation, either version 3 of
 * the License, or (at your option) any later version.
 *
 * CGTL is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with CGTL. If not, see <http://www.gnu.org/licenses/>.
 */

/*!
 * \file cgt/graph.h
 * \brief Contains graph definition. The only file that needs to be included in source code.
 * \author Leandro Costa
 * \date 2009
 *
 * $LastChangedDate$
 * $LastChangedBy$
 * $Revision$
 */

#ifndef __CGTL__CGT_GRAPH_H_
#define __CGTL__CGT_GRAPH_H_

#include "cgt/graph_type.h"
#include "cgt/graph_vertex.h"
#include "cgt/graph_edge.h"
#include "cgt/graph_adjacency.h"
#include "cgt/graph_node.h"
#include "cgt/graph_adjlist.h"
#include "cgt/graph_adjmatrix.h"
#include "cgt/vertex_iterator.h"

#include "cgt/search/depth/depth_iterator.h"
#include "cgt/search/breadth/breadth_iterator.h"
#include "cgt/shortpath/single/dijkstra/dijkstra_iterator.h"
#include "cgt/minspantree/prim/prim_iterator.h"
#include "cgt/minspantree/kruskal/kruskal_iterator.h"

#include "cgt/stconncomp/scc_iterator.h"
#include "cgt/stconncomp/graph_scc_component.h"
#include "cgt/stconncomp/graph_scc_node.h"


/*!
 * \namespace cgt
 * \brief The primary namespace where are defined graph and its main elements.
 * \author Leandro Costa
 * \date 2009
 */

namespace cgt
{
  /*!
   * \class graph
   * \brief The graph class template.
   * \author Leandro Costa
   * \date 2009
   *
   * A graph with vertices of type \b _TpVertex, edges of type \b _TpEdge.
   * The type \b _TpGraphType is used to represent directed (\b _Directed)
   * and indirected (\b _Undirected) graphs.
   */

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

      /** vertex iterator */
      typedef _VertexIterator<_TpVertex, _TpEdge>                                viterator;
      typedef _VertexIterator<_TpVertex, _TpEdge, cgt::base::iterator::_TpConst> const_viterator;

      /** edge iterator */
      typedef typename cgt::base::list<edge>::iterator       eiterator;
      typedef typename cgt::base::list<edge>::const_iterator const_eiterator;

      /** depth-first search iterator */
      typedef cgt::search::depth::_DepthIterator<_TpVertex, _TpEdge>                                 diterator;
      typedef cgt::search::depth::_DepthIterator<_TpVertex, _TpEdge, cgt::base::iterator::_TpConst>  const_diterator;
      typedef typename diterator::_DepthInfo                                                         depth_info;
      typedef typename cgt::base::list<depth_info>::iterator                                         diiterator;
      typedef typename cgt::base::list<depth_info>::const_iterator                                   const_diiterator;

      /** breadth-first search iterator */
      typedef cgt::search::breadth::_BreadthIterator<_TpVertex, _TpEdge>                                 biterator;
      typedef cgt::search::breadth::_BreadthIterator<_TpVertex, _TpEdge, cgt::base::iterator::_TpConst>  const_biterator;
      typedef typename biterator::_BreadthInfo                                                           breadth_info;
      typedef typename cgt::base::list<breadth_info>::iterator                                           biiterator;
      typedef typename cgt::base::list<breadth_info>::const_iterator                                     const_biiterator;

      /** dijkstra iterator */
      typedef cgt::shortpath::single::dijkstra::_DijkstraIterator<_TpVertex, _TpEdge>                                 djiterator;
      typedef cgt::shortpath::single::dijkstra::_DijkstraIterator<_TpVertex, _TpEdge, cgt::base::iterator::_TpConst>  const_djiterator;
      typedef typename djiterator::_Info                                                                              dijkstra_info;
      typedef typename cgt::base::list<dijkstra_info>::iterator                                                       djiiterator;
      typedef typename cgt::base::list<dijkstra_info>::const_iterator                                                 const_djiiterator;

      /** strongly connected components iterator */
      typedef cgt::stconncomp::_SCCIterator<_TpVertex, _TpEdge>                                scciterator;
      typedef cgt::stconncomp::_SCCIterator<_TpVertex, _TpEdge, cgt::base::iterator::_TpConst> const_scciterator;
      typedef cgt::stconncomp::_GraphSCCComponent<_TpVertex, _TpEdge>                          scc;
      typedef cgt::stconncomp::_GraphSCCNode<_TpVertex, _TpEdge>                               sccnode;

      /** prim iterator */
      typedef cgt::minspantree::prim::_PrimIterator<_TpVertex, _TpEdge>                                piterator;
      typedef cgt::minspantree::prim::_PrimIterator<_TpVertex, _TpEdge, cgt::base::iterator::_TpConst> const_piterator;

      /** dijkstra iterator */
      typedef cgt::minspantree::kruskal::_KruskalIterator<_TpVertex, _TpEdge>                                kiterator;
      typedef cgt::minspantree::kruskal::_KruskalIterator<_TpVertex, _TpEdge, cgt::base::iterator::_TpConst> const_kiterator;

    public:
      void insert_vertex (const _TpVertex &_vertex) { _insert_vertex (_vertex); }
      void insert_edge (const _TpEdge &_e, const _TpVertex &_v1, const _TpVertex &_v2) { _insert_edge (_e, _v1, _v2); }

    public:
      const node* get_node (const _TpVertex &_vertex) { return _Base::_get_node (_vertex); }
      iterator find (const _TpVertex &_vertex) { return _Base::_find (_vertex); }

    public:
      /**
       * A method to generate the transpose of graph.
       * Time complexity: O(V).
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

#endif // __CGTL__CGT_GRAPH_H_
