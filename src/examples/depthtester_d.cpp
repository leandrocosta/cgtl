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

  add_vertex<string, int, _Directed>(g, "A");
  add_vertex<string, int, _Directed>(g, "B");
  add_vertex<string, int, _Directed>(g, "C");
  add_vertex<string, int, _Directed>(g, "D");
  add_vertex<string, int, _Directed>(g, "E");
  add_vertex<string, int, _Directed>(g, "F");
  add_vertex<string, int, _Directed>(g, "G");
  add_vertex<string, int, _Directed>(g, "H");
  add_vertex<string, int, _Directed>(g, "I");
  add_vertex<string, int, _Directed>(g, "J");

  cout << endl;

  add_edge<string, int, _Directed>(g, 0, "A", "B");
  add_edge<string, int, _Directed>(g, 1, "A", "C");
  add_edge<string, int, _Directed>(g, 2, "C", "E");
  add_edge<string, int, _Directed>(g, 3, "D", "E");
  add_edge<string, int, _Directed>(g, 4, "D", "F");

  add_edge<string, int, _Directed>(g, 5, "C", "G");
  add_edge<string, int, _Directed>(g, 6, "E", "H");
  add_edge<string, int, _Directed>(g, 7, "D", "I");
  add_edge<string, int, _Directed>(g, 8, "C", "J");

  cout << endl;
  cout << "=== depth-first search from vertex E ===" << endl << endl;

  mygraph::depth_iterator itd;
  mygraph::depth_iterator itdEnd = g.depth_end ();

  for (itd = g.depth_begin (g.find ("E")); itd != itdEnd; ++itd)
  {
    const mygraph::node&       n = *itd;
    const mygraph::vertex&     v = n.vertex ();
    const mygraph::depth_info* i = itd.info (n);

    cout << "itd: " << v.value () <<  ", discovery: " << setw (2) << i->discovery () << ", parent: " << (i->parent () ? i->parent ()->vertex ().value ():"-") << endl;
  }

  cout << endl;
  cout << "=== show depth-first search info for all vertices ===" << endl << endl;

  mygraph::const_iterator itn;
  mygraph::const_iterator itnEnd = g.end ();

  for (itn = g.begin (); itn != itnEnd; ++itn)
  {
    const mygraph::node&   n = *itn;
    const mygraph::vertex& v = n.vertex ();
    const mygraph::depth_info* i = itd.info (n);

    cout << "node: " << v.value () << ", parent: " << (i->parent () ? i->parent ()->vertex ().value ():"-") << ", discovery: " << setw (2) << i->discovery () << ", finish: " << setw (2) << i->finish () << endl;
  }

  cout << endl;

  return 0;
}
