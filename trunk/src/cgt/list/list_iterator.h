#ifndef _LIST_ITERATOR_H_
#define _LIST_ITERATOR_H_

#include "list_iterator_base.h"
#include "iterator_type.h"


namespace cgt
{
  namespace list
  {
    template<typename _TpItem, typename _TpIterator = _TpCommon<_TpItem> >
      class _ListIterator : public _ListIteratorBase<_TpItem>
    {
      private:
        typedef _ListIteratorBase<_TpItem>                  _Base;
        typedef _ListIterator<_TpItem, _TpIterator>         _Self;
        typedef _ListIterator<_TpItem, _TpCommon<_TpItem> > _SelfCommon;
        typedef _ListItem<_TpItem>                          _Item;
        typedef typename _TpIterator::pointer               pointer;
        typedef typename _TpIterator::reference             reference;

      public:
        _ListIterator () { }
        _ListIterator (_Item *_p) : _Base (_p) { }
        _ListIterator (const _SelfCommon& _it) : _Base (_it._ptr) { }

      public:
        reference operator*() const;
        pointer operator->() const;

        _Self& operator++();
        const _Self operator++(int);
    };

    template<typename _TpItem, typename _TpIterator>
      typename _TpIterator::reference _ListIterator<_TpItem, _TpIterator>::operator*() const
      {
        return static_cast<_Item *>(_Base::_ptr)->_data;
      }

    template<typename _TpItem, typename _TpIterator>
      typename _TpIterator::pointer _ListIterator<_TpItem, _TpIterator>::operator->() const
      {
        return &(operator*());
      }

    template<typename _TpItem, typename _TpIterator>
      _ListIterator<_TpItem, _TpIterator>& _ListIterator<_TpItem, _TpIterator>::operator++()
      {
        _Base::_incr ();
        return *this;
      }

    template<typename _TpItem, typename _TpIterator>
      const _ListIterator<_TpItem, _TpIterator> _ListIterator<_TpItem, _TpIterator>::operator++(int)
      {
        _Self _it = *this;
        _Base::_incr ();
        return _it;
      }
  }
}

#endif
