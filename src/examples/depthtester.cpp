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
  g.insert_edge (0, "A", "B");

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
