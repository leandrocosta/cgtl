#ifndef _LIST_H_
#define _LIST_H_

#include "list_item_base.h"
#include "list_item.h"
#include "list_iterator_base.h"
#include "list_iterator.h"
#include "../alloc/allocator.h"


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
            _remove_all ();
          }

        public:
          _Self& operator=(const _Self& _l);

        private:
          _TpItem& _push_front (_Item *_ptr);
          _TpItem& _push_back (_Item *_ptr);
          _Item* _find (const _TpItem& _item) const;
          _TpItem* _get (_Item* _ptr_item) const;
          _TpItem* _pop (_Item* _ptr_item);
          void _unlink (const _Item* const _ptr);
          void _remove (_Item* _ptr);
          void _remove_all ();

        public:
          _TpItem& insert (const _TpItem& _item);
          _TpItem& push_front (const _TpItem& _item);
          _TpItem& push_back (const _TpItem& _item);
          _TpItem* pop_front ();
          _TpItem* pop_back ();
          _TpItem* front ();
            _TpItem* back ();
          void remove (const _TpItem& _item);
          void clear ();

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
        if (! _tail)
          _tail = _ptr;
        else
        {
          _ptr->_next = _head;
          _head->_prev = _ptr;
        }

        _head = _ptr;
        _size++;

        return _ptr->_data;
      }

    template<typename _TpItem>
      _TpItem& _List<_TpItem>::_push_back (_Item *_ptr)
      {
        if (! _head)
          _head = _ptr;
        else
        {
          _ptr->_prev = _tail;
          _tail->_next = _ptr;
        }

        _tail = _ptr;
        _size++;

        return _ptr->_data;
      }

    template<typename _TpItem>
      _ListItem<_TpItem>* _List<_TpItem>::_find (const _TpItem& _item) const
      {
        _Item* _ptr = _head;

        while (_ptr != NULL && _ptr->_data != _item)
          _ptr = static_cast<_Item *>(_ptr->_next);

        return _ptr;
      }

    template<typename _TpItem>
      _TpItem* _List<_TpItem>::_get (_Item* _ptr_item) const
      {
        _TpItem* _ptr = NULL;

        if (_ptr_item)
          _ptr = &(_ptr_item->_data);

        return _ptr;
      }

    template<typename _TpItem>
      _TpItem* _List<_TpItem>::_pop (_Item* _ptr_item)
      {
        _TpItem* _ptr = NULL;

        if (_ptr_item)
        {
          _unlink (_ptr_item);
          _ptr = new _TpItem (_ptr_item->_data);
          delete _ptr_item;
        }

        return _ptr;
      }

    template<typename _TpItem>
      void _List<_TpItem>::_unlink (const _ListItem<_TpItem>* const _ptr)
      {
        if (_ptr->_prev)
          _ptr->_prev->_next = _ptr->_next;
        else
          _head = static_cast<_Item *>(_ptr->_next);

        if (_ptr->_next)
          _ptr->_next->_prev = _ptr->_prev;
        else
          _tail = static_cast<_Item *>(_ptr->_prev);

        _size--;
      }

    template<typename _TpItem>
      void _List<_TpItem>::_remove (_Item* _ptr)
      {
        if (_ptr)
        {
          _unlink (_ptr);
          delete _ptr;
        }
      }

    template<typename _TpItem>
      void _List<_TpItem>::_remove_all ()
      {
        while (_head)
          _remove (_head);
      }

    template<typename _TpItem>
      _TpItem& _List<_TpItem>::insert (const _TpItem& _item)
      {
        return _push_back (new _Item (_item));
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
        return _pop (_head);
      }

    template<typename _TpItem>
      _TpItem* _List<_TpItem>::pop_back ()
      {
        return _pop (_tail);
      }

    template<typename _TpItem>
      _TpItem* _List<_TpItem>::front ()
      {
        return _get (_head);
      }

    template<typename _TpItem>
      _TpItem* _List<_TpItem>::back ()
      {
        return _get (_tail);
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
        return const_iterator (_find (_item));
      }

    template<typename _TpItem>
      void _List<_TpItem>::remove (const _TpItem& _item)
      {
        _remove (_find (_item));
      }

    template<typename _TpItem>
      void _List<_TpItem>::clear ()
      {
        _remove_all ();
      }

    template<typename _TpItem>
      class list : public _List<_TpItem> { };
  }
}

#endif
