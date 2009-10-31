#ifndef _QUEUE_H_
#define _QUEUE_H_

#include "../list/list.h"
using namespace cgt::base::list;

namespace cgt
{
  namespace base
  {
    namespace queue
    {
      template<typename _TpItem>
        class _Queue : private _List<_TpItem>
      {
        private:
          typedef _Queue<_TpItem>  _Self;
          typedef _List<_TpItem>   _Base;

        public:
          using _Base::iterator;
          using _Base::const_iterator;
          using _Base::begin;
          using _Base::end;
          using _Base::size;
          using _Base::empty;

        public:
          void enqueue (const _TpItem &_item);
          _TpItem* dequeue ();
          _TpItem* first ();

          void insert (const _TpItem &_item);
      };

      template<typename _TpItem>
        void _Queue<_TpItem>::enqueue (const _TpItem &_item)
        {
          _Base::push_back (_item);
        }

      template<typename _TpItem>
        _TpItem* _Queue<_TpItem>::dequeue ()
        {
          return _Base::pop_front ();
        }

      template<typename _TpItem>
        _TpItem* _Queue<_TpItem>::first ()
        {
          return _Base::front ();
        }

      template<typename _TpItem>
        void _Queue<_TpItem>::insert (const _TpItem &_item)
        {
          enqueue (_item);
        }

      template<typename _TpItem>
        class queue : public _Queue<_TpItem>
      {
      };
    }
  }
}



#endif
