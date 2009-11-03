#ifndef _ITERATOR_BASE_H_
#define _ITERATOR_BASE_H_


namespace cgt
{
  namespace base
  {
    namespace iterator
    {
      template<typename _TpItem, template<typename> class _TpIterator>
        class _IteratorBase
        {
          private:
            typedef _IteratorBase<_TpItem, _TpIterator>  _Self;

          public:
            virtual ~_IteratorBase () { }

          protected:
            virtual void _incr () = 0;

          protected:
            virtual const bool operator==(const _Self&) const { return false; }
            virtual const bool operator!=(const _Self&) const { return false; }
        };
    }
  }
}

#endif
