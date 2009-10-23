#ifndef _LIST_ITERATOR_H_
#define _LIST_ITERATOR_H_

#include "list_iterator_base.h"
#include "iterator_type.h"


namespace cgt
{
  namespace list
  {
    template<typename _TpItem, template<typename> class _TpIterator = _TpCommon>
      class _ListIterator : public _ListIteratorBase<_TpItem>
    {
      private:
        typedef _ListIteratorBase<_TpItem>                _Base;
        typedef _ListIterator<_TpItem, _TpIterator>       _Self;
        typedef _ListIterator<_TpItem, _TpCommon>         _SelfCommon;
        typedef _ListIterator<_TpItem, _TpConst>          _SelfConst;
        typedef _ListItem<_TpItem>                        _Item;
        typedef typename _TpIterator<_TpItem>::pointer    pointer;
        typedef typename _TpIterator<_TpItem>::reference  reference;

      public:
        _ListIterator () { }
        _ListIterator (_Item *_p) : _Base (_p) { }
        _ListIterator (const _SelfCommon& _it) : _Base (_it._ptr) { }
        _ListIterator (const _SelfConst& _it) : _Base (_it._ptr) { }

      public:
        reference operator*() const;
        pointer operator->() const;

        _Self& operator++();
        const _Self operator++(int);
    };

    template<typename _TpItem, template<typename> class _TpIterator>
      typename _TpIterator<_TpItem>::reference _ListIterator<_TpItem, _TpIterator>::operator*() const
      {
        return static_cast<_Item *>(_Base::_ptr)->_data;
      }

    template<typename _TpItem, template<typename> class _TpIterator>
      typename _TpIterator<_TpItem>::pointer _ListIterator<_TpItem, _TpIterator>::operator->() const
      {
        return &(operator*());
      }

    template<typename _TpItem, template<typename> class _TpIterator>
      _ListIterator<_TpItem, _TpIterator>& _ListIterator<_TpItem, _TpIterator>::operator++()
      {
        _Base::_incr ();
        return *this;
      }

    template<typename _TpItem, template<typename> class _TpIterator>
      const _ListIterator<_TpItem, _TpIterator> _ListIterator<_TpItem, _TpIterator>::operator++(int)
      {
        _Self _it = *this;
        _Base::_incr ();
        return _it;
      }
  }
}

#endif
