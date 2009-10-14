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
  g.insert_vertex ("E");
  g.insert_vertex ("F");
  g.insert_vertex ("G");
  g.insert_vertex ("H");
  g.insert_vertex ("I");
  g.insert_vertex ("J");
  g.insert_edge (0, "A", "B");
  g.insert_edge (1, "A", "C");
  g.insert_edge (2, "C", "E");
  g.insert_edge (3, "D", "E");
  g.insert_edge (4, "D", "F");

  g.insert_edge (5, "C", "G");
  g.insert_edge (6, "E", "H");
  g.insert_edge (7, "D", "I");
  g.insert_edge (8, "C", "J");

  mygraph::depth_iterator itd;
  mygraph::depth_iterator itdEnd = g.depth_end ();

  for (itd = g.depth_begin (); itd != itdEnd; ++itd)
  {
    mygraph::node&    n = *itd;
    mygraph::vertex&  v = n.vertex ();
    cout << "itd: " << v.value () << endl;
  }

/*
  mygraph::depth_iterator itd     = g.depth_begin ();
  mygraph::depth_iterator itdEnd  = g.depth_end ();

  if (itd != itdEnd)
  {
    mygraph::node&    n = *itd;
    mygraph::vertex&  v = n.vertex ();
    cout << "depth_begin: " << v.value () << endl;
    ++itd;
  }
*/

  return 0;
}
