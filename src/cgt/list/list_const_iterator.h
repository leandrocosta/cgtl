#ifndef _LIST_CONST_ITERATOR_H_
#define _LIST_CONST_ITERATOR_H_

namespace cgt
{
  namespace list
  {
    template<typename _TpItem>
      class _ListIteratorBase;

    template<typename _TpItem>
      class _ListIterator;


    template<typename _TpItem>
      class _ListConstIterator : public _ListIteratorBase<_TpItem>
    {
      public:
        _ListConstIterator () { }
        _ListConstIterator (_ListItem<_TpItem> *_p) : _ListIteratorBase<_TpItem> (_p) { }
        _ListConstIterator (const _ListIterator<_TpItem> &_iterator) : _ListIteratorBase<_TpItem> (_iterator._ptr) { }

      private:
        typedef _ListConstIterator<_TpItem>  _Self;
        typedef _ListItem<_TpItem>           _Item;

      public:
        const _TpItem& operator*() const;
        const _TpItem* operator->() const;

        _Self& operator++();
    };

    template<typename _TpItem>
      const _TpItem& _ListConstIterator<_TpItem>::operator*() const
      {
        return static_cast<_Item *>(_ListIteratorBase<_TpItem>::_ptr)->_get_data ();
      }

    template<typename _TpItem>
      const _TpItem* _ListConstIterator<_TpItem>::operator->() const
      {
        return &(operator*());
      }

    template<typename _TpItem>
      _ListConstIterator<_TpItem>& _ListConstIterator<_TpItem>::operator++()
      {
        assert (_ListIteratorBase<_TpItem>::_ptr != NULL);
        _ListIteratorBase<_TpItem>::_incr ();
        return *this;
      }
  }
}

#endif
