#include <assert.h>

#include <string>
#include <sstream>
#include <iostream>
using namespace std;

#include "graph.h"
using namespace cgt;


int main ()
{
  graph<string, int> g;

  g.insert_vertice ("A");
  g.insert_vertice ("B");
  g.insert_vertice ("C");

  g.insert_edge (0, "A", "B");
  g.insert_edge (1, "A", "C");

  g.insert_edge (2, "B", "C");
  g.insert_edge (3, "C", "C");

  /*
  graph<string, int>::vertice_iterator itv;
  graph<string, int>::vertice_iterator itvEnd = g.vertice_end ();

  for (itv = g.vertice_begin (); itv != itvEnd; ++itv)
    cout << "vertice: " << *itv << endl;

  g.insert_edge (0, "A", "B");
  g.insert_edge (1, "A", "C");
  */

  /*
  graph<string, int>::edge_iterator ite;
  graph<string, int>::edge_iterator iteEnd = g.edge_end ();

  for (ite = g.edge_begin (); ite != iteEnd; ++ite)
  {
    _Edge<string, int> &r_edge = *ite;
    cout << "edge: " << r_edge.to_string () << endl;
  }
  */

  graph<string, int>::iterator itn;
  graph<string, int>::iterator itnEnd = g.end ();

  for (itn = g.begin (); itn != itnEnd; ++itn)
  {
    graph<string, int>::node&     n = *itn;
    graph<string, int>::vertice&  v = n.vertice ();

    cout << "vertice: " << v.value () << endl;

    graph<string, int>::adjlist &adjList = n.get_adj_list ();

    graph<string, int>::adjlist::iterator itadj;
    graph<string, int>::adjlist::iterator itadjEnd = adjList.end ();

    for (itadj = adjList.begin (); itadj != itadjEnd; ++itadj)
    {
      const graph<string, int>::vertice&  v = itadj->get_vertice ();

      const graph<string, int>::edge&     e   = itadj->get_edge ();
      const graph<string, int>::vertice&  v1  = e.v1 ();
      const graph<string, int>::vertice&  v2  = e.v2 ();

      cout << "  vertice: " << v.value () << ", edge (" << e.value () << ", " << v1.value () << ", " << v2.value () << ")" << endl;
    }
  }

  /*
  graph<string, int>::iterator itn2;
  graph<string, int>::iterator itn2End = g.end ();

  for (itn2 = g.begin (); itn2 != itn2End; ++itn2)
    cout << "vertice: " << (*itn2).get_vertice ().get_value () << endl;
    */

  /*
  _ListV2<int> l;
  l.insert (1);
  l.insert (2);
  _ListV2<int>::iterator it;
  _ListV2<int>::iterator itEnd = l.end ();

  for (it = l.begin (); it != itEnd; ++it)
  {
    cout << "*it: " << *it << endl;
  }
  */

  return 0;
}
