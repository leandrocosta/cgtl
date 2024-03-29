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

#ifdef CGTL_DO_NOT_USE_STL
#include "cgt/vertex_iterator.h"
#else
#include "cgt/vertex_stl_iterator.h"
#endif

#include "cgt/search/depth/depth_iterator.h"
#include "cgt/search/breadth/breadth_iterator.h"
#include "cgt/shortpath/single/bellford/bellford_iterator.h"
#include "cgt/shortpath/single/dijkstra/dijkstra_iterator.h"
#include "cgt/minspantree/prim/prim_iterator.h"
#include "cgt/minspantree/kruskal/kruskal_iterator.h"

#include "cgt/stconncomp/scc_iterator.h"
#include "cgt/stconncomp/graph_scc_component.h"
#include "cgt/stconncomp/graph_scc_node.h"

#include "cgt/toposort/toposort_iterator.h"


/*!
 * \namespace cgt
 * \brief The primary namespace where are defined graph and its main elements.
 * \author Leandro Costa
 * \date 2009
 */

namespace cgt
{
	template<typename _TpVertex, typename _TpEdge, typename _TpGraphType>
		class _graph_base : protected _GraphAdjMatrix<_TpVertex, _TpEdge, _TpGraphType>
	{
		private:
			typedef _GraphAdjMatrix<_TpVertex, _TpEdge, _TpGraphType> _Base;

		public:
			typedef _GraphNode<_TpVertex, _TpEdge>    node;
			typedef _GraphVertex<_TpVertex>           vertex;
			typedef _GraphEdge<_TpVertex, _TpEdge>    edge;

			typedef typename _Base::iterator          iterator;
			typedef typename _Base::const_iterator    const_iterator;

		public:
			iterator insert_vertex (const _TpVertex &_vertex) { return _insert_vertex (_vertex); }
			const node* get_node (const _TpVertex &_vertex) { return _Base::_get_node (_vertex); }
			iterator find (const _TpVertex &_vertex) { return _Base::_find (_vertex); }

			/**
			 * A method to generate the transpose of graph.
			 * Time complexity: O(V).
			 */
			void invert () { _Base::_invert (); }

			const bool is_directed () const { return _Base::_is_directed (); }
			const bool is_undirected () const { return _Base::_is_undirected (); }


			/** node iterator */
			iterator begin () { return _Base::begin (); }
			iterator end () { return _Base::end (); }
			const_iterator begin () const { return _Base::begin (); }
			const_iterator end () const { return _Base::end (); }

			/** vertex iterator */
#ifdef CGTL_DO_NOT_USE_STL
			typedef _VertexIterator<_TpVertex, _TpEdge>                                viterator;
			typedef _VertexIterator<_TpVertex, _TpEdge, cgt::base::iterator::_TpConst> const_viterator;
#else
			typedef _VertexSTLIterator<_TpVertex, _TpEdge>    	viterator;
			typedef _VertexSTLConstIterator<_TpVertex, _TpEdge>	const_viterator;
#endif

			viterator vbegin () { return viterator (_Base::begin ()); }
			viterator vend () { return viterator (_Base::end ()); }
			const_viterator vbegin () const { return const_viterator (_Base::begin ()); }
			const_viterator vend () const { return const_viterator (_Base::end ()); }


			/** edge iterator */
#ifdef CGTL_DO_NOT_USE_STL
			typedef typename cgt::base::list<edge>::iterator       eiterator;
			typedef typename cgt::base::list<edge>::const_iterator const_eiterator;
#else
			typedef typename std::list<edge>::iterator       eiterator;
			typedef typename std::list<edge>::const_iterator const_eiterator;
#endif

			eiterator ebegin () { return eiterator (_Base::_edgeList.begin ()); }
			eiterator eend () { return eiterator (_Base::_edgeList.end ()); }
			const_eiterator ebegin () const { return const_eiterator (_Base::_edgeList.begin ()); }
			const_eiterator eend () const { return const_eiterator (_Base::_edgeList.end ()); }


