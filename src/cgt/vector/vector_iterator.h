#ifndef _VECTOR_ITERATOR_H_
#define _VECTOR_ITERATOR_H_

#include "../list/iterator_type.h"
using namespace cgt::list;


namespace cgt
{
  namespace vector
  {
    template<typename _TpItem, template<typename> class _TpIterator = _TpCommon>
      class _VectorIterator
    {
      private:
        friend class _VectorIterator<_TpItem, _TpConst>;

      private:
        typedef _VectorIterator<_TpItem, _TpIterator>     _Self;
        typedef _VectorIterator<_TpItem, _TpCommon>       _SelfCommon;
        typedef _VectorIterator<_TpItem, _TpConst>        _SelfConst;
        typedef typename _TpIterator<_TpItem>::pointer    pointer;
        typedef typename _TpIterator<_TpItem>::reference  reference;

      public:
        _VectorIterator () { }
        _VectorIterator (_TpItem** _p) : _ptr (_p) { }
        _VectorIterator (const _SelfCommon& _it) : _ptr (_it._ptr) { }
        _VectorIterator (const _SelfConst& _it) : _ptr (_it._ptr) { }

      public:
        const bool operator==(const _Self &_other) const { return (_ptr == _other._ptr); }
        const bool operator!=(const _Self &_other) const { return ! (*this == _other); }
        reference operator*() const { return **_ptr; }
        pointer operator->() const { return *_ptr; }

        _Self& operator++() { _ptr++; return *this; }
        const _Self operator++(int) { return _Self (_ptr++); }

      private:
        _TpItem** _ptr;
    };
  }
}

#endif
