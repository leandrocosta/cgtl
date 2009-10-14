#ifndef _GRAPH_EDGE_H_
#define _GRAPH_EDGE_H_


namespace cgt
{
  template<typename _TpVertex, typename _TpEdge>
    class _GraphEdge
    {
      public:
        _GraphEdge (const _TpEdge &_e, _GraphVertex<_TpVertex> &_v1, _GraphVertex<_TpVertex> &_v2) : _value (_e), _vertex1 (_v1), _vertex2 (_v2) { }

      public:
        const _TpEdge&    value () const { return _value; }
        const _GraphVertex<_TpVertex>& v1 () const { return _vertex1; }
        const _GraphVertex<_TpVertex>& v2 () const { return _vertex2; }

        //    const _TpVertex& v1 () const { return _vertex1.value (); }
        //    const _TpVertex& v2 () const { return _vertex2.value (); }

        const string to_string () const
        {
          ostringstream s;
          s << "(" << _value << ", " << _vertex1.value () << ", " << _vertex2.value () << ")";
          return s.str ();
        }

      private:
        _TpEdge               _value;
        _GraphVertex<_TpVertex>& _vertex1;
        _GraphVertex<_TpVertex>& _vertex2;
    };

  template<typename _TpVertex, typename _TpEdge>
    class edge : public _GraphEdge<_TpVertex, _TpEdge>
  {
    public:
      edge (const _TpEdge &_e, _GraphVertex<_TpVertex> &_v1, _GraphVertex<_TpVertex> &_v2) : _GraphEdge<_TpVertex, _TpEdge> (_e, _v1, _v2) { }
  };
}

#endif
