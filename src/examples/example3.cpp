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

  g.insert_vertex ("A");
  g.insert_vertex ("B");
  g.insert_vertex ("C");
  g.insert_vertex ("D");

  g.insert_edge (0, "A", "B");
  g.insert_edge (1, "A", "C");

  g.insert_edge (2, "B", "C");
  g.insert_edge (3, "C", "C");

  cout << endl;
  cout << "directed graph: " << (g.is_directed () ? "true":"false") << endl;
  cout << endl;

  mygraph::const_viterator itv;
  mygraph::const_viterator itvEnd = g.vend ();

  for (itv = g.vbegin (); itv != itvEnd; ++itv)
  {
    const mygraph::vertex& v = *itv;

    cout << "vertex: " << v.value () << endl;
  }

  cout << endl;

  mygraph::const_eiterator ite;
  mygraph::const_eiterator iteEnd = g.eend ();

  for (ite = g.ebegin (); ite != iteEnd; ++ite)
  {
    const mygraph::edge&     e  = *ite;
    const mygraph::vertex&  v1 = e.v1 ();
    const mygraph::vertex&  v2 = e.v2 ();

    cout << "edge (" << e.value () << ", " << v1.value () << ", " << v2.value () << ")" << endl;
  }

  cout << endl;

  cout << "getting node B..." << endl;
  const mygraph::node *n = g.get_node ("B");
  cout << "n.vertex ().value (): " << n->vertex ().value () << endl;

  return 0;
}
