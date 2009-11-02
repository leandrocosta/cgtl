#ifndef _LIST_ITEM_H_
#define _LIST_ITEM_H_

#include "list_item_base.h"
#include "list_iterator.h"


namespace cgt
{
  namespace base
  {
    namespace list
    {
      template<typename _TpItem>
        class _ListItem : public _ListItemBase<_TpItem>
      {
        private:
          friend class _ListIterator<_TpItem, cgt::base::iterator::_TpCommon>;
          friend class _ListIterator<_TpItem, cgt::base::iterator::_TpConst>;

        private:
          typedef _ListItemBase<_TpItem> _Base;

        public:
          _ListItem (const _TpItem& _d) : _data (_d) { }

        public:
          _TpItem _data;
      };
    }
  }
}

#endif
