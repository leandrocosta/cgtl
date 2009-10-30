/*
 * directed graph
 *
 * inserting vertexs and edges
 */

#include <assert.h>

#include <string>
#include <sstream>
#include <iostream>
using namespace std;

#include "cgt/graph.h"
using namespace cgt;

#include "util.h"

typedef graph<string, string> mygraph;

int main ()
{
  mygraph g;

  cout << "=== creating graph ===" << endl << endl;

  add_vertex<string, string, _Directed>(g, "A");
  add_vertex<string, string, _Directed>(g, "B");
  add_vertex<string, string, _Directed>(g, "C");

  cout << endl;

  add_edge<string, string, _Directed>(g, "0", "A", "B");
  add_edge<string, string, _Directed>(g, "1", "A", "C");

  add_edge<string, string, _Directed>(g, "2", "B", "C");
  add_edge<string, string, _Directed>(g, "3", "C", "C");

  cout << endl;
  cout << "directed graph: " << (g.is_directed () ? "true":"false") << endl;
  cout << endl;

  cout << "=== printing graph ===" << endl << endl;

  mygraph::const_iterator itn;
  mygraph::const_iterator itnEnd = g.end ();

  for (itn = g.begin (); itn != itnEnd; ++itn)
  {
    const mygraph::node&     n = *itn;
    const mygraph::vertex&  v = n.vertex ();

    cout << "vertex: " << v.value () << endl;

    const mygraph::adjlist &adjList = n.adjlist ();

    mygraph::adjlist::const_iterator itadj;
    mygraph::adjlist::const_iterator itadjEnd = adjList.end ();

    for (itadj = adjList.begin (); itadj != itadjEnd; ++itadj)
    {
      const mygraph::edge&     e   = itadj->edge ();
      const mygraph::vertex&  v1  = e.v1 ();
      const mygraph::vertex&  v2  = e.v2 ();

      cout << "  edge (" << e.value () << ", " << v1.value () << ", " << v2.value () << ")" << endl;
    }
  }

  cout << "--- running dijkstra ---" << endl << endl;

  mygraph::djiterator itdj;
  mygraph::djiterator itdjEnd = g.dijkstra_end ();

  for (itdj = g.dijkstra_begin (); itdj != itdjEnd; ++itdj)
  {
    cout << "for..." << endl;
    const mygraph::node&          n = *itdj;
    const mygraph::vertex&        v = n.vertex ();
    const mygraph::dijkstra_info* i = itdj.info (n);

    if (i)
      cout << "vertex: " << v.value () << ", distance: " << i->distance () << endl;
  }

  return 0;
}
