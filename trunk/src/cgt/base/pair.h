#ifndef _PAIR_H_
#define _PAIR_H_


namespace cgt
{
  namespace base
  {
    template<typename _Tp1, typename _Tp2>
      class pair
      {
        public:
          pair (const _Tp1& _i1, const _Tp2& _i2) : first (_i1), second (_i2) { }

        public:
          _Tp1 first;
          _Tp2 second;
      };
  }
}

#endif
