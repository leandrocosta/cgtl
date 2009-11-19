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
  create_graph_2<string, int, _Undirected> (g);

  cout << "=== prim from vertex E ===" << endl << endl;

  mygraph::piterator itp;
  mygraph::piterator itpEnd = g.prim_end ();

  for (itp = g.prim_begin (); itp != itpEnd; ++itp)
  {
//    cout << "edge: " << itp->value () << endl;
      const mygraph::edge&     e   = *itp;
      const mygraph::vertex&  v1  = e.v1 ();
      const mygraph::vertex&  v2  = e.v2 ();

    cout << "edge (" << e.value () << ", " << v1.value () << ", " << v2.value () << ")" << endl;
  }

  /*

  for (itd = g.dijkstra_begin (g.find ("E")); itd != itdEnd; ++itd)
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
  mygraph::const_djiiterator itEnd = g.dijkstra_info_end (itd);

  for (it = g.dijkstra_info_begin (itd); it != itEnd; ++it)
  {
    const mygraph::dijkstra_info& i = *it;

//    cout << "vertex: " << i.node ().vertex ().value () << ", distance: " << i.distance () << endl;
    cout << "vertex: " << i.node ().vertex ().value () << ", distance: " << i.distance () << ", previous: " << (i.previous () ? i.previous ()->vertex ().value ():"-") << endl;
  }

  cout << endl;
  */

  return 0;
}
