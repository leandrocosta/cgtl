#ifndef _GRAPH_EDGE_H_
#define _GRAPH_EDGE_H_


namespace cgt
{
  template<typename _TpVertex, typename _TpEdge>
    class _GraphEdge
    {
      private:
        typedef _GraphVertex<_TpVertex> _Vertex;

      public:
        _GraphEdge (const _TpEdge& _e, _Vertex& _v1, _Vertex& _v2) : _value (_e), _vertex1 (_v1), _vertex2 (_v2) { }

      public:
        const _TpEdge& value () const { return _value; }
        _Vertex& v1 () const { return _vertex1; }
        _Vertex& v2 () const { return _vertex2; }

        const string to_string () const
        {
          ostringstream s;
          s << "(" << _value << ", " << _vertex1.value () << ", " << _vertex2.value () << ")";
          return s.str ();
        }

      private:
        _TpEdge   _value;
        _Vertex&  _vertex1;
        _Vertex&  _vertex2;
    };
}

#endif
