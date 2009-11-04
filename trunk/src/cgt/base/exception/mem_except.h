#ifndef _MEM_EXCEPT_H_
#define _MEM_EXCEPT_H_

#include "exception.h"

namespace cgt
{
  namespace base
  {
    namespace exception
    {
      class mem_except : public exception
      {
        public:
          mem_except (const char* _m) : exception (_m) { }
      };
    }
  }
}

#endif
