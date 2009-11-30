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
  create_graph_1<string, int, _Undirected> (g);

  cout << "=== dijkstra from vertex E ===" << endl << endl;

  mygraph::djiterator itd;
  mygraph::djiterator itdEnd = g.djend ();

  for (itd = g.djbegin (g.find ("E")); itd != itdEnd; ++itd)
  {
    const mygraph::node&       n = *itd;
    const mygraph::vertex&     v = n.vertex ();

    const mygraph::dijkstra_info* i = itd.info (n);

//    cout << "vertex: " << v.value () << ", distance: " << i->distance () << endl;
    cout << "vertex: " << v.value () << ", distance: " << i->distance () << ", previous: " << (i->previous () ? i->previous ()->vertex ().value ():"-") << endl;
  }

  cout << endl;
  cout << "=== show dijkstra info for all vertices ===" << endl << endl;

  mygraph::const_iterator itn;
  mygraph::const_iterator itnEnd = g.end ();

  for (itn = g.begin (); itn != itnEnd; ++itn)
  {
    const mygraph::node&   n = *itn;
    const mygraph::vertex& v = n.vertex ();
    const mygraph::dijkstra_info* i = itd.info (n);

//    cout << "vertex: " << v.value () << ", distance: " << i->distance () << endl;
    cout << "vertex: " << v.value () << ", distance: " << i->distance () << ", previous: " << (i->previous () ? i->previous ()->vertex ().value ():"-") << endl;
  }

  cout << endl;
  cout << "=== show the same using dijkstra info iterator ===" << endl << endl;

  mygraph::const_djiiterator it;
  mygraph::const_djiiterator itEnd = g.djiend (itd);

  for (it = g.djibegin (itd); it != itEnd; ++it)
  {
    const mygraph::dijkstra_info& i = *it;

//    cout << "vertex: " << i.node ().vertex ().value () << ", distance: " << i.distance () << endl;
    cout << "vertex: " << i.node ().vertex ().value () << ", distance: " << i.distance () << ", previous: " << (i.previous () ? i.previous ()->vertex ().value ():"-") << endl;
  }

  cout << endl;

  return 0;
}
