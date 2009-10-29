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
          virtual ~_Vector () { _remove_all (); free (_array); }

        private:
          void _init ();
          void _remove_all ();
          void _increase ();
          void _swap (_TpItem** _ptr1, _TpItem** _ptr2);

        public:
          void push_back (const _TpItem& _item);
          _TpItem* pop_back ();
          iterator find (const _TpItem& _item);
          const bool empty () const;

        private:
          void _rebuild_heap (size_t _pos);

        public:
          void make_heap ();
          _TpItem* pop_heap ();
          void push_heap (const _TpItem& _item);
          void rebuild_heap (size_t _pos);

        public:
          iterator begin () { return iterator (_head); }
          iterator end () { return iterator (_tail); }
          const_iterator begin () const { return const_iterator (_head); }
          const_iterator end () const { return const_iterator (_tail); }

        private:
          _TpItem** _array;
          _TpItem** _head;
          _TpItem** _tail;
          size_t    _size;
          size_t    _bufsize;

          allocator_type  _alloc;
      };


    template<typename _TpItem, typename _Alloc>
      void _Vector<_TpItem, _Alloc>::_init ()
      {
        _array = (_TpItem **) malloc (_bufsize * sizeof (_TpItem **));
        _head = _array;
        _tail = _array;
      }

    template<typename _TpItem, typename _Alloc>
      void _Vector<_TpItem, _Alloc>::_remove_all ()
      {
        for (size_t i = 0; i < _size; i++)
        {
          _alloc.destroy (_array [i]);
          _alloc.deallocate (_array [i], 1);
        }

        _tail = _head;
        _size = 0;
      }

    template<typename _TpItem, typename _Alloc>
      void _Vector<_TpItem, _Alloc>::_increase ()
      {
        _bufsize *= 2;
        _array = (_TpItem **) realloc (_array, _bufsize * sizeof (_TpItem **));
        _head = _array;
        _tail = &(_array [_size]);
      }

    template<typename _TpItem, typename _Alloc>
      void _Vector<_TpItem, _Alloc>::_swap (_TpItem** _ptr1, _TpItem** _ptr2)
      {
        _TpItem* _p = *_ptr1;
        *_ptr1 = *_ptr2;
        *_ptr2 = _p;
      }

    template<typename _TpItem, typename _Alloc>
      void _Vector<_TpItem, _Alloc>::push_back (const _TpItem& _item)
      {
        if (_size == _bufsize)
          _increase ();

        *_tail  = _alloc.allocate (1);
        _alloc.construct (*_tail, _item);

        _tail++;
        _size++;
      }

    template<typename _TpItem, typename _Alloc>
      _TpItem* _Vector<_TpItem, _Alloc>::pop_back ()
      {
        _TpItem* _ptr = NULL;

        if (_tail > _head)
        {
          _tail--;
          _ptr = new _TpItem (**_tail);
          _alloc.destroy (*_tail);
          _alloc.deallocate (*_tail, 1);
          _size--;
        }

        return _ptr;
      }

    template<typename _TpItem, typename _Alloc>
      _VectorIterator<_TpItem> _Vector<_TpItem, _Alloc>::find (const _TpItem& _item)
      {
        iterator it;
        iterator itEnd = end ();

        for (it = begin (); it != itEnd; ++it)
          if (*it == _item)
            break;

        return it;
      }

    template<typename _TpItem, typename _Alloc>
      const bool _Vector<_TpItem, _Alloc>::empty () const
      {
        return (! _size);
      }

    template<typename _TpItem, typename _Alloc>
      void _Vector<_TpItem, _Alloc>::make_heap ()
      {
        size_t _pos = _size/2;

        while ( _pos > 0)
          _rebuild_heap (--_pos);
      }

    template<typename _TpItem, typename _Alloc>
      void _Vector<_TpItem, _Alloc>::_rebuild_heap (size_t _pos)
      {
        _TpItem* _ptr = _array [_pos];
        size_t k = 2*_pos+1;

        while (k < _size)
        {
          if (k+1 < _size && *_array[k+1] < *_array[k])
            k++;

          if (*(_array[k]) < *_ptr)
          {
            _array[_pos] = _array[k];
            _pos = k;
            k = 2*_pos+1;
          }
          else
            break;
        }

        _array[_pos] = _ptr;
      }

    template<typename _TpItem, typename _Alloc>
      void _Vector<_TpItem, _Alloc>::rebuild_heap (size_t _pos)
      {
        _rebuild_heap (_pos);
      }

    template<typename _TpItem, typename _Alloc>
      _TpItem* _Vector<_TpItem, _Alloc>::pop_heap ()
      {
        _TpItem* _ptr = NULL;

        if (_size > 1)
        {
          _swap (_head, _tail-1);
          _ptr = pop_back ();
          _rebuild_heap (0);
        }
        else if (_size)
          _ptr = pop_back ();

        return _ptr;
      }

    template<typename _TpItem, typename _Alloc>
      void _Vector<_TpItem, _Alloc>::push_heap (const _TpItem& _item)
      {
        push_back (_item);

        size_t _child = _size-1;
        size_t _parent = _child;
        _TpItem* _ptr = _array[_child];

        while (_child > 0)
        {
          _parent = (_child-1)/2;

          if (*_ptr < *_array[_parent])
          {
            _array[_child] = _array[_parent];
            _child = _parent;
          }
          else
            break;
        }

        _array[_child] = _ptr;
      }

    template<typename _TpItem>
      class vector : public _Vector<_TpItem> { };
  }
}

#endif
