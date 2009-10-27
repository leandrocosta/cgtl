#ifndef _VECTOR_H_
#define _VECTOR_H_

#include "vector_iterator.h"
#include "../alloc/allocator.h"
using namespace cgt::alloc;


namespace cgt
{
  namespace vector
  {
    template<typename _TpItem, typename _Alloc = _Allocator<_TpItem> >
      class _Vector
      {
        public:
          typedef _VectorIterator<_TpItem>            iterator;
          typedef _VectorIterator<_TpItem, _TpConst>  const_iterator;

        private:
          typedef typename _Alloc::template rebind<_TpItem>::other allocator_type;

        public:
          _Vector () : _size (0), _bufsize (1) { _init (); }
          virtual ~_Vector () { free (_array); }

        private:
          void _init ();

        public:
          void push_back (const _TpItem& _item);

        public:
          iterator begin () { return iterator (_array); }
          iterator end () { return iterator (_tail); }
          const_iterator begin () const { return const_iterator (_array); }
          const_iterator end () const { return const_iterator (_tail); }

        private:
          _TpItem** _array;
          _TpItem** _tail;
          size_t    _size;
          size_t    _bufsize;

          allocator_type  _alloc;
      };


    template<typename _TpItem, typename _Alloc>
      void _Vector<_TpItem, _Alloc>::_init ()
      {
        _array = (_TpItem **) malloc (_bufsize * sizeof (_TpItem **));
        _tail = _array;
      }

    template<typename _TpItem, typename _Alloc>
      void _Vector<_TpItem, _Alloc>::push_back (const _TpItem& _item)
      {
        if (_size == _bufsize)
        {
          _array = (_TpItem **) realloc (_array, 2 * _bufsize * sizeof (_TpItem **));
          _tail = &(_array [_size]);
          _bufsize *= 2;
        }

        _TpItem* _p = _alloc.allocate (1);
        *_tail = _p;
        _alloc.construct (*_tail, _item);

        _tail++;
        _size++;
      }

    template<typename _TpItem>
      class vector : public _Vector<_TpItem> { };
  }
}

#endif
