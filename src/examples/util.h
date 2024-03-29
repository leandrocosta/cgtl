#ifndef _UTIL_H_
#define _UTIL_H_

#include "cgt/graph_type.h"
using namespace cgt;

#include <string>
using namespace std;


namespace cgt
{
  template<typename _TpVertex, typename _TpEdge, typename _TpGraphType>
    class graph;
}

template<typename _TpVertex, typename _TpEdge, typename _TpGraphType>
  void add_vertex (graph<_TpVertex, _TpEdge, _TpGraphType> &_g, const _TpVertex &_v)
  {
    cout << "insert vertex " << _v () << endl;
    _g.insert_vertex (_v);
  }

template<typename _TpVertex, typename _TpEdge, typename _TpGraphType>
  void add_vertex (graph<string, _TpEdge, _TpGraphType> &_g, const string &_v)
  {
    cout << "insert vertex " << _v << endl;
    _g.insert_vertex (_v);
  }


template<typename _TpVertex, typename _TpEdge, typename _TpGraphType>
  void add_edge (graph<_TpVertex, _TpEdge, _TpGraphType> &_g, const _TpEdge &_e, const _TpVertex &_v1, const _TpVertex &_v2)
  {
    cout << "insert edge (" << _e () << ", " << _v1 () << ", " << _v2 () << ")" << endl;
    _g.insert_edge (_e, _v1, _v2);
  }

template<typename _TpVertex, typename _TpEdge, typename _TpGraphType>
  void add_edge (graph<string, int, _TpGraphType> &_g, const int &_e, const string &_v1, const string &_v2)
  {
    cout << "insert edge (" << _e << ", " << _v1 << ", " << _v2 << ")" << endl;
    _g.insert_edge (_e, _v1, _v2);
  }

template<typename _TpVertex, typename _TpEdge, typename _TpGraphType>
  void add_edge (graph<string, string, _TpGraphType> &_g, const string &_e, const string &_v1, const string &_v2)
  {
    cout << "insert edge (" << _e << ", " << _v1 << ", " << _v2 << ")" << endl;
    _g.insert_edge (_e, _v1, _v2);
  }


template<typename _TpVertex, typename _TpEdge, typename _TpGraphType>
  void create_graph_1 (graph<_TpVertex, _TpEdge, _TpGraphType> &_g)
{
  cout << "=== creating graph 1 ===" << endl << endl;

  add_vertex<_TpVertex, _TpEdge, _TpGraphType>(_g, "A");
  add_vertex<_TpVertex, _TpEdge, _TpGraphType>(_g, "B");
  add_vertex<_TpVertex, _TpEdge, _TpGraphType>(_g, "C");
  add_vertex<_TpVertex, _TpEdge, _TpGraphType>(_g, "D");
  add_vertex<_TpVertex, _TpEdge, _TpGraphType>(_g, "E");
  add_vertex<_TpVertex, _TpEdge, _TpGraphType>(_g, "F");
  add_vertex<_TpVertex, _TpEdge, _TpGraphType>(_g, "G");
  add_vertex<_TpVertex, _TpEdge, _TpGraphType>(_g, "H");
  add_vertex<_TpVertex, _TpEdge, _TpGraphType>(_g, "I");
  add_vertex<_TpVertex, _TpEdge, _TpGraphType>(_g, "J");

  cout << endl;

  add_edge<_TpVertex, _TpEdge, _TpGraphType>(_g, 0, "A", "B");
  add_edge<_TpVertex, _TpEdge, _TpGraphType>(_g, 1, "A", "C");
  add_edge<_TpVertex, _TpEdge, _TpGraphType>(_g, 2, "C", "E");
  add_edge<_TpVertex, _TpEdge, _TpGraphType>(_g, 3, "D", "E");
  add_edge<_TpVertex, _TpEdge, _TpGraphType>(_g, 4, "D", "F");

  add_edge<_TpVertex, _TpEdge, _TpGraphType>(_g, 5, "C", "G");
  add_edge<_TpVertex, _TpEdge, _TpGraphType>(_g, 6, "E", "H");
  add_edge<_TpVertex, _TpEdge, _TpGraphType>(_g, 7, "D", "I");
  add_edge<_TpVertex, _TpEdge, _TpGraphType>(_g, 8, "C", "J");

  cout << endl;
}

