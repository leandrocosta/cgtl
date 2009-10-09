#ifndef _LIST_ITEM_BASE_H_
#define _LIST_ITEM_BASE_H_

template<typename _TpItem>
class _ListItem;

template<typename _TpItem>
class _List;

template<typename _TpItem>
class _ListIteratorBase;


template<typename _TpItem>
class _ListItemBase
{
  private:
    friend class _ListItem<_TpItem>;
    friend class _List<_TpItem>;
    friend class _ListIteratorBase<_TpItem>;

  private:
    typedef _ListItemBase<_TpItem>  _Self;

  private:
    _ListItemBase () : _next (NULL) { }
    _ListItemBase (_Self *_n) : _next (_n) { }

  private:
    _Self* _get_next () const;
    void _set_next (_Self *_n);

  private:
    _Self* _next;
};

template<typename _TpItem>
_ListItemBase<_TpItem>* _ListItemBase<_TpItem>::_get_next () const
{
  return _next;
}

template<typename _TpItem>
void _ListItemBase<_TpItem>::_set_next (_ListItemBase<_TpItem> *_n)
{
  _next = _n;
}

#endif
