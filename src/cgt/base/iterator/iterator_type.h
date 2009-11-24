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
 * \file cgt/base/iterator/iterator_type.h
 * \brief Contains definition of structures used to identify common and const iterators.
 * \author Leandro Costa
 * \date 2009
 *
 * $LastChangedDate$
 * $LastChangedBy$
 * $Revision$
 */

#ifndef __CGTL__CGT_BASE_ITERATOR_ITERATOR_TYPE_H_
#define __CGTL__CGT_BASE_ITERATOR_ITERATOR_TYPE_H_


namespace cgt
{
  namespace base
  {
    /*!
     * \namespace cgt::base::iterator
     * \brief Where are defined the base templates for iterators.
     * \author Leandro Costa
     * \date 2009
     */

    namespace iterator
    {
      template<typename _TpItem>
        struct _TpCommon
        {
          typedef _TpItem* pointer;
          typedef _TpItem& reference;
        };

      template<typename _TpItem>
        struct _TpConst
        {
          typedef const _TpItem* pointer;
          typedef const _TpItem& reference;
        };
    }
  }
}

#endif // __CGTL__CGT_BASE_ITERATOR_ITERATOR_TYPE_H_
