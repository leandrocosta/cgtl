#ifndef _EDGE_H_
#define _EDGE_H_


template<typename _TpVertice, typename _TpEdge>
class _Edge
{
  public:
    _Edge (const _TpEdge &_e, _Vertice<_TpVertice> &_v1, _Vertice<_TpVertice> &_v2) : _value (_e), _vertice1 (_v1), _vertice2 (_v2) { }

  public:
    const _TpEdge&    value () const { return _value; }
    const _Vertice<_TpVertice>& v1 () const { return _vertice1; }
    const _Vertice<_TpVertice>& v2 () const { return _vertice2; }

//    const _TpVertice& v1 () const { return _vertice1.value (); }
//    const _TpVertice& v2 () const { return _vertice2.value (); }

    const string to_string () const
    {
      ostringstream s;
      s << "(" << _value << ", " << _vertice1.value () << ", " << _vertice2.value () << ")";
      return s.str ();
    }

  private:
    _TpEdge               _value;
    _Vertice<_TpVertice>& _vertice1;
    _Vertice<_TpVertice>& _vertice2;
};

template<typename _TpVertice, typename _TpEdge>
class edge : public _Edge<_TpVertice, _TpEdge>
{
  public:
    edge (const _TpEdge &_e, _Vertice<_TpVertice> &_v1, _Vertice<_TpVertice> &_v2) : _Edge<_TpVertice, _TpEdge> (_e, _v1, _v2) { }
};

#endif
