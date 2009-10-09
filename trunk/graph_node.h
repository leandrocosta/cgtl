#ifndef _GRAPH_NODE_H_
#define _GRAPH_NODE_H_

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
    _AdjList<_TpVertice, _TpEdge>&  get_adj_list () { return _adjList; }

    void insert (const _TpEdge &_e, _Vertice<_TpVertice> &_v);

  private:
    _Vertice<_TpVertice>          _vertice;
    _AdjList<_TpVertice, _TpEdge> _adjList;
};

template<typename _TpVertice, typename _TpEdge>
void _GraphNode<_TpVertice, _TpEdge>::insert (const _TpEdge &_e, _Vertice<_TpVertice> &_v)
{
  _adjList.insert (_e, _vertice, _v);
}

#endif
