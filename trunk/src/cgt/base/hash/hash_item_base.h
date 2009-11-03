#ifndef _HASH_ITEM_BASE_H_
#define _HASH_ITEM_BASE_H_


namespace cgt
{
  namespace base
  {
    namespace hash
    {
      template<typename _TpKey, typename _TpValue>
        class _HashItemBase
        {
          public:
            _HashItemBase () : _next (NULL) { }

          public:
            _HashItemBase*  _next;
        };
    }
  }
}

#endif
