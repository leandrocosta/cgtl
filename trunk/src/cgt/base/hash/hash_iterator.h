#ifndef _HASH_ITERATOR_H_
#define _HASH_ITERATOR_H_

#include "../iterator/iterator_ptr.h"
#include "hash_item.h"


namespace cgt
{
  namespace base
  {
    namespace hash
    {
      using namespace cgt::base::iterator;

      template<typename _TpKey, typename _TpItem, typename _Alloc>
        class _Hash;


      template<typename _TpKey, typename _TpItem, typename _Alloc, template<typename> class _TpIterator = _TpCommon>
        class _HashIterator : public _IteratorPtr<_HashItem<_TpKey, _TpItem>, _TpIterator>
      {
        private:
          friend class _HashIterator<_TpKey, _TpItem, _Alloc, _TpConst>;

        private:
          typedef _IteratorPtr<_HashItem<_TpKey, _TpItem>, _TpIterator>  _Base;
          typedef _HashIterator<_TpKey, _TpItem, _Alloc, _TpIterator>     _Self;
          typedef _HashIterator<_TpKey, _TpItem, _Alloc, _TpCommon>       _SelfCommon;
          typedef _HashItem<_TpKey, _TpItem>                              _Item;
          typedef _Hash<_TpKey, _TpItem, _Alloc>                          _Hsh;
          typedef typename _TpIterator<_Item>::pointer                  pointer;
          typedef typename _TpIterator<_Item>::reference                reference;

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
              size_t _pos = _ptr_hash->_get_position (_ptr->_key) + 1;

              while (_pos < _ptr_hash->_tabsize && ! _ptr_hash->_table [_pos])
                _pos++;

              if (_pos < _ptr_hash->_tabsize)
                _ptr = _ptr_hash->_table [_pos];
              else
                _ptr = NULL;
            }
          };

        public:
          reference operator*() const { return *_ptr; }
          pointer operator->() const { return &(operator*()); }

          _Self& operator++() { _incr (); return *this; }
          const _Self operator++(int) { return _Self (_ptr++); }

        private:
          _Hsh* _ptr_hash;
      };
    }
  }
}

#endif
