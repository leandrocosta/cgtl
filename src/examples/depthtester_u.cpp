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

  cout << "=== depth-first search from vertex E ===" << endl << endl;

  mygraph::diterator itd;
  mygraph::diterator itdEnd = g.dend ();

  for (itd = g.dbegin (g.find ("E")); itd != itdEnd; ++itd)
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
  cout << "=== show the same using depth info iterator ===" << endl << endl;

  mygraph::const_diiterator it;
  mygraph::const_diiterator itEnd = g.diend (itd);

  for (it = g.dibegin (itd); it != itEnd; ++it)
  {
    const mygraph::depth_info& i = *it;

    cout << "node: " << i.node ().vertex ().value () << ", parent: " << (i.parent () ? i.parent ()->vertex ().value ():"-") << ", discovery: " << setw (2) << i.discovery () << ", finish: " << setw (2) << i.finish () << endl;
  }

  cout << endl;

  return 0;
}
