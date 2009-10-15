#ifndef _LIST_CONST_ITERATOR_H_
#define _LIST_CONST_ITERATOR_H_

#include "list_iterator_base.h"


namespace cgt
{
  namespace list
  {
    template<typename _TpItem>
      class _ListIterator;


    template<typename _TpItem>
      class _ListConstIterator : public _ListIteratorBase<_TpItem>
    {
      private:
        typedef _ListIteratorBase<_TpItem>  _Base;
        typedef _ListConstIterator<_TpItem> _Self;
        typedef _ListItem<_TpItem>          _Item;
        typedef _ListIterator<_TpItem>      _Iterator;

      public:
        _ListConstIterator () { }
        _ListConstIterator (_Item *_p) : _Base (_p) { }
        _ListConstIterator (const _Iterator &_iterator) : _Base (_iterator._ptr) { }

      public:
        const _TpItem& operator*() const;
        const _TpItem* operator->() const;

        _Self& operator++();
        const _Self operator++(int);
    };

    template<typename _TpItem>
      const _TpItem& _ListConstIterator<_TpItem>::operator*() const
      {
        return static_cast<_Item *>(_Base::_ptr)->_data;
      }

    template<typename _TpItem>
      const _TpItem* _ListConstIterator<_TpItem>::operator->() const
      {
        return &(operator*());
      }

    template<typename _TpItem>
      _ListConstIterator<_TpItem>& _ListConstIterator<_TpItem>::operator++()
      {
        _Base::_incr ();
        return *this;
      }

    template<typename _TpItem>
      const _ListConstIterator<_TpItem> _ListConstIterator<_TpItem>::operator++(int)
      {
        _Self _it = *this;
        _Base::_incr ();
        return _it;
      }
  }
}

#endif
