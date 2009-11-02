#ifndef _ITERATOR_PTR_H_
#define _ITERATOR_PTR_H_

#include "iterator_base.h"
#include "iterator_type.h"


namespace cgt
{
  namespace base
  {
    namespace iterator
    {
      template<typename _TpItem, template<typename> class _TpIterator>
        class _IteratorPtr : public _IteratorBase<_TpItem, _TpIterator>
      {
        private:
          friend class _IteratorPtr<_TpItem, _TpCommon>;
          friend class _IteratorPtr<_TpItem, _TpConst>;

        private:
          typedef _IteratorPtr<_TpItem, _TpIterator>  _Self;
          typedef _IteratorPtr<_TpItem, _TpCommon>    _SelfCommon;
          typedef _IteratorPtr<_TpItem, _TpConst>     _SelfConst;

        protected:
          _IteratorPtr () : _ptr (NULL) { }
          _IteratorPtr (_TpItem* _p) : _ptr (_p) { }

        public:
            const bool operator==(const _SelfCommon& _other) const { return (_ptr == _other._ptr); }
            const bool operator==(const _SelfConst& _other) const { return (_ptr == _other._ptr); }
            const bool operator!=(const _SelfCommon& _other) const { return !(*this == _other); }
            const bool operator!=(const _SelfConst& _other) const { return !(*this == _other); }

        protected:
          _TpItem* _ptr;
      };
    }
  }
}

#endif
