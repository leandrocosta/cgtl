#ifndef _STORAGE_H_
#define _STORAGE_H_


namespace cgt
{
  namespace alloc
  {
    template<typename _TpItem>
      class _Storage
    template<typename _TpItem>
      class _Storage
      {
        private:
          class _Block
          {
            private:
              unsigned char _data [sizeof (_TpItem)];
              _Block *_ptr_next;
          };

        public:
        private:
          // TODO: we need a list of arrays
          _Block _blocks [1024];
      };
  }
}

#endif
