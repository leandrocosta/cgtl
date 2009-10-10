#ifndef _ADJ_MATRIX_H_
#define _ADJ_MATRIX_H_

#include "graph_type.h"


namespace cgt
{
  using namespace list;

  namespace list
  {
    template<typename _TpItem>
      class _List;

    template<typename _TpItem>
      class _ListItem;

    template<typename _TpItem>
      class _ListIterator;
  }

  template<typename _TpVertice>
    class _Vertice;

  template<typename _TpVertice, typename _TpEdge>
    class _GraphNode;

  template<typename _TpVertice, typename _TpEdge>
    class _edge_iterator;

  template<typename _TpVertice, typename _TpEdge, typename _TpGraphType>
    class graph;


  template<typename _TpVertice, typename _TpEdge, typename _TpGraphType>
    class _AdjMatrix : private _List<_GraphNode<_TpVertice, _TpEdge> >
  {
    private:
      friend class _edge_iterator<_TpVertice, _TpEdge>;
      friend class graph<_TpVertice, _TpEdge, _TpGraphType>;

    private:
      typedef _List<_GraphNode<_TpVertice, _TpEdge> > _Base;
      typedef _GraphNode<_TpVertice, _TpEdge>         _Node;

    private:
      _Node* _get_node (const _TpVertice &_vertice);

    private:
      void _insert_node (const _TpVertice &_vertice);
      void _insert_vertice (const _TpVertice &_vertice);
      void _insert_edge (const _TpEdge &_e, const _TpVertice &_v1, const _TpVertice &_v2);

    private:
      const bool _is_directed () const;
      const bool _is_undirected () const;

    private:
      _TpGraphType _type;
  };


  template<typename _TpVertice, typename _TpEdge, typename _TpGraphType>
    _GraphNode<_TpVertice, _TpEdge>* _AdjMatrix<_TpVertice, _TpEdge, _TpGraphType>::_get_node (const _TpVertice &_vertice)
    {
      _Node *_ptr_node = NULL;

      typename _Base::iterator it;
      typename _Base::iterator itEnd = _Base::end ();

      for (it = _Base::begin (); it != itEnd; ++it)
      {
        if (it->vertice () == _vertice)
        {
          _ptr_node = &(*it);
          break;
        }
      }

      return _ptr_node;
    }

  template<typename _TpVertice, typename _TpEdge, typename _TpGraphType>
    void _AdjMatrix<_TpVertice, _TpEdge, _TpGraphType>::_insert_node (const _TpVertice &_vertice)
    {
      insert (_GraphNode<_TpVertice, _TpEdge> (_vertice));
    }

  template<typename _TpVertice, typename _TpEdge, typename _TpGraphType>
    void _AdjMatrix<_TpVertice, _TpEdge, _TpGraphType>::_insert_vertice (const _TpVertice &_vertice)
    {
      _Node *_ptr = _get_node (_vertice);

      if (! _ptr)
        _insert_node (_vertice);
    }

  template<typename _TpVertice, typename _TpEdge, typename _TpGraphType>
    void _AdjMatrix<_TpVertice, _TpEdge, _TpGraphType>::_insert_edge (const _TpEdge &_e, const _TpVertice &_v1, const _TpVertice &_v2)
    {
      _Node *_ptr_n1 = _get_node (_v1);

      if (_ptr_n1)
      {
        _Node *_ptr_n2 = _get_node (_v2);

        if (_ptr_n2)
        {
          _Vertice<_TpVertice>& _vertice2 = _ptr_n2->vertice ();

//          if (! _ptr_n1->_get_edge (_vertice2))
//          {
            _Vertice<_TpVertice>& _vertice1 = _ptr_n1->vertice ();

            _Edge<_TpVertice, _TpEdge> *_ptr_e = new _Edge<_TpVertice, _TpEdge> (_e, _vertice1, _vertice2);

            _ptr_n1->_insert (_ptr_e, _vertice2);

            if (! _type._directed)
              _ptr_n2->_insert (_ptr_e, _vertice1);
//          }
        }
      }
    }

  template<typename _TpVertice, typename _TpEdge, typename _TpGraphType>
    const bool _AdjMatrix<_TpVertice, _TpEdge, _TpGraphType>::_is_directed () const
    {
      return _type._directed;
    }

  template<typename _TpVertice, typename _TpEdge, typename _TpGraphType>
    const bool _AdjMatrix<_TpVertice, _TpEdge, _TpGraphType>::_is_undirected () const
    {
      return (! _is_directed ());
    }
}

#endif
