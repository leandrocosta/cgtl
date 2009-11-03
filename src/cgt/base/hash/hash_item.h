#ifndef _HASH_ITEM_H_
#define _HASH_ITEM_H_


namespace cgt
{
  namespace base
  {
    namespace hash
    {
      template<typename _TpKey, typename _TpValue>
        class _HashItem
        {
          public:
            _HashItem (const _TpKey& _k, const _TpValue& _v) : _key (_k), _value (_v), _next (NULL) { }

          public:
            _TpKey& key () { return _key; }
            const _TpKey& key () const { return _key; }
            _TpValue& value () { return _value; }
            const _TpValue& value () const { return _value; }

          public:
            _TpKey      _key;
            _TpValue    _value;
            _HashItem*  _next;
        };
    }
  }
}

#endif
