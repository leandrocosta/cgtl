#ifndef _LIST_H_
#define _LIST_H_

#include "list_item_base.h"
#include "list_item.h"
#include "list_iterator_base.h"
#include "list_iterator.h"
#include "../alloc/allocator.h"
using namespace cgt::alloc;


namespace cgt
{
  namespace list
  {
    template<typename _TpItem, typename _Alloc = _Allocator<_ListItem<_TpItem> > >
      class _List
      {
        private:
          typedef _List<_TpItem, _Alloc>  _Self;
          typedef _ListItem<_TpItem>      _Item;

        public:
          typedef _ListIterator<_TpItem>            iterator;
          typedef _ListIterator<_TpItem, _TpConst>  const_iterator;

        private:
          typedef typename _Alloc::template rebind<_ListItem<_TpItem> >::other allocator_type;

        public:
          _List () : _head (NULL), _tail (NULL), _size (0) { }
          _List (const _List& _l) : _head (NULL), _tail (NULL), _size (0) { *this = _l; }
          virtual ~_List () { _remove_all (); }

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

          void make_heap ();
          void _rebuild_heap (unsigned int i, _TpItem* _arrayItem[]);
          _TpItem* pop_heap ();

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

          allocator_type  _alloc;
      };

    template<typename _TpItem, typename _Alloc>
      _List<_TpItem, _Alloc>& _List<_TpItem, _Alloc>::operator=(const _Self& _l)
      {
        const_iterator it;
        const_iterator itEnd = _l.end ();

        for (it = _l.begin (); it != itEnd; ++it)
          insert (*it);

        return *this;
      }

    template<typename _TpItem, typename _Alloc>
      _TpItem& _List<_TpItem, _Alloc>::_push_front (_Item *_ptr)
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

    template<typename _TpItem, typename _Alloc>
      _TpItem& _List<_TpItem, _Alloc>::_push_back (_Item *_ptr)
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

    template<typename _TpItem, typename _Alloc>
      _ListItem<_TpItem>* _List<_TpItem, _Alloc>::_find (const _TpItem& _item) const
      {
        _Item* _ptr = _head;

        while (_ptr != NULL && _ptr->_data != _item)
          _ptr = static_cast<_Item *>(_ptr->_next);

        return _ptr;
      }

    template<typename _TpItem, typename _Alloc>
      _TpItem* _List<_TpItem, _Alloc>::_get (_Item* _ptr_item) const
      {
        _TpItem* _ptr = NULL;

        if (_ptr_item)
          _ptr = &(_ptr_item->_data);

        return _ptr;
      }

    template<typename _TpItem, typename _Alloc>
      _TpItem* _List<_TpItem, _Alloc>::_pop (_Item* _ptr_item)
      {
        _TpItem* _ptr = NULL;

        if (_ptr_item)
        {
          _unlink (_ptr_item);
          _ptr = new _TpItem (_ptr_item->_data);
          _alloc.destroy (_ptr_item);
          _alloc.deallocate (_ptr_item, 1);
        }

        return _ptr;
      }

    template<typename _TpItem, typename _Alloc>
      void _List<_TpItem, _Alloc>::_unlink (const _ListItem<_TpItem>* const _ptr)
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

    template<typename _TpItem, typename _Alloc>
      void _List<_TpItem, _Alloc>::_remove (_Item* _ptr)
      {
        if (_ptr)
        {
          _unlink (_ptr);
          _alloc.destroy (_ptr);
          _alloc.deallocate (_ptr, 1);
        }
      }

    template<typename _TpItem, typename _Alloc>
      void _List<_TpItem, _Alloc>::_remove_all ()
      {
        while (_head)
          _remove (_head);
      }

    template<typename _TpItem, typename _Alloc>
      _TpItem& _List<_TpItem, _Alloc>::insert (const _TpItem& _item)
      {
        _Item* _ptr = _alloc.allocate (1);
        _alloc.construct (_ptr, _Item (_item));
        return _push_back (_ptr);
      }

    template<typename _TpItem, typename _Alloc>
      _TpItem& _List<_TpItem, _Alloc>::push_front (const _TpItem& _item)
      {
        _Item* _ptr = _alloc.allocate (1);
        _alloc.construct (_ptr, _Item (_item));
        return _push_front (_ptr);
      }

