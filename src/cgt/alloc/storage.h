#ifndef _STORAGE_H_
#define _STORAGE_H_

namespace cgt
{
  namespace alloc
  {
    template<typename _TpItem, size_t _ChunkSize = 0xFFFF /* 64k-1 */>
      class _Storage
      {
        private:
          class _Chunk
          {
            public:
              class _Block
              {
                public:
                  _Block () : _next (NULL) { }

                public:
                  unsigned char _data [sizeof (_TpItem)];
                  _Block* _next;
              };

            public:
              _Chunk () : _next (NULL) { _init (); }

            private:
              void _init ()
              {
                unsigned int i = 0;

                for (i = 0; i < _ChunkSize-1; i++)
                  reinterpret_cast<_Block *>(_block)[i]._next = &(reinterpret_cast<_Block *>(_block)[i+1]);

                reinterpret_cast<_Block *>(_block)[_ChunkSize-1]._next = NULL;
              }

            public:
              char _block [_ChunkSize * sizeof (_Block)];
              _Chunk* _next;
          };

        private:
          typedef typename _Chunk::_Block _Block;

        public:
          _Storage () : _tail (NULL), _free (NULL) { _init (); }
          virtual ~_Storage () { _destroy (); }

        private:
          void _init ();
          void _add_chunk ();
          void _destroy ();

        public:
          _TpItem* allocate (size_t size);
          void deallocate (_TpItem* _ptr);

        private:
          _Chunk* _head;
          _Chunk* _tail;
          _Block* _free;
      };


    template<typename _TpItem, size_t _ChunkSize>
      void _Storage<_TpItem, _ChunkSize>::_init ()
      {
        if (! _head)
        {
          cout << "_init ()" << endl;
          _head = new _Chunk ();
          _free = reinterpret_cast<_Block *>(_head->_block);
          _tail = _head;
        }
      }

    template<typename _TpItem, size_t _ChunkSize>
      void _Storage<_TpItem, _ChunkSize>::_add_chunk ()
      {
        _tail->_next = new _Chunk ();
        _free = reinterpret_cast<_Block *>(_tail->_block);
        _tail = _tail->_next;
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
      _TpItem* _Storage<_TpItem, _ChunkSize>::allocate (size_t size)
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



#endif