			/** breadth-first search iterator */
			typedef cgt::search::breadth::_BreadthIterator<_TpVertex, _TpEdge>                                 biterator;
			typedef cgt::search::breadth::_BreadthIterator<_TpVertex, _TpEdge, cgt::base::iterator::_TpConst>  const_biterator;
			typedef typename biterator::_BreadthInfo                                                           breadth_info;
#ifdef CGTL_DO_NOT_USE_STL
			typedef typename cgt::base::list<breadth_info>::iterator                                           biiterator;
			typedef typename cgt::base::list<breadth_info>::const_iterator                                     const_biiterator;
#else
			typedef typename std::list<breadth_info>::iterator                                           biiterator;
			typedef typename std::list<breadth_info>::const_iterator                                     const_biiterator;
#endif

			biterator bbegin () { return biterator (_Base::begin (), _Base::begin (), _Base::end ()); }
			biterator bbegin (const iterator& _it) { return biterator (_it, _Base::begin (), _Base::end ()); }
			biterator bend () { return biterator (NULL); }
			const_biterator bbegin () const { return const_biterator (_Base::begin (), _Base::begin (), _Base::end ()); }
			const_biterator bbegin (const iterator& _it) const { return const_biterator (_it, _Base::begin (), _Base::end ()); }
			const_biterator bend () const { return const_biterator (NULL); }

			biiterator bibegin (biterator &_it) { return biiterator (_it.info_begin ()); }
			biiterator biend (biterator &_it) { return biiterator (_it.info_end ()); }
			const_biiterator bibegin (biterator &_it) const { return const_biiterator (_it.info_begin ()); }
			const_biiterator bibegin (const_biterator &_it) const { return const_biiterator (_it.info_begin ()); }
			const_biiterator biend (biterator &_it) const { return const_biiterator (_it.info_end ()); }
			const_biiterator biend (const_biterator &_it) const { return const_biiterator (_it.info_end ()); }


			/** depth-first search iterator */
			typedef cgt::search::depth::_DepthIterator<_TpVertex, _TpEdge>                                 diterator;
			typedef cgt::search::depth::_DepthIterator<_TpVertex, _TpEdge, cgt::base::iterator::_TpConst>  const_diterator;
			typedef typename diterator::_DepthInfo                                                         depth_info;
#ifdef CGTL_DO_NOT_USE_STL
			typedef typename cgt::base::list<depth_info>::iterator                                         diiterator;
			typedef typename cgt::base::list<depth_info>::const_iterator                                   const_diiterator;
#else
			typedef typename std::list<depth_info>::iterator                                         diiterator;
			typedef typename std::list<depth_info>::const_iterator                                   const_diiterator;
#endif

			diterator dbegin () { return diterator (_Base::begin (), _Base::begin (), _Base::end ()); }
			diterator dbegin (const iterator& _it) { return diterator (_it, _Base::begin (), _Base::end ()); }
			diterator dend () { return diterator (NULL); }
			const_diterator dbegin () const { return const_diterator (_Base::begin (), _Base::begin (), _Base::end ()); }
			const_diterator dbegin (const iterator& _it) const { return const_diterator (_it, _Base::begin (), _Base::end ()); }
			const_diterator dend () const { return const_diterator (NULL); }

			diiterator dibegin (diterator &_it) { return diiterator (_it.info_begin ()); }
			diiterator diend (diterator &_it) { return diiterator (_it.info_end ()); }
			const_diiterator dibegin (diterator &_it) const { return const_diiterator (_it.info_begin ()); }
			const_diiterator diend (diterator &_it) const { return const_diiterator (_it.info_end ()); }


			/** strongly connected components iterator */
			typedef cgt::stconncomp::_SCCIterator<_TpVertex, _TpEdge>                                scciterator;
			typedef cgt::stconncomp::_SCCIterator<_TpVertex, _TpEdge, cgt::base::iterator::_TpConst> const_scciterator;
			typedef cgt::stconncomp::_GraphSCCComponent<_TpVertex, _TpEdge>                          scc;
			typedef cgt::stconncomp::_GraphSCCNode<_TpVertex, _TpEdge>                               sccnode;

			scciterator sccbegin () { return scciterator (_Base::begin (), _Base::end ()); }
			scciterator sccend () { return scciterator (); }
			const_scciterator sccbegin () const { return const_scciterator (_Base::begin (), _Base::end ()); }
			const_scciterator sccend () const { return const_scciterator (); }