template<typename _TpVertex, typename _TpEdge, typename _TpGraphType>
  void create_graph_2 (graph<_TpVertex, _TpEdge, _TpGraphType> &_g)
{
  cout << "=== creating graph 2 ===" << endl << endl;

  add_vertex<_TpVertex, _TpEdge, _TpGraphType>(_g, "A");
  add_vertex<_TpVertex, _TpEdge, _TpGraphType>(_g, "B");
  add_vertex<_TpVertex, _TpEdge, _TpGraphType>(_g, "C");
  add_vertex<_TpVertex, _TpEdge, _TpGraphType>(_g, "D");
  add_vertex<_TpVertex, _TpEdge, _TpGraphType>(_g, "E");
  add_vertex<_TpVertex, _TpEdge, _TpGraphType>(_g, "F");
  add_vertex<_TpVertex, _TpEdge, _TpGraphType>(_g, "G");
  add_vertex<_TpVertex, _TpEdge, _TpGraphType>(_g, "H");
  add_vertex<_TpVertex, _TpEdge, _TpGraphType>(_g, "I");
  add_vertex<_TpVertex, _TpEdge, _TpGraphType>(_g, "J");

  cout << endl;

  add_edge<_TpVertex, _TpEdge, _TpGraphType>(_g, 3, "A", "B");
  add_edge<_TpVertex, _TpEdge, _TpGraphType>(_g, 7, "A", "C");
  add_edge<_TpVertex, _TpEdge, _TpGraphType>(_g, 9, "A", "D");

  add_edge<_TpVertex, _TpEdge, _TpGraphType>(_g, 2, "B", "D");
  add_edge<_TpVertex, _TpEdge, _TpGraphType>(_g, 1, "B", "E");
  add_edge<_TpVertex, _TpEdge, _TpGraphType>(_g, 3, "B", "F");

  add_edge<_TpVertex, _TpEdge, _TpGraphType>(_g, 6, "C", "F");
  add_edge<_TpVertex, _TpEdge, _TpGraphType>(_g, 2, "E", "G");
  add_edge<_TpVertex, _TpEdge, _TpGraphType>(_g, 4, "F", "G");
  add_edge<_TpVertex, _TpEdge, _TpGraphType>(_g, 1, "G", "H");
  add_edge<_TpVertex, _TpEdge, _TpGraphType>(_g, 8, "H", "J");
  add_edge<_TpVertex, _TpEdge, _TpGraphType>(_g, 2, "I", "J");
  add_edge<_TpVertex, _TpEdge, _TpGraphType>(_g, 1, "H", "I");

  cout << endl;
}

  template<typename _TpVertex, typename _TpEdge, typename _TpGraphType>
  void create_graph_3 (graph<_TpVertex, _TpEdge, _TpGraphType> &_g)
{
  cout << "=== creating graph 3 ===" << endl << endl;

  add_vertex<_TpVertex, _TpEdge, _TpGraphType>(_g, "A");
  add_vertex<_TpVertex, _TpEdge, _TpGraphType>(_g, "B");
  add_vertex<_TpVertex, _TpEdge, _TpGraphType>(_g, "C");
  add_vertex<_TpVertex, _TpEdge, _TpGraphType>(_g, "D");
  add_vertex<_TpVertex, _TpEdge, _TpGraphType>(_g, "E");
  add_vertex<_TpVertex, _TpEdge, _TpGraphType>(_g, "F");
  add_vertex<_TpVertex, _TpEdge, _TpGraphType>(_g, "G");
  add_vertex<_TpVertex, _TpEdge, _TpGraphType>(_g, "H");
  add_vertex<_TpVertex, _TpEdge, _TpGraphType>(_g, "I");
  add_vertex<_TpVertex, _TpEdge, _TpGraphType>(_g, "J");

  cout << endl;

  add_edge<_TpVertex, _TpEdge, _TpGraphType>(_g, 1, "C", "A");
  add_edge<_TpVertex, _TpEdge, _TpGraphType>(_g, 2, "C", "B");
  add_edge<_TpVertex, _TpEdge, _TpGraphType>(_g, 3, "B", "A");
  add_edge<_TpVertex, _TpEdge, _TpGraphType>(_g, 4, "A", "G");
  add_edge<_TpVertex, _TpEdge, _TpGraphType>(_g, 5, "A", "D");
  add_edge<_TpVertex, _TpEdge, _TpGraphType>(_g, 6, "B", "F");
  add_edge<_TpVertex, _TpEdge, _TpGraphType>(_g, 7, "B", "J");
  add_edge<_TpVertex, _TpEdge, _TpGraphType>(_g, 8, "E", "G");
  add_edge<_TpVertex, _TpEdge, _TpGraphType>(_g, 9, "D", "E");
  add_edge<_TpVertex, _TpEdge, _TpGraphType>(_g, 10, "F", "D");
  add_edge<_TpVertex, _TpEdge, _TpGraphType>(_g, 11, "F", "I");
  add_edge<_TpVertex, _TpEdge, _TpGraphType>(_g, 12, "J", "H");

  cout << endl;
}


#endif
