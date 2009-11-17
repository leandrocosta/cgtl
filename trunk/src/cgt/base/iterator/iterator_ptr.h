#ifndef _ITERATOR_PTR_H_
#define _ITERATOR_PTR_H_

#include "iterator_type.h"


namespace cgt
{
  namespace base
  {
    namespace iterator
    {
      template<typename _TpItem, template<typename> class _TpIterator>
        class _IteratorPtr
      {
        private:
          friend class _IteratorPtr<_TpItem, _TpCommon>;
          friend class _IteratorPtr<_TpItem, _TpConst>;

        private:
          typedef _IteratorPtr<_TpItem, _TpCommon>  _SelfCommon;
          typedef _IteratorPtr<_TpItem, _TpConst>   _SelfConst;

        protected:
          _IteratorPtr () : _ptr (NULL) { }
          _IteratorPtr (_TpItem* _p) : _ptr (_p) { }
          virtual ~_IteratorPtr () { }

        public:
            virtual const bool operator==(const _SelfCommon& _other) const { return (_ptr == _other._ptr); }
            virtual const bool operator==(const _SelfConst& _other) const { return (_ptr == _other._ptr); }
            virtual const bool operator!=(const _SelfCommon& _other) const { return !(*this == _other); }
            virtual const bool operator!=(const _SelfConst& _other) const { return !(*this == _other); }

        protected:
            virtual void _incr () = 0;

        protected:
          _TpItem* _ptr;
      };
    }
  }
}

#endif
