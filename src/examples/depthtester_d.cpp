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
  create_graph_1<string, int, _Directed> (g);

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
    const mygraph::node&   n = *itn;
    const mygraph::vertex& v = n.vertex ();
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

    cout << "node: " << i.node ().vertex ().value () << ", parent: " << (i.parent () ? i.parent ()->vertex ().value ():"-") << ", discovery: " << setw (2) << i.discovery () << ", finish: " << setw (2) << i.finish () << endl;
  }

  cout << endl;

  cout << "=== make inverse graph ===" << endl << endl;

  g.invert ();

  cout << "=== depth-first search from begin ===" << endl << endl;

//  mygraph::diterator itd2;
  itdEnd = g.depth_end ();

  for (itd = g.depth_begin (); itd != itdEnd; ++itd)
  {
    const mygraph::node&       n = *itd;
    const mygraph::vertex&     v = n.vertex ();
    const mygraph::depth_info* i = itd.info (n);

    cout << "itd: " << v.value () <<  ", discovery: " << setw (2) << i->discovery () << ", parent: " << (i->parent () ? i->parent ()->vertex ().value ():"-") << endl;
  }

  cout << endl;
  cout << "=== show depth-first search info for all vertices ===" << endl << endl;

  mygraph::const_iterator itn2;
  mygraph::const_iterator itn2End = g.end ();

  for (itn2 = g.begin (); itn2 != itn2End; ++itn2)
  {
    const mygraph::node&   n = *itn2;
    const mygraph::vertex& v = n.vertex ();
    const mygraph::depth_info* i = itd.info (n);

    cout << "node: " << v.value () << ", parent: " << (i->parent () ? i->parent ()->vertex ().value ():"-") << ", discovery: " << setw (2) << i->discovery () << ", finish: " << setw (2) << i->finish () << endl;
  }

  cout << endl;

  return 0;
}
