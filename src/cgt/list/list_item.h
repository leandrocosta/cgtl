#ifndef _LIST_ITEM_H_
#define _LIST_ITEM_H_

#include "list_item_base.h"
#include "iterator_type.h"


namespace cgt
{
  namespace list
  {
    template<typename _TpItem>
      class _List;

    template<typename _TpItem, typename _TpIterator>
      class _ListIterator;


    template<typename _TpItem>
      class _ListItem : public _ListItemBase<_TpItem>
    {
      private:
        friend class _List<_TpItem>;
        friend class _ListIterator<_TpItem, _TpCommon<_TpItem> >;
        friend class _ListIterator<_TpItem, _TpConst<_TpItem> >;

      private:
        _ListItem (const _TpItem &_d) : _data (_d) { }

      private:
        _TpItem _data;
    };
  }
}

#endif
