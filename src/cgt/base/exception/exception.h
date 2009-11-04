#ifndef _EXCEPTION_H_
#define _EXCEPTION_H_

#include <string.h>


namespace cgt
{
  namespace base
  {
    namespace exception
    {
      class exception
      {
        public:
          exception (const char* _m) { _message = strdup (_m); }

        public:
          const char* message () { return _message; }

        private:
          char *_message;
      };
    }
  }
}

#endif
