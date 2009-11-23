/*!
 * \mainpage CGTL
 * \author Leandro Costa
 * \date 2009
 *
 * \section sec_intro Introduction
 *
 * This is a graph template library for general use.
 *
 * \section sec_examples Examples
 *
 * A simple example that explains how to create a graph using CGTL:
 * \code
 * cgt::graph<string, int> g;
 *
 * g.insert_vertex ("A");
 * g.insert_vertex ("B");
 * g.insert_vertex ("C");
 * g.insert_edge (1, "A", "B");
 * g.insert_edge (2, "A", "C");
 * g.insert_edge (3, "B", "C");
 * \endcode
 *
 * Here is an example of how to iterate by vertices using the graph created above:
 *
 * \code
 * cgt::graph<string, int>::const_viterator itEnd = g.vertex_end ();
 * for (cgt::graph<string, int>::const_viterator it; it != itEnd; ++it)
 * {
 *   const cgt::graph<string, int>::vertex& v = *it;
 *   cout << "vertex " << v.value () << endl;
 * }
 * \endcode
 *
 * And here is an example of how to iterate by edges:
 *
 * \code
 * cgt::graph<string, int>::const_eiterator itEnd = g.edge_end ();
 * 
 * for (cgt::graph<string, int>::const_eiterator it; it != itEnd; ++it)
 * {
 *   const cgt::graph<string, int>::edge&   e  = *it;
 *   const cgt::graph<string, int>::vertex& v1 = e.v1 ();
 *   const cgt::graph<string, int>::vertex& v2 = e.v2 ();
 *
 *   cout << "edge (" << e.value () << ", " << v1.value () << ", " << v2.value () << ")" << endl;
 * }
 * \endcode
 *
 * If we are interested in access the neighborhood of each vertex, we can iterate
 * by nodes. A node is a structure that encapsulates the vertex and its adjacency
 * list, and each adjacency has a reference to the other node of the relationship:
 *
 * \code
 * cgt::graph<string, int>::const_iterator itEnd = g.end ();
 * for (cgt::graph<string, int>::const_iterator it = g.begin (); it != itEnd; ++it)
 * {
 *   const cgt::graph<string, int>::node&     n    = *it;
 *   const cgt::graph<string, int>::vertex&   v    = n.vertex ();
 *   const cgt::graph<string, int>::adjlist&  adjs = n.adjlist ();
 *
 *   cout << "vertex " << v.value () << " with " << adjs.size () << " edges" << endl;
 * }
 * \endcode
 *
 * Of course we can use adjlist to iterate by adjancencies, and this way access the
 * whole graph.
 */
