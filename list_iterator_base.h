#ifndef _LIST_ITERATOR_BASE_H_
#define _LIST_ITERATOR_BASE_H_

template<typename _TpItem>
class _ListItemBase;


template<typename _TpItem>
class _ListIteratorBase
{
  private:
    typedef _ListIteratorBase<_TpItem>  _Self;

  public:
    _ListIteratorBase () : _ptr (NULL) { }
    _ListIteratorBase (_ListItemBase<_TpItem> *_p) : _ptr (_p) { }

  protected:
    void _incr ();

  public:
    const bool operator==(_Self &_other) const;
    const bool operator!=(_Self &_other) const;

  protected:
    _ListItemBase<_TpItem>* _ptr;
};

template<typename _TpItem>
void _ListIteratorBase<_TpItem>::_incr ()
{
  _ptr = _ptr->_get_next ();
}

template<typename _TpItem>
const bool _ListIteratorBase<_TpItem>::operator==(_ListIteratorBase<_TpItem> &_other) const
{
  return _ptr == _other._ptr;
}

template<typename _TpItem>
const bool _ListIteratorBase<_TpItem>::operator!=(_ListIteratorBase<_TpItem> &_other) const
{
  return ! (*this == _other);
}

#endif
