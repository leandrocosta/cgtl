/*
 * directed graph
 *
 * inserting vertices and edges
 */

#include <assert.h>

#include <string>
#include <sstream>
#include <iostream>
using namespace std;

#include "cgt/graph.h"
using namespace cgt;

typedef graph<string, int> mygraph;

int main ()
{
  mygraph g;

  g.insert_vertice ("A");
  g.insert_vertice ("B");
  g.insert_vertice ("C");

  g.insert_edge (0, "A", "B");
  g.insert_edge (1, "A", "C");

  g.insert_edge (2, "B", "C");
  g.insert_edge (3, "C", "C");

  cout << endl;
  cout << "directed graph: " << (g.is_directed () ? "true":"false") << endl;
  cout << endl;

  mygraph::const_iterator itn;
  mygraph::const_iterator itnEnd = g.end ();

  for (itn = g.begin (); itn != itnEnd; ++itn)
  {
    const mygraph::node&     n = *itn;
    const mygraph::vertice&  v = n.vertice ();

    cout << "vertice: " << v.value () << endl;

    const mygraph::adjlist &adjList = n.get_adj_list ();

    mygraph::adjlist::const_iterator itadj;
    mygraph::adjlist::const_iterator itadjEnd = adjList.end ();

    for (itadj = adjList.begin (); itadj != itadjEnd; ++itadj)
    {
      const mygraph::edge&     e   = itadj->get_edge ();
      const mygraph::vertice&  v1  = e.v1 ();
      const mygraph::vertice&  v2  = e.v2 ();

      cout << "  edge (" << e.value () << ", " << v1.value () << ", " << v2.value () << ")" << endl;
    }
  }

  return 0;
}
