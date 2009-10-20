#ifndef _ADJ_LIST_H_
#define _ADJ_LIST_H_

#include "list/list.h"
using namespace cgt::list;


namespace cgt
{
  template<typename _TpVertex>
    class _GraphVertex;

  template<typename _TpVertex, typename _TpEdge>
    class _GraphAdjacency;


  template<typename _TpVertex, typename _TpEdge>
    class _AdjList : public _List<_GraphAdjacency<_TpVertex, _TpEdge> >
  {
    private:
      typedef _List<_GraphAdjacency<_TpVertex, _TpEdge> > _Base;

    public:
      const _GraphEdge<_TpVertex, _TpEdge>* _get_edge (const _GraphVertex<_TpVertex> &_v) const;

    public:
      void _insert (const _GraphEdge<_TpVertex, _TpEdge>& _e, _GraphVertex<_TpVertex> &_v, _GraphNode<_TpVertex, _TpEdge>* const _ptr_n);
  };

  template<typename _TpVertex, typename _TpEdge>
    const _GraphEdge<_TpVertex, _TpEdge>* _AdjList<_TpVertex, _TpEdge>::_get_edge (const _GraphVertex<_TpVertex> &_v) const
    {
      const _GraphEdge<_TpVertex, _TpEdge> *_ptr_edge = NULL;

      typename _Base::const_iterator it;
      typename _Base::const_iterator itEnd = _Base::end ();

      for (it = _Base::begin (); it != itEnd; ++it)
      {
        if (it->get_vertex () == _v)
        {
          _ptr_edge = &(it->get_edge ());
          break;
        }
      }

      return _ptr_edge;
    }

  template<typename _TpVertex, typename _TpEdge>
    void _AdjList<_TpVertex, _TpEdge>::_insert (const _GraphEdge<_TpVertex, _TpEdge>& _e, _GraphVertex<_TpVertex> &_v, _GraphNode<_TpVertex, _TpEdge>* const _ptr_n)
    {
      _List<_GraphAdjacency<_TpVertex, _TpEdge> >::insert (_GraphAdjacency<_TpVertex, _TpEdge> (_e, _v, _ptr_n));
    }
}

#endif
