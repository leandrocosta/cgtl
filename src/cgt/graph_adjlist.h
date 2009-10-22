#ifndef _GRAPH_ADJLIST_H_
#define _GRAPH_ADJLIST_H_

#include "list/list.h"
using namespace cgt::list;


namespace cgt
{
  template<typename _TpVertex>
    class _GraphVertex;

  template<typename _TpVertex, typename _TpEdge>
    class _GraphAdjacency;


  template<typename _TpVertex, typename _TpEdge>
    class _GraphAdjList : public _List<_GraphAdjacency<_TpVertex, _TpEdge> >
  {
    private:
      typedef _GraphAdjList<_TpVertex, _TpEdge>   _Self;
      typedef _GraphNode<_TpVertex, _TpEdge>      _Node;
      typedef _GraphEdge<_TpVertex, _TpEdge>      _Edge;
      typedef _GraphVertex<_TpVertex>             _Vertex;
      typedef _GraphAdjacency<_TpVertex, _TpEdge> _Adjacency;
      typedef _List<_Adjacency>                   _Base;
      typedef typename _Base::const_iterator      _Iterator;

    public:
      const _Edge* _get_edge (const _Vertex& _v) const;

    public:
      void _insert (const _Edge& _e, _Vertex& _v, _Node* const _ptr_n);
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
    void _GraphAdjList<_TpVertex, _TpEdge>::_insert (const _Edge& _e, _Vertex& _v, _Node* const _ptr_n)
    {
      _Base::insert (_Adjacency (_e, _v, _ptr_n));
    }
}

#endif
