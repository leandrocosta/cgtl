#ifndef _LIST_ITERATOR_BASE_H_
#define _LIST_ITERATOR_BASE_H_

#include "iterator_type.h"


namespace cgt
{
  namespace list
  {
    template<typename _TpItem, typename _TpIterator>
      class _ListIterator;

    template<typename _TpItem>
      class _ListItemBase;


    template<typename _TpItem>
      class _ListIteratorBase
      {
        private:
          friend class _ListIterator<_TpItem, _TpCommon<_TpItem> >;
          friend class _ListIterator<_TpItem, _TpConst<_TpItem> >;

        private:
          typedef _ListIteratorBase<_TpItem>  _Self;
          typedef _ListItemBase<_TpItem>      _Item;

        private:
          _ListIteratorBase () : _ptr (NULL) { }
          _ListIteratorBase (_Item *_p) : _ptr (_p) { }

        private:
          void _incr ();

        public:
          const bool operator==(const _Self &_other) const;
          const bool operator!=(const _Self &_other) const;

        private:
          _Item* _ptr;
      };

    template<typename _TpItem>
      void _ListIteratorBase<_TpItem>::_incr ()
      {
        _ptr = _ptr->_next;
      }

    template<typename _TpItem>
      const bool _ListIteratorBase<_TpItem>::operator==(const _Self &_other) const
      {
        return _ptr == _other._ptr;
      }

    template<typename _TpItem>
      const bool _ListIteratorBase<_TpItem>::operator!=(const _Self &_other) const
      {
        return ! (*this == _other);
      }
  }
}

#endif
