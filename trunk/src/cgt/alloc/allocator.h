#ifndef _ALLOCATOR_H_
#define _ALLOCATOR_H_

#include "storage.h"
#include <stdlib.h>
#include <malloc.h>


namespace cgt
{
  namespace alloc
  {
    template<typename _TpItem>
      class _Allocator
      {
        public:
          typedef size_t    size_type;
          typedef ptrdiff_t difference_type;
          typedef _TpItem*        pointer;
          typedef const _TpItem*  const_pointer;
          typedef _TpItem&        reference;
          typedef const _TpItem&  const_reference;
          typedef _TpItem         value_type;
          template <class _U> struct rebind { typedef _Allocator<_U> other; };

          _Allocator() { };
          _Allocator(const _Allocator&) { };
          template <class _U> _Allocator(const _Allocator<_U>&) { };
          ~_Allocator() { };

          pointer address(reference x) const { return &x; }
          const_pointer address(const_reference x) const { return &x; }

          pointer allocate(size_type size, _Allocator<_TpItem>::const_pointer hint = 0)
          {
            return static_cast<pointer>(_storage.allocate (size));
          }

          void deallocate(pointer p, size_type n)
          {
            _storage.deallocate (p);
          }

          size_type max_size() const
          {
            return (size_t (-1) / sizeof (_TpItem));
          }

          void construct(pointer p, const _TpItem& val)
          {
            new (static_cast<_TpItem *>(p)) _TpItem (val);
          }

          void destroy(pointer p)
          {
            p->~_TpItem ();
          }

        private:
          static _Storage<_TpItem> _storage;
      };

    template<typename _TpItem>
      _Storage<_TpItem> _Allocator<_TpItem>::_storage;
  }
}

#endif
