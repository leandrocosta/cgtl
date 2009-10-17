#ifndef _DEPTH_INFO_ITERATOR_H_
#define _DEPTH_INFO_ITERATOR_H_

#include "depth_iterator.h"


namespace cgt
{
  template<typename _TpVertex, typename _TpEdge, template<typename> class _TpIterator = _TpCommon>
    class _DepthInfoIterator : public _List<_DepthIterator<_TpVertex, _TpEdge, _TpIterator> >
    {
      private:
        typedef _DepthIterator<_TpVertex, _TpEdge, _TpIterator> _DIterator;

      public:
        _DepthInfoIterator (const _DIterator &_it) : _DepthInfoList (_it._DepthInfoList) { }

      private:
        const _List<typename _DIterator::_DepthInfo>& _DepthInfoList;
    };
}

#endif
