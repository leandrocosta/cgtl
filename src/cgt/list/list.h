#ifndef _LIST_H_
#define _LIST_H_

namespace cgt
{
  namespace list
  {
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
          void insert (const _TpItem &_item);

        public:
          iterator begin () { return iterator (_head); }
          iterator end () { return iterator (NULL); }

        public:
          iterator find (const _TpItem &_item);

        protected:
          _ListItem<_TpItem>*  _head;
          _ListItem<_TpItem>*  _tail;
      };

    template<typename _TpItem>
      void _List<_TpItem>::insert (const _TpItem &_item)
      {
        _ListItem<_TpItem> *_ptr = new _ListItem<_TpItem> (_item);

        if (! _head)
          _head = _ptr;
        else
          _tail->_set_next (_ptr);

        _tail = _ptr;
      }

    template<typename _TpItem>
      _ListIterator<_TpItem> _List<_TpItem>::find (const _TpItem &_item)
      {
        _ListIterator<_TpItem> it    = begin ();
        _ListIterator<_TpItem> itEnd = end ();

        while (it != end () && *it != _item)
          ++it;

        return it;
      }
  }
}

#endif
