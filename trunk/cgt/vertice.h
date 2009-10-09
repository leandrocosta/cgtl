#ifndef _VERTICE_H_
#define _VERTICE_H_


namespace cgt
{
  template<typename _TpVertice>
    class _Vertice
    {
      public:
        _Vertice (const _TpVertice &_v) { _value = _v; }

      public:
        const bool operator==(const _TpVertice &_v) const { return _value == _v; }
        const bool operator!=(const _TpVertice &_v) const { return ! (*this == _v); }

      public:
        const _TpVertice&  value () const { return _value; }

      private:
        _TpVertice _value;
    };
}

#endif
