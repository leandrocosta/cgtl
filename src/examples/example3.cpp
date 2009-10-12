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
  g.insert_vertice ("D");

  g.insert_edge (0, "A", "B");
  g.insert_edge (1, "A", "C");

  g.insert_edge (2, "B", "C");
  g.insert_edge (3, "C", "C");

  cout << endl;
  cout << "directed graph: " << (g.is_directed () ? "true":"false") << endl;
  cout << endl;

  mygraph::vertice_iterator itv;
  mygraph::vertice_iterator itvEnd = g.vertice_end ();

  for (itv = g.vertice_begin (); itv != itvEnd; ++itv)
  {
    const mygraph::vertice& v = *itv;

    cout << "vertice: " << v.value () << endl;
  }

  cout << endl;

  mygraph::edge_iterator ite;
  mygraph::edge_iterator iteEnd = g.edge_end ();

  for (ite = g.edge_begin (); ite != iteEnd; ++ite)
  {
    const mygraph::edge&     e  = *ite;
    const mygraph::vertice&  v1 = e.v1 ();
    const mygraph::vertice&  v2 = e.v2 ();

    cout << "edge (" << e.value () << ", " << v1.value () << ", " << v2.value () << ")" << endl;
  }

  cout << endl;

  cout << "getting node B..." << endl;
  const mygraph::node *n = g.get_node ("B");
  cout << "n.vertice ().value (): " << n->vertice ().value () << endl;

  mygraph::depth_iterator itd = g.depth_begin ();

  return 0;
}
