#ifndef _LIST_ITERATOR_BASE_H_
#define _LIST_ITERATOR_BASE_H_

namespace cgt
{
  namespace list
  {
    template<typename _TpItem>
      class _ListIterator;

    template<typename _TpItem>
      class _ListConstIterator;

    template<typename _TpItem>
      class _ListItemBase;


    template<typename _TpItem>
      class _ListIteratorBase
      {
        private:
          friend class _ListIterator<_TpItem>;
          friend class _ListConstIterator<_TpItem>;

        private:
          typedef _ListIteratorBase<_TpItem>  _Self;

        private:
          _ListIteratorBase () : _ptr (NULL) { }
          _ListIteratorBase (_ListItemBase<_TpItem> *_p) : _ptr (_p) { }

        private:
          void _incr ();

        public:
          const bool operator==(_Self &_other) const;
          const bool operator!=(_Self &_other) const;

        private:
          _ListItemBase<_TpItem>* _ptr;
      };

    template<typename _TpItem>
      void _ListIteratorBase<_TpItem>::_incr ()
      {
        _ptr = _ptr->_next;
      }

    template<typename _TpItem>
      const bool _ListIteratorBase<_TpItem>::operator==(_ListIteratorBase<_TpItem> &_other) const
      {
        return _ptr == _other._ptr;
      }

    template<typename _TpItem>
      const bool _ListIteratorBase<_TpItem>::operator!=(_ListIteratorBase<_TpItem> &_other) const
      {
        return ! (*this == _other);
      }
  }
}

#endif
