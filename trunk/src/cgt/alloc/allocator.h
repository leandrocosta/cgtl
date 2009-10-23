#ifndef _ALLOCATOR_H_
#define _ALLOCATOR_H_

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
          template <class _U> struct rebind { typedef _Allocator<_U>
            other; };

          _Allocator() { };
          _Allocator(const _Allocator&) { };
          template <class _U> _Allocator(const _Allocator<_U>&) { };
          ~_Allocator() { };

          pointer address(reference x) const { return &x; }
          const_pointer address(const_reference x) const { return &x; }

          pointer allocate(size_type size, _Allocator<_TpItem>::const_pointer hint = 0)
          {
            cout << "_Allocator.allocate ()" << endl;
            return static_cast<pointer>(malloc (size * sizeof (_TpItem)));
          }
          void deallocate(pointer p, size_type n)
          {
            cout << "_Allocator.deallocate ()" << endl;
            free (p);
          }
          size_type max_size() const
          {
            cout << "_Allocator.max_size ()" << endl;
            return (sizeof (-1) / sizeof (_TpItem));
          }

          void construct(pointer p, const _TpItem& val)
          {
            cout << "_Allocator.construct ()" << endl;
            new (static_cast<_TpItem *>(p)) _TpItem (val);
          }
          void destroy(pointer p)
          {
            cout << "_Allocator.destroy ()" << endl;
            p->~_TpItem ();
          }
      };
  }
}

#endif
