#ifndef _HASH_H_
#define _HASH_H_

#include <string.h>
#include "hash_item.h"
#include "hash_iterator.h"
#include "../alloc/allocator.h"
#include "hash_func.h"
#include "../pair.h"
using namespace cgt::base;


namespace cgt
{
  namespace base
  {
    template<typename _TpKey, typename _TpItem, typename _Alloc = cgt::base::alloc::_Allocator<_HashItem<pair<const _TpKey, _TpItem> > > >
      class _Hash
      {
        private:
          friend class _HashIterator<_TpKey, _TpItem, _Alloc, _TpCommon>;
          friend class _HashIterator<_TpKey, _TpItem, _Alloc, _TpConst>;

        private:
          typedef _HashItem<pair<const _TpKey, _TpItem> >  _Item;
          typedef _HashFunc<_TpKey>           _Func;

        private:
          typedef typename _Alloc::template rebind<_Item>::other allocator_type;

        public:
          typedef _HashIterator<_TpKey, _TpItem, _Alloc>            iterator;
          typedef _HashIterator<_TpKey, _TpItem, _Alloc, _TpConst>  const_iterator;

        public:
          _Hash () : _size (0), _tabsize (2) { _init (); }
          virtual ~_Hash () { _remove_all (); free (_table); }

        private:
          void _init ();
          void _increase ();
          void _insert (_Item* const _p);
          _Item* _pop (_Item** const _p);
          void _remove_all ();
          const size_t _get_position (const _TpKey& _key) const;
          _TpItem** _get_head ();

        public:
          void insert (const _TpKey& _key, const _TpItem& _item);

        public:
          _TpItem* operator[](const _TpKey& _key);

        public:
          void dump () const;

          iterator begin ()
          {
            size_t _pos = 0;

            while (_pos < _tabsize && ! _table [_pos])
              _pos++;

            if (_pos < _tabsize)
              return iterator (_table [_pos], this);
            else
              return end ();
          }
          iterator end (){ return iterator (NULL, this); }
          const_iterator begin () const
          {
            size_t _pos = 0;

            while (! _table [_pos] && _pos < _tabsize)
              _pos++;

            if (_pos < _tabsize)
              return iterator (_table [_pos], this);
            else
              return end ();
          }
          const_iterator end () const { return const_iterator (NULL, this); }

        private:
          _Item** _table;
          size_t  _size;
          size_t  _tabsize;

          _Func           _hash_func;
          allocator_type  _alloc;
      };


    template<typename _TpKey, typename _TpItem, typename _Alloc>
      void _Hash<_TpKey, _TpItem, _Alloc>::_init ()
      {
        _table = (_Item **) malloc (_tabsize * sizeof (_Item **));
        bzero (_table, _tabsize * sizeof (_Item **));
      }

    template<typename _TpKey, typename _TpItem, typename _Alloc>
      void _Hash<_TpKey, _TpItem, _Alloc>::_increase ()
      {
        _tabsize *= 2;
        _table = (_Item **) realloc (_table, _tabsize * sizeof (_Item **));
        bzero (&(_table [_size]), (_tabsize/2) * sizeof (_Item **));

        for (size_t i = 0; i < _tabsize/2; i++)
        {
          _Item** _ptr = &(_table [i]);

          while (*_ptr)
          {
            if (_get_position ((*_ptr)->_item.first) != i)
              _insert (_pop (_ptr));
            else
              _ptr = &((*_ptr)->_next);
          }
        }
      }

    template<typename _TpKey, typename _TpItem, typename _Alloc>
      void _Hash<_TpKey, _TpItem, _Alloc>::_insert (_Item* const _p)
      {
        _Item** _ptr = &(_table [_get_position (_p->_item.first)]);
        while (*_ptr)
          _ptr = &((*_ptr)->_next);
        *_ptr = _p;

        _size++;
      }

    template<typename _TpKey, typename _TpItem, typename _Alloc>
      _HashItem<pair<const _TpKey, _TpItem> >* _Hash<_TpKey, _TpItem, _Alloc>::_pop (_Item** const _p)
      {
        _Item* _ptr = *_p;
        *_p = (*_p)->_next;
        _ptr->_next = NULL;
        _size--;

        return _ptr;
      }

    template<typename _TpKey, typename _TpItem, typename _Alloc>
      void _Hash<_TpKey, _TpItem, _Alloc>::_remove_all ()
      {
        for (size_t i = 0; i < _tabsize; i++)
        {
          while (_table [i])
          {
            _Item* _ptr = _table [i];
            _table [i] = _table [i]->_next;
            _alloc.destroy (_ptr);
            _alloc.deallocate (_ptr, 1);
          }
        }
      }

    template<typename _TpKey, typename _TpItem, typename _Alloc>
      const size_t _Hash<_TpKey, _TpItem, _Alloc>::_get_position (const _TpKey& _key) const
      {
        return (_hash_func (_key) % _tabsize);
      }

    template<typename _TpKey, typename _TpItem, typename _Alloc>
      _TpItem** _Hash<_TpKey, _TpItem, _Alloc>::_get_head ()
      {
        _TpItem** _ptr = &(_table [0]);

        while (! *_ptr)
          _ptr++;

        return _ptr;
      }

    template<typename _TpKey, typename _TpItem, typename _Alloc>
      void _Hash<_TpKey, _TpItem, _Alloc>::insert (const _TpKey& _key, const _TpItem& _item)
      {
        if (_size == _tabsize)
          _increase ();

        _Item* _ptr = _alloc.allocate (1);
        _alloc.construct (_ptr, _Item (pair<const _TpKey, _TpItem> (_key, _item)));
        _insert (_ptr);
      }

    template<typename _TpKey, typename _TpItem, typename _Alloc>
      _TpItem* _Hash<_TpKey, _TpItem, _Alloc>::operator[](const _TpKey& _key)
      {
        _TpItem* _ptr = NULL;

        _Item* _p = _table [_get_position (_key)];

        while (_p && _p->_key != _key)
          _p = _p->_next;

        if (_p)
          _ptr = &(_p->_value);

        return _ptr;
      }

    template<typename _TpKey, typename _TpItem, typename _Alloc>
      void _Hash<_TpKey, _TpItem, _Alloc>::dump () const
      {
        cout << "dump - _tabsize: " << _tabsize << endl;

        for (size_t i = 0; i < _tabsize; i++)
        {
          _Item* _ptr = _table [i];

          while (_ptr)
          {
            cout << "dump - pos: " << i << ", key: " << _ptr->_item.first << ", value: " << _ptr->_item.second << ", _get_position (): " << _get_position (_ptr->_item.first) << endl;
            _ptr = _ptr->_next;
          }
        }
      }

    template<typename _TpKey, typename _TpItem>
      class hash : public _Hash<_TpKey, _TpItem> { };
  }
}


#endif
