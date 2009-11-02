#ifndef _LIST_ITERATOR_BASE_H_
#define _LIST_ITERATOR_BASE_H_

#include "../iterator/iterator_ptr.h"
#include "../iterator/iterator_type.h"
using namespace cgt::base::iterator;


namespace cgt
{
  namespace base
  {
    namespace list
    {
      template<typename _TpItem, template<typename> class _TpIterator>
        class _ListIterator;

      template<typename _TpItem>
        class _ListItemBase;


      template<typename _TpItem, template<typename> class _TpIterator = _TpCommon>
        class _ListIteratorBase : public _IteratorPtr<_ListItemBase<_TpItem>, _TpIterator>
        {
          private:
            typedef _ListIteratorBase<_TpItem, _TpIterator> _Self;
            typedef _ListItemBase<_TpItem>                  _Item;
            typedef _IteratorPtr<_Item, _TpIterator>        _Base;

          private:
            using _Base::_ptr;

          protected:
            _ListIteratorBase () { }
            _ListIteratorBase (_Item *_p) : _Base (_p) { }

          protected:
            void _incr ();

          public:
//            const bool operator==(const _Self& _other) const;
//            const bool operator!=(const _Self& _other) const;

//          private:
//            _Item* _ptr;
        };

      template<typename _TpItem, template<typename> class _TpIterator>
        void _ListIteratorBase<_TpItem, _TpIterator>::_incr ()
        {
          _ptr = _ptr->_next;
        }

      /*
      template<typename _TpItem, template<typename> class _TpIterator>
        const bool _ListIteratorBase<_TpItem, _TpIterator>::operator==(const _Self &_other) const
        {
          return _ptr == _other._ptr;
        }

      template<typename _TpItem, template<typename> class _TpIterator>
        const bool _ListIteratorBase<_TpItem, _TpIterator>::operator!=(const _Self &_other) const
        {
          return ! (*this == _other);
        }
        */
    }
  }
}

#endif
