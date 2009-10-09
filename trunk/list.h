#ifndef _LIST_H_
#define _LIST_H_

template<typename _TpItem>
class _ListItem;

template<typename _TpItem>
class _ListIterator;


template<typename _TpItem>
class _List
{
  public:
    typedef _ListIterator<_TpItem>  iterator;

  public:
    _List () : _head (NULL), _tail (NULL) { }
    virtual ~_List ()
    {
      _ListItem<_TpItem> *_ptr = NULL;

      while (_head)
      {
        _ptr = _head;
        _head = static_cast<_ListItem<_TpItem> *>(_ptr->_get_next ());
        delete _ptr;
      }
    }

  public:
    void insert (const _TpItem &_item)
    {
      _ListItem<_TpItem> *_ptr = new _ListItem<_TpItem> (_item);

      if (! _head)
        _head = _ptr;
      else
        _tail->_set_next (_ptr);

      _tail = _ptr;
    }

  public:
    iterator begin () { return iterator (_head); }
    iterator end () { return iterator (NULL); }

  protected:
    _ListItem<_TpItem>*  _head;
    _ListItem<_TpItem>*  _tail;
};

#endif
