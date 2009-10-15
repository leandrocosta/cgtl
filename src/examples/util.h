#ifndef _UTIL_H_
#define _UTIL_H_

#include "../cgt/graph_type.h"
using namespace cgt;


namespace cgt
{
  template<typename _TpVertex, typename _TpEdge, typename _TpGraphType>
    class graph;
}

template<typename _TpVertex, typename _TpEdge, typename _TpGraphType>
  void add_vertex (graph<_TpVertex, _TpEdge, _TpGraphType> &_g, const _TpVertex &_v)
  {
    cout << "insert vertex " << _v << endl;
    _g.insert_vertex (_v);
  }

template<typename _TpVertex, typename _TpEdge, typename _TpGraphType>
  void add_edge (graph<_TpVertex, _TpEdge, _TpGraphType> &_g, const _TpEdge &_e, const _TpVertex &_v1, const _TpVertex &_v2)
  {
    cout << "insert edge (" << _e << ", " << _v1 << ", " << _v2 << ")" << endl;
    _g.insert_edge (_e, _v1, _v2);
  }

#endif
