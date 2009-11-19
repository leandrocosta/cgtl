#ifndef _PRIM_ADJACENCY_HEAP_H_
#define _PRIM_ADJACENCY_HEAP_H_

#include "../../base/heap.h"
#include "../../graph_adjacency.h"


namespace cgt
{
  namespace minspantree
  {
    namespace prim
    {
      template<typename _TpItem>
        class _PrimAdjacencyHeap : public cgt::base::heap<_TpItem>
        {
          protected:
            virtual const bool _less_than (const _TpItem& _child, const _TpItem& _parent) const
            {
              return (_child->edge ().value () < _parent->edge ().value ());
            }
        };
    }
  }
}



#endif
