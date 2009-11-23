/*
 * CGTL - A graph template library for C++
 * ---------------------------------------
 * Copyright (C) 2009 Leandro Costa
 *
 * This file is part of CGTL.
 *
 * CGTL is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as
 * published by the Free Software Foundation, either version 3 of
 * the License, or (at your option) any later version.
 *
 * CGTL is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with CGTL. If not, see <http://www.gnu.org/licenses/>.
 */

/*!
 * \file cgt/base/hash_iterator.h
 * \brief [brief description]
 * \author Leandro Costa
 * \date 2009
 *
 * $LastChangedDate$
 * $LastChangedBy$
 * $Revision$
 */

#ifndef __CGTL__CGT_BASE_HASH_ITERATOR_H_
#define __CGTL__CGT_BASE_HASH_ITERATOR_H_

#include "hash_item.h"
#include "pair.h"
#include "iterator/iterator_ptr.h"


namespace cgt
{
  namespace base
  {
    template<typename _TpKey, typename _TpItem, typename _Alloc>
      class _Hash;


    template<typename _TpKey, typename _TpItem, typename _Alloc, template<typename> class _TpIterator = cgt::base::iterator::_TpCommon>
      class _HashIterator : public cgt::base::iterator::_IteratorPtr<_HashItem<pair<const _TpKey, _TpItem> >, _TpIterator>
    {
      private:
        friend class _HashIterator<_TpKey, _TpItem, _Alloc, cgt::base::iterator::_TpConst>;

      private:
        typedef cgt::base::iterator::_IteratorPtr<_HashItem<pair<const _TpKey, _TpItem> >, _TpIterator>  _Base;
        typedef _HashIterator<_TpKey, _TpItem, _Alloc, _TpIterator>                 _Self;
        typedef _HashIterator<_TpKey, _TpItem, _Alloc, cgt::base::iterator::_TpCommon>                   _SelfCommon;
        typedef _HashItem<pair<const _TpKey, _TpItem> >                             _Item;
        typedef _Hash<_TpKey, _TpItem, _Alloc>                                      _Hsh;
        typedef typename _TpIterator<pair<const _TpKey, _TpItem> >::pointer         pointer;
        typedef typename _TpIterator<pair<const _TpKey, _TpItem> >::reference       reference;

      private:
        using _Base::_ptr;

      public:
        _HashIterator () : _Base (NULL), _ptr_hash (NULL) { }
        _HashIterator (_Item* _p, _Hsh* _p_hsh) : _Base (_p), _ptr_hash (_p_hsh) { }
        _HashIterator (const _SelfCommon& _it) : _Base (_it._ptr), _ptr_hash (_it._ptr_hash) { }

      private:
        void _incr ()
        {
          if (_ptr->_next)
            _ptr = _ptr->_next;
          else
          {
            size_t _pos = _ptr_hash->_get_position (_ptr->_item.first) + 1;

            while (_pos < _ptr_hash->_tabsize && ! _ptr_hash->_table [_pos])
              _pos++;

            if (_pos < _ptr_hash->_tabsize)
              _ptr = _ptr_hash->_table [_pos];
            else
              _ptr = NULL;
          }
        };

      public:
        reference operator*() const { return _ptr->_item; }
        pointer operator->() const { return &(operator*()); }

        _Self& operator++() { _incr (); return *this; }
        const _Self operator++(int) { return _Self (_ptr++); }

      private:
        _Hsh* _ptr_hash;
    };
  }
}

#endif // __CGTL__CGT_BASE_HASH_ITERATOR_H_
