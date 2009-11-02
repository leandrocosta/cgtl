#ifndef _HASH_ITERATOR_H_
#define _HASH_ITERATOR_H_

#include "../iterator/iterator_ptr.h"


namespace cgt
{
  namespace base
  {
    namespace hash
    {
      using namespace cgt::base::iterator;

      template<typename _TpItem, template<typename> class _TpIterator = _TpCommon>
        class _HashIterator : public _IteratorPtr<_TpItem*, _TpIterator>
      {
        private:
          typedef _IteratorPtr<_TpItem*, _TpIterator>       _Base;
          typedef _HashIterator<_TpItem, _TpIterator>       _Self;
          typedef _HashIterator<_TpItem, _TpCommon>         _SelfCommon;
          typedef typename _TpIterator<_TpItem>::pointer    pointer;
          typedef typename _TpIterator<_TpItem>::reference  reference;

        private:
          using _Base::_ptr;

        public:
          _HashIterator () { }
          _HashIterator (_TpItem** _p) : _Base (_p) { }
          _HashIterator (const _SelfCommon& _it) : _Base (_it._ptr) { }

        private:
          void _incr ()
          {
            do
            {
              _ptr++;
            } while (! *_ptr);
          };

        public:
          reference operator*() const { return **_ptr; }
          pointer operator->() const { return *_ptr; }

          _Self& operator++() { _incr (); return *this; }
          const _Self operator++(int) { return _Self (_ptr++); }
      };
    }
  }
}

#endif
