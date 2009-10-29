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
          typedef _Vector<_TpItem, _Alloc>        _Base;
          typedef typename _Base::iterator        _Iterator;
          typedef typename _Base::const_iterator  _ConstIterator;

        public:
          using _Base::find;
          using _Base::empty;
          using _Base::const_iterator;
          using _Base::begin;
          using _Base::end;

        public:
          void push (const _TpItem& _i) { _Base::push_heap (_i); }
          _TpItem* pop () { return _Base::pop_heap (); }
          void modify (_ConstIterator& _it, const _TpItem& _i);
      };


    template<typename _TpItem, typename _Alloc>
      void _Heap<_TpItem, _Alloc>::modify (_ConstIterator& _it, const _TpItem& _i)
      {
        if (_it >= begin () && _it < end ())
        {
          *(find (*_it)) = _i;

          size_t _pos = _it - begin () + 1;

          while (_pos > 0)
            _Base::rebuild_heap (--_pos);
        }
      }

    template<typename _TpItem>
      class heap : public _Heap<_TpItem> { };
  }
}

#endif
