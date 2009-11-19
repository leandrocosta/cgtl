#ifndef _KRUSKAL_EDGE_HEAP_H_
#define _KRUSKAL_EDGE_HEAP_H_

#include "../../base/heap.h"
#include "../../graph_edge.h"


namespace cgt
{
  namespace minspantree
  {
    namespace kruskal
    {
      template<typename _TpItem>
        class _KruskalEdgeHeap : public cgt::base::heap<_TpItem>
        {
          protected:
            virtual const bool _less_than (const _TpItem& _child, const _TpItem& _parent) const
            {
              return (_child->value () < _parent->value ());
            }
        };
    }
  }
}



#endif