			/** prim iterator */
			typedef cgt::minspantree::prim::_PrimIterator<_TpVertex, _TpEdge>                                piterator;
			typedef cgt::minspantree::prim::_PrimIterator<_TpVertex, _TpEdge, cgt::base::iterator::_TpConst> const_piterator;

			piterator pbegin () { return piterator (_Base::begin ()); }
			piterator pbegin (const iterator& _it) { return piterator (_it); }
			piterator pend () { return piterator (NULL); }
			const_piterator pbegin () const { return const_piterator (_Base::begin ()); }
			const_piterator pbegin (const iterator& _it) const { return const_piterator (_it); }
			const_piterator pend () const { return const_piterator (NULL); }


			/** kruskal iterator */
			typedef cgt::minspantree::kruskal::_KruskalIterator<_TpVertex, _TpEdge>                                kiterator;
			typedef cgt::minspantree::kruskal::_KruskalIterator<_TpVertex, _TpEdge, cgt::base::iterator::_TpConst> const_kiterator;

			kiterator kbegin () { return kiterator (_Base::begin (), viterator (_Base::begin ()), viterator (_Base::end ()), _Base::_edgeList.begin (), _Base::_edgeList.end ()); }
			kiterator kbegin (const iterator& _it) { return kiterator (_it, viterator (_Base::begin ()), viterator (_Base::end ()), _Base::_edgeList.begin (), _Base::_edgeList.end ()); }
			kiterator kend () { return kiterator (NULL); }
			const_kiterator kbegin () const { return const_kiterator (_Base::begin (), viterator (_Base::begin ()), viterator (_Base::end ()), _Base::_edgeList.begin (), _Base::_edgeList.end ()); }
			const_kiterator kbegin (const iterator& _it) const { return const_kiterator (_it, viterator (_Base::begin ()), viterator (_Base::end ()), _Base::_edgeList.begin (), _Base::_edgeList.end ()); }
			const_kiterator kend () const { return const_kiterator (NULL); }


			/** topological sort iterator */
			typedef cgt::toposort::_ToposortIterator<_TpVertex, _TpEdge>                                tsiterator;
			typedef cgt::toposort::_ToposortIterator<_TpVertex, _TpEdge, cgt::base::iterator::_TpConst> const_tsiterator;

			tsiterator tsbegin () { return tsiterator (_Base::begin (), _Base::end ()); }
			tsiterator tsbegin (const iterator& _it) { return tsiterator (_it); }
			tsiterator tsend () { return tsiterator (); }
			const_tsiterator tsbegin () const { return const_tsiterator (_Base::begin (), _Base::end ()); }
			const_tsiterator tsbegin (const iterator& _it) const { return const_tsiterator (_it); }
			const_tsiterator tsend () const { return const_tsiterator (); }
	};


