#ifndef _LIST_ITEM_BASE_H_
#define _LIST_ITEM_BASE_H_

#include "iterator/iterator_type.h"


namespace cgt
{
  namespace base
  {
    template<typename _TpItem>
      class _ListItem;

    template<typename _TpItem>
      class _ListItemBase
      {
        private:
          friend class _ListItem<_TpItem>;

        private:
          typedef _ListItemBase<_TpItem> _Self;

        private:
          _ListItemBase () : _next (NULL), _prev (NULL) { }

        public:
          _Self* _next;
          _Self* _prev;
      };
  }
}

#endif
