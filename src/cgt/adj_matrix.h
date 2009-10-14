#ifndef _ADJ_MATRIX_H_
#define _ADJ_MATRIX_H_

#include "graph_type.h"

using namespace cgt::list;

namespace cgt
{
  namespace list
  {
    template<typename _TpItem>
      class _List;

    template<typename _TpItem>
      class _ListItem;

    template<typename _TpItem>
      class _ListIterator;
  }

  template<typename _TpVertex>
    class _GraphVertex;

  template<typename _TpVertex, typename _TpEdge>
    class _GraphNode;

  template<typename _TpVertex, typename _TpEdge, typename _TpGraphType>
    class graph;


  template<typename _TpVertex, typename _TpEdge, typename _TpGraphType>
    class _AdjMatrix : private _List<_GraphNode<_TpVertex, _TpEdge> >
  {
    private:
      friend class graph<_TpVertex, _TpEdge, _TpGraphType>;

    private:
      typedef _List<_GraphNode<_TpVertex, _TpEdge> > _Base;
      typedef _GraphNode<_TpVertex, _TpEdge>         _Node;

    private:
      _Node* _get_node (const _TpVertex &_vertex);

    private:
      void _insert_node (const _TpVertex &_vertex);
      void _insert_vertex (const _TpVertex &_vertex);
      void _insert_edge (const _TpEdge &_e, const _TpVertex &_v1, const _TpVertex &_v2);

    private:
      const bool _is_directed () const;
      const bool _is_undirected () const;

    private:
      _TpGraphType                        _type;
      _List<_GraphEdge<_TpVertex, _TpEdge> >  _edge_list;
  };


  template<typename _TpVertex, typename _TpEdge, typename _TpGraphType>
    _GraphNode<_TpVertex, _TpEdge>* _AdjMatrix<_TpVertex, _TpEdge, _TpGraphType>::_get_node (const _TpVertex &_vertex)
    {
      _Node *_ptr_node = NULL;

      typename _Base::iterator it;
      typename _Base::iterator itEnd = _Base::end ();

      for (it = _Base::begin (); it != itEnd; ++it)
      {
        if (it->vertex () == _vertex)
        {
          _ptr_node = &(*it);
          break;
        }
      }

      return _ptr_node;
    }

  template<typename _TpVertex, typename _TpEdge, typename _TpGraphType>
    void _AdjMatrix<_TpVertex, _TpEdge, _TpGraphType>::_insert_node (const _TpVertex &_vertex)
    {
      insert (_GraphNode<_TpVertex, _TpEdge> (_vertex));
    }

  template<typename _TpVertex, typename _TpEdge, typename _TpGraphType>
    void _AdjMatrix<_TpVertex, _TpEdge, _TpGraphType>::_insert_vertex (const _TpVertex &_vertex)
    {
      _Node *_ptr = _get_node (_vertex);

      if (! _ptr)
        _insert_node (_vertex);
    }

  template<typename _TpVertex, typename _TpEdge, typename _TpGraphType>
    void _AdjMatrix<_TpVertex, _TpEdge, _TpGraphType>::_insert_edge (const _TpEdge &_e, const _TpVertex &_v1, const _TpVertex &_v2)
    {
      _Node *_ptr_n1 = _get_node (_v1);

      if (_ptr_n1)
      {
        _Node *_ptr_n2 = _get_node (_v2);

        if (_ptr_n2)
        {
          _GraphVertex<_TpVertex>& _vertex2 = _ptr_n2->vertex ();

          if (! _ptr_n1->_get_edge (_vertex2))
          {
            _GraphVertex<_TpVertex>& _vertex1 = _ptr_n1->vertex ();

            _GraphEdge<_TpVertex, _TpEdge> &_edge = _edge_list.insert (_GraphEdge<_TpVertex, _TpEdge> (_e, _vertex1, _vertex2));

            _ptr_n1->_insert (_edge, _vertex2, _ptr_n2);

            if (! _type._directed && ! _ptr_n2->_get_edge (_vertex1))
              _ptr_n2->_insert (_edge, _vertex1, _ptr_n1);
          }
        }
      }
    }

  template<typename _TpVertex, typename _TpEdge, typename _TpGraphType>
    const bool _AdjMatrix<_TpVertex, _TpEdge, _TpGraphType>::_is_directed () const
    {
      return _type._directed;
    }

  template<typename _TpVertex, typename _TpEdge, typename _TpGraphType>
    const bool _AdjMatrix<_TpVertex, _TpEdge, _TpGraphType>::_is_undirected () const
    {
      return (! _is_directed ());
    }
}

#endif
