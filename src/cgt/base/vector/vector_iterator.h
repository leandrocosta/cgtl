#ifndef _VECTOR_ITERATOR_H_
#define _VECTOR_ITERATOR_H_

#include "../iterator/iterator_type.h"
using namespace cgt::base::iterator;

#include "../iterator/iterator_ptr.h"


namespace cgt
{
  namespace base
  {
    namespace vector
    {
      template<typename _TpItem, template<typename> class _TpIterator = _TpCommon>
        class _VectorIterator : public _IteratorPtr<_TpItem*, _TpIterator>
        {
          private:
            typedef _IteratorPtr<_TpItem*, _TpIterator>       _Base;
            typedef _VectorIterator<_TpItem, _TpIterator>     _Self;
            typedef _VectorIterator<_TpItem, _TpCommon>       _SelfCommon;
            typedef typename _TpIterator<_TpItem>::pointer    pointer;
            typedef typename _TpIterator<_TpItem>::reference  reference;

          private:
            using _Base::_ptr;

          public:
            _VectorIterator () { }
            _VectorIterator (_TpItem** _p) : _Base (_p) { }
            _VectorIterator (const _SelfCommon& _it) : _Base (_it._ptr) { }

          private:
            void _incr () { _ptr++; }

          public:
            const bool operator<(const _Self& _other) const { return (_ptr < _other._ptr); }
            const bool operator>(const _Self& _other) const { return (_ptr > _other._ptr); }
            const bool operator>=(const _Self& _other) const { return (_ptr >= _other._ptr); }
            reference operator*() const { return **_ptr; }
            pointer operator->() const { return *_ptr; }

            _Self& operator++() { _incr (); return *this; }
            const _Self operator++(int) { _Self _it = *this; _incr (); return _it; }
            const size_t operator-(const _Self &_other) const { return _ptr - _other._ptr; }
        };


      template<typename _TpItem, typename _Predicate>
        _VectorIterator<_TpItem> find_if (_VectorIterator<_TpItem> _it, _VectorIterator<_TpItem> _end, _Predicate _pred)
        {
          while (_it != _end && ! _pred (*_it))
            ++_it;

          return _it;
        }

      template<typename _TpItem, typename _Predicate, typename _Parm>
        _VectorIterator<_TpItem> find_if (_VectorIterator<_TpItem> _it, _VectorIterator<_TpItem> _end, _Predicate _pred, const _Parm& _parm)
        {
          while (_it != _end && ! _pred (*_it, _parm))
            ++_it;

          return _it;
        }
    }
  }
}

#endif
