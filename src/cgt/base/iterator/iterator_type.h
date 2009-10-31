#ifndef _ITERATOR_TYPE_H_
#define _ITERATOR_TYPE_H_


namespace cgt
{
  namespace base
  {
    namespace iterator
    {
      template<typename _TpItem>
        struct _TpCommon
        {
          typedef _TpItem* pointer;
          typedef _TpItem& reference;
        };

      template<typename _TpItem>
        struct _TpConst
        {
          typedef const _TpItem* pointer;
          typedef const _TpItem& reference;
        };
    }
  }
}

#endif
