#ifndef _GRAPH_NODE_H_
#define _GRAPH_NODE_H_

namespace cgt
{
  template<typename _TpVertice>
    class _Vertice;

  template<typename _TpVertice, typename _TpEdge>
    class _AdjList;


  template<typename _TpVertice, typename _TpEdge>
    class _GraphNode
    {
      private:
        typedef _GraphNode<_TpVertice, _TpEdge> _Self;

      public:
        _GraphNode (const _TpVertice &_v) : _vertice (_v) { };

      public:
        _Vertice<_TpVertice>&           vertice ()  { return _vertice; }
        const _Vertice<_TpVertice>&     vertice () const  { return _vertice; }
        _AdjList<_TpVertice, _TpEdge>&  get_adj_list () { return _adjList; }
        const _AdjList<_TpVertice, _TpEdge>&  get_adj_list () const { return _adjList; }

      public:
        const _Edge<_TpVertice, _TpEdge>* _get_edge (const _Vertice<_TpVertice> &_v) const;

      public:
//        void _insert (const _TpEdge &_e, _Vertice<_TpVertice> &_v);
        void _insert (const _Edge<_TpVertice, _TpEdge>* _ptr_e, _Vertice<_TpVertice> &_v);

      private:
        _Vertice<_TpVertice>          _vertice;
        _AdjList<_TpVertice, _TpEdge> _adjList;
    };

  template<typename _TpVertice, typename _TpEdge>
    const _Edge<_TpVertice, _TpEdge>* _GraphNode<_TpVertice, _TpEdge>::_get_edge (const _Vertice<_TpVertice> &_v) const
    {
      return _adjList._get_edge (_v);
    }

  template<typename _TpVertice, typename _TpEdge>
//    void _GraphNode<_TpVertice, _TpEdge>::_insert (const _TpEdge &_e, _Vertice<_TpVertice> &_v)
    void _GraphNode<_TpVertice, _TpEdge>::_insert (const _Edge<_TpVertice, _TpEdge>* _ptr_e, _Vertice<_TpVertice> &_v)
    {
//      _adjList._insert (_e, _vertice, _v);
      _adjList._insert (_ptr_e, _v);
    }
}

#endif
