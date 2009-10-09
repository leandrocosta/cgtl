#ifndef _LIST_ITERATOR_H_
#define _LIST_ITERATOR_H_

namespace cgt
{
  namespace list
  {
    template<typename _TpItem>
      class _ListIteratorBase;


    template<typename _TpItem>
      class _ListIterator : public _ListIteratorBase<_TpItem>
    {
      public:
        _ListIterator () : _ListIteratorBase<_TpItem> (NULL) { }
        _ListIterator (_ListItem<_TpItem> *_p) : _ListIteratorBase<_TpItem> (_p) { }

      private:
        typedef _ListIterator<_TpItem>  _Self;
        typedef _ListItem<_TpItem>      _Item;

      public:
        _TpItem& operator*() const;
        _TpItem* operator->() const;

        _Self& operator++();
    };

    template<typename _TpItem>
      _TpItem& _ListIterator<_TpItem>::operator*() const
      {
        return static_cast<_Item *>(_ListIteratorBase<_TpItem>::_ptr)->_get_data ();
      }

    template<typename _TpItem>
      _TpItem* _ListIterator<_TpItem>::operator->() const
      {
        return &(operator*());
      }

    template<typename _TpItem>
      _ListIterator<_TpItem>& _ListIterator<_TpItem>::operator++()
      {
        assert (_ListIteratorBase<_TpItem>::_ptr != NULL);
        _ListIteratorBase<_TpItem>::_incr ();
        return *this;
      }
  }
}

#endif
