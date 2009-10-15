#ifndef _LIST_ITERATOR_H_
#define _LIST_ITERATOR_H_

#include "list_iterator_base.h"


namespace cgt
{
  namespace list
  {
    template<typename _TpItem>
      class _ListIterator : public _ListIteratorBase<_TpItem>
    {
      private:
        typedef _ListIteratorBase<_TpItem>  _Base;
        typedef _ListIterator<_TpItem>      _Self;
        typedef _ListItem<_TpItem>          _Item;

      public:
        _ListIterator () { }
        _ListIterator (_Item *_p) : _Base (_p) { }

      public:
        _TpItem& operator*() const;
        _TpItem* operator->() const;

        _Self& operator++();
        const _Self operator++(int);
    };

    template<typename _TpItem>
      _TpItem& _ListIterator<_TpItem>::operator*() const
      {
        return static_cast<_Item *>(_Base::_ptr)->_data;
      }

    template<typename _TpItem>
      _TpItem* _ListIterator<_TpItem>::operator->() const
      {
        return &(operator*());
      }

    template<typename _TpItem>
      _ListIterator<_TpItem>& _ListIterator<_TpItem>::operator++()
      {
        _Base::_incr ();
        return *this;
      }

    template<typename _TpItem>
      const _ListIterator<_TpItem> _ListIterator<_TpItem>::operator++(int)
      {
        _Self _it = *this;
        _Base::_incr ();
        return _it;
      }
  }
}

#endif
