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
  add_edge<string, int> (g, 15, "I", "F");
  add_edge<string, int> (g, 16, "F", "D");

  mygraph::scciterator it;
  mygraph::scciterator itEnd = g.sccend ();

  for (it = g.sccbegin (); it != itEnd; ++it)
  {
    mygraph::scc& s = *it;

    mygraph::scc::const_iterator it2End = s.end ();

    cout << "scc:" << endl;

    for (mygraph::scc::const_iterator it2 = s.begin (); it2 != it2End; ++it2)
    {
      const mygraph::node& n = it2->node ();

      cout << "  node: " << n.value () << endl;

      mygraph::adjlist::const_iterator it3End = it2->adjlist ().end ();

      for (mygraph::adjlist::const_iterator it3 = it2->adjlist ().begin (); it3 != it3End; ++it3)
      {
        const mygraph::edge& e = it3->edge ();

        cout << "    edge (" << e.value () << ", " << e.v1 ().value () << ", " << e.v2 ().value () << ")" << endl;
      }
    }
  }

  return 0;
}
