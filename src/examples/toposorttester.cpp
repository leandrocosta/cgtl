#include <string>

/*
#include <assert.h>

#include <sstream>
#include <iostream>
#include <iomanip>
using namespace std;
*/

#include "cgt/graph.h"
using namespace cgt;

#include "examples/util.h"

typedef graph<std::string, int> mygraph;

int main ()
{
  mygraph g;

  cout << "=== creating graph ===" << endl << endl;
  create_graph_3<std::string, int> (g);

  mygraph::tsiterator it;
  mygraph::tsiterator itEnd = g.tsend ();

  for (it = g.tsbegin (); it != itEnd; ++it)
  {
    cout << "node: " << it->vertex ().value () << endl;
    /*
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
    */
  }

  return 0;
}
