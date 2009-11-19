#ifndef _HASH_FUNC_H_
#define _HASH_FUNC_H_


namespace cgt
{
  namespace base
  {
    template<typename _TpKey>
      struct _HashFunc
      {
        const size_t operator()(const _TpKey& _key) const;
      };

    template<typename _TpKey>
      const size_t _HashFunc<_TpKey>::operator()(const _TpKey& _key) const
      {
        size_t _h = 0;

        size_t numbytes = sizeof (_TpKey);

        for (size_t i = 0; i < numbytes; i++)
          _h = 5*_h + *(reinterpret_cast<const unsigned char *>(&_key)+i);

        return _h;
      }

    template<>
      const size_t _HashFunc<int>::operator()(const int& _key) const
      {
        return _key;
      }
  }
}

#endif