	/*!
	 * \class graph
	 * \brief The graph class template.
	 * \author Leandro Costa
	 * \date 2009
	 *
	 * A graph with vertices of type \b _TpVertex, edges of type \b _TpEdge.
	 * The type \b _TpGraphType is used to represent directed (\b _Directed)
	 * and indirected (\b _Undirected) graphs.
	 *
	 * \code
	 *  _______________________________________________________________________________________________________________________________________________________________
	 * | graph                                                                                                                                                         |
	 * |_______________________________________________________________________________________________________________________________________________________________|
	 * |  ___________________________________________________________________________________________________________________________________________________________  |
	 * | | _GraphNodeList                                                                                                                                            | |
	 * | |___________________________________________________________________________________________________________________________________________________________| |
	 * | |               __________________________________________________________________      __________________________________________________________________  | |
	 * | | _GraphNode*  | _GraphNode                                                       |    | _GraphNode                                                       | | |
	 * | | _GraphNode*  |__________________________________________________________________| -> |__________________________________________________________________| | |
	 * | | size_t       |  ______________                                                  |    |  ______________                                                  | | |
	 * | |              | | _GraphVertex |                                                 |    | | _GraphVertex |                                                 | | |
	 * | |              | |______________|                                                 |    | |______________|                                                 | | |
	 * | |              |                                                                  |    |                                                                  | | |
	 * | |              |  ______________________________________________________________  |    |  ______________________________________________________________  | | |
	 * | |              | | _GraphAdjList                                                | |    | | _GraphAdjList                                                | | | |
	 * | |              | |______________________________________________________________| |    | |______________________________________________________________| | | |
	 * | |              | |                    _________________      _________________  | |    | |                    _________________      _________________  | | | |
	 * | |              | | _GraphAdjacency*  | _GraphAdjacency |    | _GraphAdjacency | | |    | | _GraphAdjacency*  | _GraphAdjacency |    | _GraphAdjacency | | | | |
	 * | |              | | _GraphAdjacency*  |_________________| -> |_________________| | |    | | _GraphAdjacency*  |_________________| -> |_________________| | | | |
	 * | |              | | size_t            |                 |    |                 | | |    | | size_t            |                 |    |                 | | | | |
	 * | |              | |                   |   _GraphEdge&   |    |   _GraphEdge&   | | |    | |                   |   _GraphEdge&   |    |   _GraphEdge&   | | | | |
	 * | |              | |                   |   _GraphNode&   | <- |   _GraphNode&   | | |    | |                   |   _GraphNode&   | <- |   _GraphNode&   | | | | |
	 * | |              | |                   |_________________|    |_________________| | |    | |                   |_________________|    |_________________| | | | |
	 * | |              | |______________________________________________________________| |    | |______________________________________________________________| | | |
	 * | |              |                                                                  |    |                                                                  | | |
	 * | |              |  ______________________________________________________________  |    |  ______________________________________________________________  | | |
	 * | |              | | _GraphAdjList                                                | |    | | _GraphAdjList                                                | | | |
	 * | |              | |______________________________________________________________| |    | |______________________________________________________________| | | |
	 * | |              | |                    _________________      _________________  | |    | |                    _________________      _________________  | | | |
	 * | |              | | _GraphAdjacency*  | _GraphAdjacency |    | _GraphAdjacency | | |    | | _GraphAdjacency*  | _GraphAdjacency |    | _GraphAdjacency | | | | |
	 * | |              | | _GraphAdjacency*  |_________________| -> |_________________| | |    | | _GraphAdjacency*  |_________________| -> |_________________| | | | |
	 * | |              | | size_t            |                 |    |                 | | |    | | size_t            |                 |    |                 | | | | |
	 * | |              | |                   |   _GraphEdge&   |    |   _GraphEdge&   | | |    | |                   |   _GraphEdge&   |    |   _GraphEdge&   | | | | |
	 * | |              | |                   |   _GraphNode&   | <- |   _GraphNode&   | | |    | |                   |   _GraphNode&   | <- |   _GraphNode&   | | | | |
	 * | |              | |                   |_________________|    |_________________| | |    | |                   |_________________|    |_________________| | | | |
	 * | |              | |______________________________________________________________| | <- | |______________________________________________________________| | | |
	 * | |              |__________________________________________________________________|    |__________________________________________________________________| | |
	 * | |___________________________________________________________________________________________________________________________________________________________| |
	 * |                                                                                                                                                               |
	 * |  __________________________________________________________________________                                                                                   |
	 * | | _GraphEdgeList                                                           |                                                                                  |
	 * | |__________________________________________________________________________|                                                                                  |
	 * | |               _______________      _______________      _______________  |                                                                                  |
	 * | | _GraphEdge*  | _GraphEdge    |    | _GraphEdge    |    | _GraphEdge    | |                                                                                  |
	 * | | _GraphEdge*  |_______________| -> |_______________| -> |_______________| |                                                                                  |
	 * | | size_t       |               |    |               |    |               | |                                                                                  |
	 * | |              | _TpEdge       |    | _TpEdge       |    | _TpEdge       | |                                                                                  |
	 * | |              | _GraphVertex& |    | _GraphVertex& |    | _GraphVertex& | |                                                                                  |
	 * | |              | _GraphVertex& | <- | _GraphVertex& | <- | _GraphVertex& | |                                                                                  |
	 * | |              |_______________|    |_______________|    |_______________| |                                                                                  |
	 * | |__________________________________________________________________________|                                                                                  |
	 * |                                                                                                                                                               |
	 * |                                                                                                                                                               |
	 * |  _TpGraphType                                                                                                                                                 |
	 * |_______________________________________________________________________________________________________________________________________________________________|
	 *
	 * \endcode
	 */

