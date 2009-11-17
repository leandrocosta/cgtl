#ifndef _GRAPH_ADJLIST_H_
#define _GRAPH_ADJLIST_H_

#include "base/list/list.h"
using namespace cgt::base::list;


namespace cgt
{
  template<typename _TpVertex>
    class _GraphVertex;

  template<typename _TpVertex, typename _TpEdge>
    class _GraphAdjacency;


  template<typename _TpVertex, typename _TpEdge>
    class _GraphAdjList : public list<_GraphAdjacency<_TpVertex, _TpEdge> >
  {
    private:
      typedef _GraphAdjList<_TpVertex, _TpEdge>   _Self;
      typedef _GraphNode<_TpVertex, _TpEdge>      _Node;
      typedef _GraphEdge<_TpVertex, _TpEdge>      _Edge;
      typedef _GraphVertex<_TpVertex>             _Vertex;
      typedef _GraphAdjacency<_TpVertex, _TpEdge> _Adjacency;
      typedef list<_Adjacency>                    _Base;
      typedef typename _Base::const_iterator      _Iterator;

    public:
      const _Edge* _get_edge (const _Vertex& _v) const;

    public:
      void _insert (const _Edge& _e, _Node& _n);
  };

  template<typename _TpVertex, typename _TpEdge>
    const _GraphEdge<_TpVertex, _TpEdge>* _GraphAdjList<_TpVertex, _TpEdge>::_get_edge (const _Vertex& _v) const
    {
      const _Edge *_ptr_edge = NULL;

      _Iterator it;
      _Iterator itEnd = _Base::end ();

      for (it = _Base::begin (); it != itEnd; ++it)
      {
        if (it->vertex () == _v)
        {
          _ptr_edge = &(it->edge ());
          break;
        }
      }

      return _ptr_edge;
    }

  template<typename _TpVertex, typename _TpEdge>
    void _GraphAdjList<_TpVertex, _TpEdge>::_insert (const _Edge& _e, _Node& _n)
    {
      _Base::insert (_Adjacency (_e, _n));
    }
}

#endif
