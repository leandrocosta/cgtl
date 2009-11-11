#ifndef _GRAPH_SCC_COMPONENT_H_
#define _GRAPH_SCC_COMPONENT_H_

#include "graph_scc_node.h"
#include "../base/list/list.h"
using namespace cgt::base::list;


namespace cgt
{
  namespace stconncomp
  {
    template<typename _TpVertex, typename _TpEdge>
      class _GraphSCCComponent : public _List<_GraphSCCNode<_TpVertex, _TpEdge> >
      {
      };
  }
}

#endif