    template<typename _TpItem, typename _Alloc>
      _TpItem& _List<_TpItem, _Alloc>::push_back (const _TpItem& _item)
      {
        _Item* _ptr = _alloc.allocate (1);
        _alloc.construct (_ptr, _Item (_item));
        return _push_back (_ptr);
      }

    template<typename _TpItem, typename _Alloc>
      _TpItem* _List<_TpItem, _Alloc>::pop_front ()
      {
        return _pop (_head);
      }

    template<typename _TpItem, typename _Alloc>
      _TpItem* _List<_TpItem, _Alloc>::pop_back ()
      {
        return _pop (_tail);
      }

    template<typename _TpItem, typename _Alloc>
      _TpItem* _List<_TpItem, _Alloc>::front ()
      {
        return _get (_head);
      }

    template<typename _TpItem, typename _Alloc>
      _TpItem* _List<_TpItem, _Alloc>::back ()
      {
        return _get (_tail);
      }

    template<typename _TpItem, typename _Alloc>
      const unsigned long _List<_TpItem, _Alloc>::size () const
      {
        return _size;
      }

    template<typename _TpItem, typename _Alloc>
      const bool _List<_TpItem, _Alloc>::empty () const
      {
        return (! _head);
      }

    template<typename _TpItem, typename _Alloc>
      void _List<_TpItem, _Alloc>::make_heap ()
      {
        _TpItem* _arrayItem [_size];

        iterator it;
        iterator itEnd = end ();
        int i = 0;

        for (it = begin (); it != itEnd; ++it)
          _arrayItem [i++] = &(*it);

        i = _size/2 - 1;

        while (i >= 0)
          _rebuild_heap (i--, _arrayItem);
      }

    template<typename _TpItem, typename _Alloc>
      void _List<_TpItem, _Alloc>::_rebuild_heap (unsigned int i, _TpItem* _arrayItem[])
      {
        _TpItem item = *(_arrayItem [i]);

        unsigned int k = 2*i+1;

        while (k < _size)
        {
          if (k+1 < _size && *(_arrayItem[k+1]) < *(_arrayItem[k]))
            k++;

          if (*(_arrayItem [k]) < item)
          {
            *(_arrayItem [i]) = *(_arrayItem [k]);
            i = k;
            k = 2*i+1;
          }
          else
            break;
        }

        *(_arrayItem [i]) = item;
      }

    template<typename _TpItem, typename _Alloc>
      _TpItem* _List<_TpItem, _Alloc>::pop_heap ()
      {
        _TpItem* _ptr = NULL;
        
        if (_head)
        {
          if (_head == _tail)
            _ptr = _pop (_head);
          else
          {
            _ptr = new _TpItem (_head->_data);

            _TpItem* _arrayItem [_size];

            iterator it;
            iterator itEnd = end ();
            int i = 0;

            for (it = begin (); it != itEnd; ++it)
              _arrayItem [i++] = &(*it);

            _TpItem* _p = _pop (_tail);
            _head->_data = *_p;
            delete _p;

            _rebuild_heap (0, _arrayItem);
          }
        }

        return _ptr;
      }

    template<typename _TpItem, typename _Alloc>
      _ListIterator<_TpItem> _List<_TpItem, _Alloc>::find (const _TpItem& _item)
      {
        return static_cast<const _Self *>(this)->find (_item);
      }

    template<typename _TpItem, typename _Alloc>
      _ListIterator<_TpItem, _TpConst> _List<_TpItem, _Alloc>::find (const _TpItem& _item) const
      {
        return const_iterator (_find (_item));
      }

    template<typename _TpItem, typename _Alloc>
      void _List<_TpItem, _Alloc>::remove (const _TpItem& _item)
      {
        _remove (_find (_item));
      }

    template<typename _TpItem, typename _Alloc>
      void _List<_TpItem, _Alloc>::clear ()
      {
        _remove_all ();
      }

    template<typename _TpItem>
      class list : public _List<_TpItem> { };
  }
}

#endif
