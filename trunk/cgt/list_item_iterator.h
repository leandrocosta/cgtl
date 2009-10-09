#ifndef _LIST_ITEM_ITERATOR_H_
#define _LIST_ITEM_ITERATOR_H_

template<typename _TpItem>
class _ListItemBaseIterator


template<typename _TpItem>
class _ListItemIterator : protected _ListItemBaseIterator<_TpItem>
{
  private:
    typedef _ListItemIterator<_TpItem>  _Self;
    typedef _ListItem<_TpItem>          _Item;

  public:
    _TpItem& operator*() const { return static_cast<_Item *>(_ptr)._data; }
};

#endif
