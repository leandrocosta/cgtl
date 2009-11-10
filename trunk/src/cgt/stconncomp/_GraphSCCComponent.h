#ifndef _GRAPH_SCC_COMPONENT_H_
#define _GRAPH_SCC_COMPONENT_H_

#include "graph_scnode.h"
#include "../base/list/list.h"
using namespace cgt::base::list;


namespace cgt
{
  namespace stconncomp
  {
    template<typename _TpVertex, typename _TpEdge>
      class _GraphSCComponent : public _List<_GraphSCNode<_TpVertex, _TpEdge> >
      {
      }
  }
}

#endif
