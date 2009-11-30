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

  cout << "=== breadth-first search from vertex E ===" << endl << endl;

  mygraph::iterator itE = g.find ("E");
  mygraph::const_biterator itd = g.bbegin (itE);
  mygraph::const_biterator itdEnd = g.bend ();

//  for (itd = g.bbegin (g.find ("E")); itd != itdEnd; ++itd)
  for (; itd != itdEnd; ++itd)
  {
    const mygraph::node&       n = *itd;
    const mygraph::vertex&     v = n.vertex ();
    const mygraph::breadth_info* i = itd.info (n);

    cout << "itd: " << v.value () <<  ", discovery: " << setw (2) << i->discovery () << ", parent: " << (i->parent () ? i->parent ()->vertex ().value ():"-") << endl;
  }

  cout << endl;
  cout << "=== show breadth-first search info for all vertices ===" << endl << endl;

  mygraph::const_iterator itn;
  mygraph::const_iterator itnEnd = g.end ();

  for (itn = g.begin (); itn != itnEnd; ++itn)
  {
    const mygraph::node&   n = *itn;
    const mygraph::vertex& v = n.vertex ();
    const mygraph::breadth_info* i = itd.info (n);

    cout << "node: " << v.value ();
    if (i)
    {
      cout << ", parent: " << (i->parent () ? i->parent ()->vertex ().value ():"-");
      cout << ", discovery: " << setw (2) << i->discovery ();
      cout << ", finish: " << setw (2) << i->finish () << endl;
    }
    else
      cout << ", info is null" << endl;
  }

  cout << endl;
  cout << "=== show the same using breadth info iterator ===" << endl << endl;

  mygraph::const_biiterator it;
  mygraph::const_biiterator itEnd = g.biend (itd);

  for (it = g.bibegin (itd); it != itEnd; ++it)
  {
    const mygraph::breadth_info& i = *it;

    cout << "node: " << i.node ().vertex ().value () << ", parent: " << (i.parent () ? i.parent ()->vertex ().value ():"-") << ", discovery: " << setw (2) << i.discovery () << ", finish: " << setw (2) << i.finish () << endl;
  }

  cout << endl;

  return 0;
}
