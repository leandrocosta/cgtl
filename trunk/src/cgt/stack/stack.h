#ifndef _STACK_H_
#define _STACK_H_

#include "../list/list.h"
using namespace cgt::list;


namespace cgt
{
  namespace stack
  {
    template<typename _TpItem>
      class _Stack : private _List<_TpItem>
      {
        private:
          typedef _Stack<_TpItem>  _Self;
          typedef _List<_TpItem>   _Base;

        public:
          using _Base::iterator;
          using _Base::const_iterator;
          using _Base::begin;
          using _Base::end;
          using _Base::size;
          using _Base::empty;

        public:
          void push (const _TpItem &_item);
          _TpItem* pop ();
          _TpItem* top ();

          void insert (const _TpItem &_item);
      };

    template<typename _TpItem>
      void _Stack<_TpItem>::push (const _TpItem &_item)
      {
        _Base::push_front (_item);
      }

    template<typename _TpItem>
      _TpItem* _Stack<_TpItem>::pop ()
      {
        return _Base::pop_front ();
      }

    template<typename _TpItem>
      _TpItem* _Stack<_TpItem>::top ()
      {
        return _Base::front ();
      }

    template<typename _TpItem>
      void _Stack<_TpItem>::insert (const _TpItem &_item)
      {
        push (_item);
      }

    template<typename _TpItem>
      class stack : public _Stack<_TpItem>
      {
      };
  }
}

#endif
