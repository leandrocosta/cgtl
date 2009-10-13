#ifndef _VERTEX_H_
#define _VERTEX_H_


namespace cgt
{
  template<typename _TpVertex>
    class _Vertex
    {
      public:
        _Vertex (const _TpVertex &_v) { _value = _v; }

      public:
        const bool operator==(const _Vertex<_TpVertex> &_v) const { return _value == _v.value (); }
        const bool operator!=(const _Vertex<_TpVertex> &_v) const { return ! (*this == _v.value ()); }

        const bool operator==(const _TpVertex &_v) const { return _value == _v; }
        const bool operator!=(const _TpVertex &_v) const { return ! (*this == _v); }

      public:
        const _TpVertex&  value () const { return _value; }

      private:
        _TpVertex _value;
    };
}

#endif
