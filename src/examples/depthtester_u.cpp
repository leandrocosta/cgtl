#include <assert.h>

#include <string>
#include <sstream>
#include <iostream>
#include <iomanip>
using namespace std;

#include "cgt/graph.h"
using namespace cgt;

#include "util.h"

typedef graph<string, int, _Undirected> mygraph;

int main ()
{
  mygraph g;

  cout << "=== creating graph ===" << endl << endl;

  add_vertex<string, int, _Undirected>(g, "A");
  add_vertex<string, int, _Undirected>(g, "B");
  add_vertex<string, int, _Undirected>(g, "C");
  add_vertex<string, int, _Undirected>(g, "D");
  add_vertex<string, int, _Undirected>(g, "E");
  add_vertex<string, int, _Undirected>(g, "F");
  add_vertex<string, int, _Undirected>(g, "G");
  add_vertex<string, int, _Undirected>(g, "H");
  add_vertex<string, int, _Undirected>(g, "I");
  add_vertex<string, int, _Undirected>(g, "J");

  cout << endl;

  add_edge<string, int, _Undirected>(g, 0, "A", "B");
  add_edge<string, int, _Undirected>(g, 1, "A", "C");
  add_edge<string, int, _Undirected>(g, 2, "C", "E");
  add_edge<string, int, _Undirected>(g, 3, "D", "E");
  add_edge<string, int, _Undirected>(g, 4, "D", "F");

  add_edge<string, int, _Undirected>(g, 5, "C", "G");
  add_edge<string, int, _Undirected>(g, 6, "E", "H");
  add_edge<string, int, _Undirected>(g, 7, "D", "I");
  add_edge<string, int, _Undirected>(g, 8, "C", "J");

  cout << endl;
  cout << "=== depth-first search from vertex E ===" << endl << endl;

  mygraph::diterator itd;
  mygraph::diterator itdEnd = g.depth_end ();

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
    const mygraph::node&       n = *itn;
    const mygraph::vertex&     v = n.vertex ();
    const mygraph::depth_info* i = itd.info (n);

    cout << "node: " << v.value () << ", parent: " << (i->parent () ? i->parent ()->vertex ().value ():"-") << ", discovery: " << setw (2) << i->discovery () << ", finish: " << setw (2) << i->finish () << endl;
  }

  cout << endl;
  cout << "=== show the same using depth info iterator ===" << endl << endl;

  mygraph::const_diiterator it;
  mygraph::const_diiterator itEnd = g.depth_info_end (itd);

  for (it = g.depth_info_begin (itd); it != itEnd; ++it)
  {
    const mygraph::depth_info& i = *it;

    cout << "node: " << i.node ()->vertex ().value () << ", parent: " << (i.parent () ? i.parent ()->vertex ().value ():"-") << ", discovery: " << setw (2) << i.discovery () << ", finish: " << setw (2) << i.finish () << endl;
  }

  return 0;
}
