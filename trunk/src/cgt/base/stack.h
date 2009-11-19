#ifndef _STACK_H_
#define _STACK_H_

#include "list.h"


namespace cgt
{
  namespace base
  {
    template<typename _TpItem>
      class stack : private cgt::base::list<_TpItem>
    {
      private:
        typedef cgt::base::list<_TpItem>  _Base;

      public:
        using _Base::iterator;
        using _Base::const_iterator;
        using _Base::begin;
        using _Base::end;
        using _Base::clear;
        using _Base::empty;

      public:
        void insert (const _TpItem &_item) { _Base::push_front (_item); }
        void push (const _TpItem &_item) { _Base::push_front (_item); }
        _TpItem* pop () { return _Base::_pop (_Base::_head); }
        _TpItem* top () { return _Base::_get (_Base::_head); }
    };
  }
}

#endif