	template<typename _TpVertex, typename _TpEdge = void, typename _TpGraphType = _Directed>
		class graph : public _graph_base<_TpVertex, _TpEdge, _TpGraphType>
	{
		private:
			typedef _graph_base<_TpVertex, _TpEdge, _TpGraphType> _Base;

		public:
			typedef _GraphEdge<_TpVertex, _TpEdge>    edge;
			typedef _GraphAdjList<_TpVertex, _TpEdge> adjlist;

		public:
			void insert_edge (const _TpEdge &_e, const _TpVertex &_v1, const _TpVertex &_v2) { _insert_edge (_e, _v1, _v2); }
			void insert_edge (const _TpEdge& _e, typename _Base::iterator& _it_v1, typename _Base::iterator& _it_v2) { _insert_edge (_e, _it_v1, _it_v2); }


		public:
			/** bellman-ford iterator */
			typedef cgt::shortpath::single::bellford::_BellfordIterator<_TpVertex, _TpEdge>	bfiterator;



			bfiterator bfbegin (const typename _Base::iterator& _it) { return bfiterator (_it, _Base::begin (), _Base::end (), _Base::_edgeList, _Base::size ()); }


			/** dijkstra iterator */
			typedef cgt::shortpath::single::dijkstra::_DijkstraIterator<_TpVertex, _TpEdge>                                 djiterator;
			typedef cgt::shortpath::single::dijkstra::_DijkstraIterator<_TpVertex, _TpEdge, cgt::base::iterator::_TpConst>  const_djiterator;
			typedef typename djiterator::_Info                                                                              dijkstra_info;
#ifdef CGTL_DO_NOT_USE_STL
			typedef typename cgt::base::list<dijkstra_info>::iterator                                                       djiiterator;
			typedef typename cgt::base::list<dijkstra_info>::const_iterator                                                 const_djiiterator;
#else
			typedef typename std::list<dijkstra_info>::iterator                                                       djiiterator;
			typedef typename std::list<dijkstra_info>::const_iterator                                                 const_djiiterator;
#endif

			djiterator djbegin () { return djiterator (_Base::begin (), _Base::begin (), _Base::end ()); }
			djiterator djbegin (const typename _Base::iterator& _it) { return djiterator (_it, _Base::begin (), _Base::end ()); }
			djiterator djend () { return djiterator (NULL); }
			const_djiterator djbegin () const { return const_djiterator (_Base::begin (), _Base::begin (), _Base::end ()); }
			const_djiterator djbegin (const typename _Base::iterator& _it) const { return const_djiterator (_it, _Base::begin (), _Base::end ()); }
			const_djiterator djend () const { return const_djiterator (NULL); }

			djiiterator djibegin (djiterator &_it) { return djiiterator (_it.info_begin ()); }
			djiiterator djiend (djiterator &_it) { return djiiterator (_it.info_end ()); }
			const_djiiterator djibegin (djiterator &_it) const { return const_djiiterator (_it.info_begin ()); }
			const_djiiterator djiend (djiterator &_it) const { return const_djiiterator (_it.info_end ()); }
	};


	/*
	 * A simple graph, with no type for edges
	 */

	template<typename _TpVertex, typename _TpGraphType>
		class graph<_TpVertex, void, _TpGraphType> : public _graph_base<_TpVertex, void, _TpGraphType>
		{
			private:
				typedef _GraphAdjMatrix<_TpVertex, void, _TpGraphType> _Base;

			public:
				typedef _GraphEdge<_TpVertex, void>    edge;
				typedef _GraphNode<_TpVertex, void>    node;
				typedef _GraphAdjList<_TpVertex, void> adjlist;

			public:
				void insert_edge (const _TpVertex &_v1, const _TpVertex &_v2) { _insert_edge (_v1, _v2); }
				void insert_edge (typename _Base::iterator& _it_v1, typename _Base::iterator& _it_v2) { _insert_edge (_it_v1, _it_v2); }
		};
}

#endif // __CGTL__CGT_GRAPH_H_
