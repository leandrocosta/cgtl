#ifndef _LIST_H_
#define _LIST_H_

#include "list_item_base.h"
#include "list_item.h"
#include "list_iterator_base.h"
#include "list_iterator.h"


namespace cgt
{
  namespace list
  {
    template<typename _TpItem>
      class _List
      {
        private:
          typedef _List<_TpItem>     _Self;
          typedef _ListItem<_TpItem> _Item;

        public:
          typedef _ListIterator<_TpItem>            iterator;
          typedef _ListIterator<_TpItem, _TpConst>  const_iterator;

        public:
          _List () : _head (NULL), _tail (NULL), _size (0) { }
          _List (const _List& _l) : _head (NULL), _tail (NULL), _size (0)
          {
            *this = _l;
          }
          virtual ~_List ()
          {
            _Item *_ptr = NULL;

            while (_head)
            {
              _ptr = _head;
              _head = static_cast<_Item *>(_ptr->_next);
              delete _ptr;
            }
          }

        public:
          _Self& operator=(const _Self& _l);

        private:
          _TpItem& _push_front (_Item *_ptr);
          _TpItem& _push_back (_Item *_ptr);

        public:
          _TpItem& insert (const _TpItem& _item);
          void remove (const _TpItem& _item);
          _TpItem& push_front (const _TpItem& _item);
          _TpItem& push_back (const _TpItem& _item);
          _TpItem* pop_front ();
          _TpItem* front ();
          _TpItem* back ();

          const unsigned long size () const;
          const bool empty () const;

        public:
          iterator begin () { return iterator (_head); }
          iterator end () { return iterator (NULL); }
          const_iterator begin () const { return const_iterator (_head); }
          const_iterator end () const { return const_iterator (NULL); }

        public:
          iterator find (const _TpItem& _item);
          const_iterator find (const _TpItem& _item) const;

        private:
          _Item*        _head;
          _Item*        _tail;
          unsigned long _size;
      };

    template<typename _TpItem>
      _List<_TpItem>& _List<_TpItem>::operator=(const _Self& _l)
      {
        const_iterator it;
        const_iterator itEnd = _l.end ();

        for (it = _l.begin (); it != itEnd; ++it)
          insert (*it);

        return *this;
      }

    template<typename _TpItem>
      _TpItem& _List<_TpItem>::_push_front (_Item *_ptr)
      {
        _ptr->_next = _head;
        _head = _ptr;

        if (! _tail)
          _tail = _ptr;

        _size++;

        return _ptr->_data;
      }

    template<typename _TpItem>
      _TpItem& _List<_TpItem>::_push_back (_Item *_ptr)
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
      _TpItem& _List<_TpItem>::insert (const _TpItem& _item)
      {
        return _push_back (new _Item (_item));
      }

    template<typename _TpItem>
      void _List<_TpItem>::remove (const _TpItem& _item)
      {
        _Item* _ptr = NULL;

        if (_head->_data == _item)
        {
          _ptr = _head;
          _head = static_cast<_Item *> (_head->_next);
          delete _ptr;
        }
        else
        {
          _Item* _ptr_prv = _head;
          _ptr = static_cast<_Item *> (_ptr_prv->_next);

          while (_ptr)
          {
            if (_ptr->_data == _item)
            {
              if (_tail == _ptr)
                _tail = _ptr_prv;

              _ptr_prv->_next = _ptr->_next;
              delete _ptr;

              break;
            }
            else
            {
              _ptr_prv = _ptr;
              _ptr = static_cast<_Item *> (_ptr->_next);
            }
          }
        }
      }

    template<typename _TpItem>
      _TpItem& _List<_TpItem>::push_front (const _TpItem& _item)
      {
        return _push_front (new _Item (_item));
      }

    template<typename _TpItem>
      _TpItem& _List<_TpItem>::push_back (const _TpItem& _item)
      {
        return _push_back (new _Item (_item));
      }

    template<typename _TpItem>
      _TpItem* _List<_TpItem>::pop_front ()
      {
        _TpItem *_ptr = NULL;

        if (_head)
        {
          _Item *_ptr_item = _head;
          _head = static_cast<_Item *> (_head->_next);
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
      _TpItem* _List<_TpItem>::back ()
      {
        _TpItem *_ptr = NULL;

        if (_tail)
          _ptr = &(_tail->_data);
        
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
      _ListIterator<_TpItem> _List<_TpItem>::find (const _TpItem& _item)
      {
        return static_cast<const _Self *>(this)->find (_item);
      }

    template<typename _TpItem>
      _ListIterator<_TpItem, _TpConst> _List<_TpItem>::find (const _TpItem& _item) const
      {
        const_iterator it    = begin ();
        const_iterator itEnd = end ();

        while (it != end () && *it != _item)
          ++it;

        return it;
      }

    template<typename _TpItem>
      class list : public _List<_TpItem> { };
  }
}

#endif
