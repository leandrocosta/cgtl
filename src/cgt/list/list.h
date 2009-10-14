#ifndef _LIST_H_
#define _LIST_H_

#include "list_item_base.h"
#include "list_item.h"
#include "list_iterator_base.h"
#include "list_iterator.h"
#include "list_const_iterator.h"

namespace cgt
{
  namespace list
  {
    template<typename _TpItem>
      class _ListItem;

    template<typename _TpItem>
      class _ListIterator;

    template<typename _TpItem>
      class _ListConstIterator;


    template<typename _TpItem>
      class _List
      {
        public:
          typedef _ListIterator<_TpItem>       iterator;
          typedef _ListConstIterator<_TpItem>  const_iterator;

        public:
          _List () : _head (NULL), _tail (NULL), _size (0) { }
          _List (const _List& _l) : _head (NULL), _tail (NULL), _size (0)
          {
//            cout << "_List (const _List& _l)" << endl;
            *this = _l;
          }
          virtual ~_List ()
          {
//            cout << "~_List () - _head: " << _head << endl;

            _ListItem<_TpItem> *_ptr = NULL;

            while (_head)
            {
              _ptr = _head;
              _head = static_cast<_ListItem<_TpItem> *>(_ptr->_next);
              delete _ptr;
            }
          }

        public:
          _List& operator=(const _List& _l)
          {
//            cout << "_List& operator=(const _List& _l)" << endl;

            const_iterator it;
            const_iterator itEnd = _l.end ();

            for (it = _l.begin (); it != itEnd; ++it)
              insert (*it);

            return *this;
          }

        private:
          _TpItem& _push_front (_ListItem<_TpItem> *_ptr);
          _TpItem& _push_back (_ListItem<_TpItem> *_ptr);

        public:
          _TpItem& insert (const _TpItem &_item);
          _TpItem& push_front (const _TpItem &_item);
          _TpItem& push_back (const _TpItem &_item);

          _TpItem* pop_front ();

          _TpItem* front ();

          const unsigned long size () const;
          const bool empty () const;

        public:
          iterator begin () { return iterator (_head); }
          iterator end () { return iterator (NULL); }
          const_iterator begin () const { return const_iterator (_head); }
          const_iterator end () const { return const_iterator (NULL); }

        public:
          iterator find (const _TpItem &_item);
          const_iterator find (const _TpItem &_item) const;

        protected:
          _ListItem<_TpItem>*  _head;
          _ListItem<_TpItem>*  _tail;
          unsigned long        _size;
      };

    template<typename _TpItem>
      _TpItem& _List<_TpItem>::_push_front (_ListItem<_TpItem> *_ptr)
      {
//        cout << "_push_front (_ptr: " << _ptr << ") - _head: " << _head << endl;

        _ptr->_next = _head;
        _head = _ptr;

//        cout << "_push_front (_ptr: " << _ptr << ") - _head: " << _head << ", _head->_next: " << _head->_next << endl;

        if (! _tail)
          _tail = _ptr;

        _size++;

        return _ptr->_data;
      }

    template<typename _TpItem>
      _TpItem& _List<_TpItem>::_push_back (_ListItem<_TpItem> *_ptr)
      {
        if (! _head)
          _head = _ptr;
        else
          _tail->_next = _ptr;

        _tail = _ptr;

        _size++;

        return _ptr->_data;
      }

    template<typename _TpItem>
      _TpItem& _List<_TpItem>::insert (const _TpItem &_item)
      {
        return _push_back (new _ListItem<_TpItem> (_item));
      }

    template<typename _TpItem>
      _TpItem& _List<_TpItem>::push_front (const _TpItem &_item)
      {
        return _push_front (new _ListItem<_TpItem> (_item));
      }

    template<typename _TpItem>
      _TpItem& _List<_TpItem>::push_back (const _TpItem &_item)
      {
        return _push_back (new _ListItem<_TpItem> (_item));
      }

    template<typename _TpItem>
      _TpItem* _List<_TpItem>::pop_front ()
      {
        _TpItem *_ptr = NULL;

        if (_head)
        {
          _ListItem<_TpItem> *_ptr_item = _head;
          _head = static_cast<_ListItem<_TpItem> *> (_head->_next);
          _ptr = new _TpItem (_ptr_item->_data);

          delete _ptr_item;
        }

        if (! _head)
          _tail = NULL;

       _size--;
        
        return _ptr;
      }

    template<typename _TpItem>
      _TpItem* _List<_TpItem>::front ()
      {
        _TpItem *_ptr = NULL;

        if (_head)
          _ptr = &(_head->_data);
        
        return _ptr;
      }

    template<typename _TpItem>
      const unsigned long _List<_TpItem>::size () const
      {
        return _size;
      }

    template<typename _TpItem>
      const bool _List<_TpItem>::empty () const
      {
        return (! _head);
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

    template<typename _TpItem>
      _ListConstIterator<_TpItem> _List<_TpItem>::find (const _TpItem &_item) const
      {
        const_iterator it    = begin ();
        const_iterator itEnd = end ();

        while (it != end () && *it != _item)
          ++it;

        return it;
      }

    template<typename _TpItem>
      class list : public _List<_TpItem>
      {
      };
  }
}

#endif
