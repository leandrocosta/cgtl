#ifndef _LIST_ITEM_H_
#define _LIST_ITEM_H_

template<typename _TpItem>
class _List;

template<typename _TpItem>
class _ListItemBase;


template<typename _TpItem>
class _ListItem : public _ListItemBase<_TpItem>
{
  private:
    friend class _List<_TpItem>;

  public:
    _ListItem (const _TpItem &_d) : _data (_d) { }

  public:
   _TpItem& _get_data () { return _data; }

  private:
    _TpItem _data;
};

#endif
