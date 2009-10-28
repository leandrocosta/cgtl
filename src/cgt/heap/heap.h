#ifndef _HEAP_H_
#define _HEAP_H_

#include "../vector/vector.h"
using namespace cgt::vector;


namespace cgt
{
  namespace heap
  {
    template<typename _TpItem, typename _Alloc = _Allocator<_TpItem> >
      class _Heap : private _Vector<_TpItem, _Alloc>
      {
        private:
          typedef _Vector<_TpItem, _Alloc> _Base;

        public:
          using _Base::empty;
          using _Base::iterator;
          using _Base::const_iterator;
          using _Base::begin;
          using _Base::end;

        public:
          void push (const _TpItem& _i) { _Base::push_heap (_i); }
          _TpItem* pop () { return _Base::pop_heap (); }
      };

    template<typename _TpItem>
      class heap : public _Heap<_TpItem> { };
  }
}

#endif
