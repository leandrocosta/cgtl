#ifndef _HASH_ITEM_H_
#define _HASH_ITEM_H_


namespace cgt
{
  namespace base
  {
    template<typename _TpItem>
      class _HashItem
      {
        public:
          _HashItem (const _TpItem& _i) : _item (_i), _next (NULL) { }

        public:
          _TpItem     _item;
          _HashItem*  _next;
      };
  }
}

#endif
