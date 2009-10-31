#ifndef _HEAP_H_
#define _HEAP_H_

#include "../vector/vector.h"
using namespace cgt::base::vector;


namespace cgt
{
  namespace base
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
          using _Base::size;
          using _Base::const_iterator;
          using _Base::begin;
          using _Base::end;

        private:
          void _rebuild (size_t _pos);

        public:
          void push (const _TpItem& _i) { _Base::push_heap (_i); }
          _TpItem* pop () { return _Base::pop_heap (); }
          void modify (_ConstIterator& _it, const _TpItem& _i);

          template<typename _Modifier, typename _Parm>
            void modify_by (_ConstIterator& _it, _Modifier _modify, const _Parm& _parm)
            {
              if (_it >= begin () && _it < end ())
              {
                _TpItem* _ptr = &(*(find (*_it)));
                _modify (*_ptr, _parm);
                _rebuild (_it - begin () + 1);
                _it = find (*_ptr);
              }
            }
      };


      template<typename _TpItem, typename _Alloc>
        void _Heap<_TpItem, _Alloc>::modify (_ConstIterator& _it, const _TpItem& _i)
        {
          if (_it >= begin () && _it < end ())
          {
            *(find (*_it)) = _i;
            _rebuild (_it - begin () + 1);
          }
        }

      template<typename _TpItem, typename _Alloc>
        void _Heap<_TpItem, _Alloc>::_rebuild (size_t _pos)
        {
          while (_pos > 0)
            _Base::rebuild_heap (--_pos);
        }

      template<typename _TpItem>
        class heap : public _Heap<_TpItem> { };
    }
  }
}

#endif
