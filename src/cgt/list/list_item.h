#ifndef _LIST_ITEM_H_
#define _LIST_ITEM_H_

namespace cgt
{
  namespace list
  {
    template<typename _TpItem>
      class _ListItemBase;

    template<typename _TpItem>
      class _List;

    template<typename _TpItem>
      class _ListIterator;

    template<typename _TpItem>
      class _ListConstIterator;


    template<typename _TpItem>
      class _ListItem : public _ListItemBase<_TpItem>
    {
      private:
        friend class _List<_TpItem>;
        friend class _ListIterator<_TpItem>;
        friend class _ListConstIterator<_TpItem>;

      private:
        _ListItem (const _TpItem &_d) : _data (_d) { }

      private:
        _TpItem _data;
    };
  }
}

#endif
