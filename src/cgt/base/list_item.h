/*
 * CGTL - A graph template library for C++
 * ---------------------------------------
 * Copyright (C) 2009 Leandro Costa
 *
 * This file is part of CGTL.
 *
 * CGTL is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as
 * published by the Free Software Foundation, either version 3 of
 * the License, or (at your option) any later version.
 *
 * CGTL is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with CGTL. If not, see <http://www.gnu.org/licenses/>.
 */

/*!
 * \file cgt/base/list_item.h
 * \brief Contains definition of the structure used as a list's item.
 * \author Leandro Costa
 * \date 2009
 *
 * $LastChangedDate$
 * $LastChangedBy$
 * $Revision$
 */

#ifndef __CGTL__CGT_BASE_LIST_ITEM_H_
#define __CGTL__CGT_BASE_LIST_ITEM_H_

#include "cgt/base/list_item_base.h"
#include "cgt/base/list_iterator.h"


namespace cgt
{
  namespace base
  {
    template<typename _TpItem>
      class _ListItem : public _ListItemBase<_TpItem>
    {
      private:
        typedef _ListItemBase<_TpItem> _Base;

      public:
        _ListItem (const _TpItem& _d) : _data (_d) { }

      public:
        _TpItem _data;
    };
  }
}

#endif // __CGTL__CGT_BASE_LIST_ITEM_H_
