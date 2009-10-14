#ifndef _GRAPH_VERTEX_H_
#define _GRAPH_VERTEX_H_


namespace cgt
{
  template<typename _TpVertex>
    class _GraphVertex
    {
      public:
        _GraphVertex (const _TpVertex &_v) { _value = _v; }

      public:
        const bool operator==(const _GraphVertex<_TpVertex> &_v) const { return _value == _v.value (); }
        const bool operator!=(const _GraphVertex<_TpVertex> &_v) const { return ! (*this == _v.value ()); }

        const bool operator==(const _TpVertex &_v) const { return _value == _v; }
        const bool operator!=(const _TpVertex &_v) const { return ! (*this == _v); }

      public:
        const _TpVertex&  value () const { return _value; }

      private:
        _TpVertex _value;
    };
}

#endif
