#include <assert.h>

#include <string>
#include <sstream>
#include <iostream>
using namespace std;

#include "cgt/graph.h"
using namespace cgt;


int main ()
{
  graph<string, int, _Undirected> g;

  g.insert_vertex ("A");
  g.insert_vertex ("B");
  g.insert_vertex ("C");

  g.insert_edge (0, "A", "B");
  g.insert_edge (1, "A", "C");

  g.insert_edge (2, "B", "C");
  g.insert_edge (3, "C", "C");

  /*
  graph<string, int>::vertex_iterator itv;
  graph<string, int>::vertex_iterator itvEnd = g.vertex_end ();

  for (itv = g.vertex_begin (); itv != itvEnd; ++itv)
    cout << "vertex: " << *itv << endl;

  g.insert_edge (0, "A", "B");
  g.insert_edge (1, "A", "C");
  */

  /*
  graph<string, int>::edge_iterator ite;
  graph<string, int>::edge_iterator iteEnd = g.edge_end ();

  for (ite = g.edge_begin (); ite != iteEnd; ++ite)
  {
    _GraphEdge<string, int> &r_edge = *ite;
    cout << "edge: " << r_edge.to_string () << endl;
  }
  */

  graph<string, int>::iterator itn;
  graph<string, int>::iterator itnEnd = g.end ();

  for (itn = g.begin (); itn != itnEnd; ++itn)
  {
    graph<string, int>::node&     n = *itn;
    graph<string, int>::vertex&  v = n.vertex ();

    cout << "vertex: " << v.value () << endl;

    graph<string, int>::adjlist &adjList = n.get_adj_list ();

    graph<string, int>::adjlist::iterator itadj;
    graph<string, int>::adjlist::iterator itadjEnd = adjList.end ();

    for (itadj = adjList.begin (); itadj != itadjEnd; ++itadj)
    {
      const graph<string, int>::vertex&  v = itadj->get_vertex ();

      const graph<string, int>::edge&     e   = itadj->get_edge ();
      const graph<string, int>::vertex&  v1  = e.v1 ();
      const graph<string, int>::vertex&  v2  = e.v2 ();

      cout << "  vertex: " << v.value () << ", edge (" << e.value () << ", " << v1.value () << ", " << v2.value () << ")" << endl;
    }
  }

  /*
  graph<string, int>::iterator itn2;
  graph<string, int>::iterator itn2End = g.end ();

  for (itn2 = g.begin (); itn2 != itn2End; ++itn2)
    cout << "vertex: " << (*itn2).get_vertex ().get_value () << endl;
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
