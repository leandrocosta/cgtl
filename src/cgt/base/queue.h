#ifndef _QUEUE_H_
#define _QUEUE_H_

#include "list/list.h"


namespace cgt
{
  namespace base
  {
    template<typename _TpItem>
      class queue : private cgt::base::list::list<_TpItem>
    {
      private:
        typedef cgt::base::list::list<_TpItem> _Base;

      public:
        using _Base::iterator;
        using _Base::const_iterator;
        using _Base::begin;
        using _Base::end;
        using _Base::empty;

      public:
        void insert (const _TpItem &_item) { _Base::_push_back (_item); }
        void enqueue (const _TpItem &_item) { _Base::_push_back (_item); }
        _TpItem* dequeue () { return _Base::_pop (_Base::_head); }
        _TpItem* first () { return _Base::_get (_Base::_head); }
    };
  }
}

#endif
