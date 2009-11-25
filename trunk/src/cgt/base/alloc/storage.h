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
 * \file cgt/base/alloc/storage.h
 * \brief Contains definitions of storage and chunk, used by allocator.
 * \author Leandro Costa
 * \date 2009
 */

#ifndef __CGTL__CGT_BASE_ALLOC_STORAGE_H_
#define __CGTL__CGT_BASE_ALLOC_STORAGE_H_

#include "cgt/base/exception/mem_except.h"


namespace cgt
{
  namespace base
  {
    namespace alloc
    {
      /*
       * Based on the example presented in The C++ Programming Language, 3rd Edition, by Bjarne Stroustrup, page 570
       */

      template<typename _TpItem, size_t _ChunkSize = 0xFFFF /* 64k-1 */>
        class _Storage
        {
          private:
            class _Chunk
            {
              public:
                struct _Block
                {
                  _Block* _next;
                };

              public:
                _Chunk () : _next (NULL) { _init (); }

              private:
                void _init ()
                {
                  size_t size = sizeof (_TpItem);
                  char* _ptr_last = &(_block [(_ChunkSize-1) * size]);

                  for (char* _ptr = _block; _ptr < _ptr_last; _ptr += size)
                    reinterpret_cast<_Block *>(_ptr)->_next = reinterpret_cast<_Block *>(_ptr + size);

                  reinterpret_cast<_Block *>(_ptr_last)->_next = NULL;
                }

              public:
                char _block [_ChunkSize * sizeof (_TpItem)];
                _Chunk* _next;
            };

          private:
            typedef typename _Chunk::_Block _Block;

          public:
            _Storage () : _head (NULL), _free (NULL) { }
            virtual ~_Storage () { _destroy (); }

          private:
            void _add_chunk ();
            void _destroy ();

          public:
            _TpItem* allocate ();
            void deallocate (_TpItem* _ptr);

          private:
            _Chunk* _head;
            _Block* _free;
        };


      template<typename _TpItem, size_t _ChunkSize>
        void _Storage<_TpItem, _ChunkSize>::_add_chunk ()
        {
          _Chunk* _ptr = new _Chunk ();

          if (! _ptr)
            throw cgt::base::exception::mem_except ("Not available memory");

          _ptr->_next = _head;
          _head = _ptr;
          _free = reinterpret_cast<_Block *>(_ptr->_block);
        }

      template<typename _TpItem, size_t _ChunkSize>
        void _Storage<_TpItem, _ChunkSize>::_destroy ()
        {
          _Chunk* _ptr = NULL;

          while (_head)
          {
            _ptr = _head;
            _head = _head->_next;
            delete _ptr;
          }
        }

      template<typename _TpItem, size_t _ChunkSize>
        _TpItem* _Storage<_TpItem, _ChunkSize>::allocate ()
        {
          if (! _free)
            _add_chunk ();

          _TpItem* _ptr = reinterpret_cast<_TpItem *>(_free);
          _free = _free->_next;

          return _ptr;
        }

      template<typename _TpItem, size_t _ChunkSize>
        void _Storage<_TpItem, _ChunkSize>::deallocate (_TpItem* _ptr)
        {
          reinterpret_cast<_Block *>(_ptr)->_next = _free;
          _free = reinterpret_cast<_Block *>(_ptr);
        }
    }
  }
}

#endif // __CGTL__CGT_BASE_ALLOC_STORAGE_H_ // __CGTL__CGT_BASE_ALLOC_STORAGE_H_
