#include <assert.h>

#include <string>
#include <sstream>
#include <iostream>
#include <iomanip>
using namespace std;

#include "cgt/graph.h"
using namespace cgt;

#include "util.h"

typedef graph<string, int> mygraph;

int main ()
{
  mygraph g;

  cout << "=== creating graph ===" << endl << endl;
  create_graph_1<string, int> (g);
  add_edge<string, int> (g, 9, "B", "C");
  add_edge<string, int> (g, 10, "C", "A");
  add_edge<string, int> (g, 11, "H", "E");
  add_edge<string, int> (g, 12, "H", "J");
  add_edge<string, int> (g, 13, "J", "G");
  add_edge<string, int> (g, 14, "G", "E");

  mygraph::scciterator it;
  mygraph::scciterator itEnd = g.stconncomp_end ();

  for (it = g.stconncomp_begin (); it != itEnd; ++it)
  {
//    cout << "first node of SCC [" << &(*it) << "], front [" << it->front () << "]" << endl;
//    cout << "first node of SCC: " << it->front ()->vertex ().value () << endl;

    mygraph::scc& s = *it;

    mygraph::scc::iterator it2    = s.begin ();
    mygraph::scc::iterator it2End = s.end ();

    cout << "scc: " << it2->vertex ().value ();

    for (++it2; it2 != it2End; ++it2)
    {
      mygraph::sccnode& n = *it2;
      cout << ", " << n.vertex ().value ();
    }

    cout << endl;
  }

  return 0;
}
