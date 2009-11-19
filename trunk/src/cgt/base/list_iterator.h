#ifndef _LIST_ITERATOR_H_
#define _LIST_ITERATOR_H_

#include "iterator/iterator_ptr.h"


namespace cgt
{
  using namespace base::iterator;

  namespace base
  {
    template<typename _TpItem, template<typename> class _TpIterator = _TpCommon>
      class _ListIterator : public _IteratorPtr<_ListItemBase<_TpItem>, _TpIterator>
    {
      private:
        typedef _ListItemBase<_TpItem>                _ItemBase;
        typedef _IteratorPtr<_ItemBase, _TpIterator>  _Base;
        typedef _ListIterator<_TpItem, _TpIterator>   _Self;
        typedef _ListIterator<_TpItem, _TpCommon>     _SelfCommon;
        typedef _ListItem<_TpItem>                    _Item;

      private:
        typedef typename _TpIterator<_TpItem>::pointer    pointer;
        typedef typename _TpIterator<_TpItem>::reference  reference;

      private:
        using _Base::_ptr;

      public:
        _ListIterator () { }
        _ListIterator (_Item* _p) : _Base (_p) { }
        _ListIterator (const _SelfCommon& _it) : _Base (_it._ptr) { }

      private:
        void _incr () { _ptr = _ptr->_next; }

      public:
        reference operator*() const;
        pointer operator->() const;

        _Self& operator++();
        const _Self operator++(int);
    };


    template<typename _TpItem, template<typename> class _TpIterator>
      typename _TpIterator<_TpItem>::reference _ListIterator<_TpItem, _TpIterator>::operator*() const
      {
        return static_cast<_Item *>(_ptr)->_data;
      }

    template<typename _TpItem, template<typename> class _TpIterator>
      typename _TpIterator<_TpItem>::pointer _ListIterator<_TpItem, _TpIterator>::operator->() const
      {
        return &(operator*());
      }

    template<typename _TpItem, template<typename> class _TpIterator>
      _ListIterator<_TpItem, _TpIterator>& _ListIterator<_TpItem, _TpIterator>::operator++()
      {
        _incr ();
        return *this;
      }

    template<typename _TpItem, template<typename> class _TpIterator>
      const _ListIterator<_TpItem, _TpIterator> _ListIterator<_TpItem, _TpIterator>::operator++(int)
      {
        _Self _it = *this;
        _incr ();
        return _it;
      }

    template<typename _TpItem, typename _Predicate>
      _ListIterator<_TpItem> find_if (_ListIterator<_TpItem> _it, _ListIterator<_TpItem> _end, _Predicate _pred)
      {
        while (_it != _end && ! _pred (*_it))
          ++_it;

        return _it;
      }

    template<typename _TpItem, typename _Predicate, typename _Parm>
      _ListIterator<_TpItem> find_if (_ListIterator<_TpItem> _it, _ListIterator<_TpItem> _end, _Predicate _pred, const _Parm& _parm)
      {
        while (_it != _end && ! _pred (*_it, _parm))
          ++_it;

        return _it;
      }
  }
}

#endif
