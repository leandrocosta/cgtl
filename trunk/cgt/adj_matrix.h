#ifndef _ADJ_MATRIX_H_
#define _ADJ_MATRIX_H_


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

  template<typename _TpVertice, typename _TpEdge>
    class graph;


  template<typename _TpVertice, typename _TpEdge>
    class _AdjMatrix : private _List<_GraphNode<_TpVertice, _TpEdge> >
  {
    private:
      friend class _edge_iterator<_TpVertice, _TpEdge>;
      friend class graph<_TpVertice, _TpEdge>;

    private:
      typedef _List<_GraphNode<_TpVertice, _TpEdge> > _Base;
      typedef _GraphNode<_TpVertice, _TpEdge>         _Node;

    private:
      _Node* _get_node (const _TpVertice &_vertice);
      void _insert_node (const _TpVertice &_vertice);

    private:
      void _insert_vertice (const _TpVertice &_vertice);
      void _insert_edge (const _TpEdge &_e, const _TpVertice &_v1, const _TpVertice &_v2);
  };


  template<typename _TpVertice, typename _TpEdge>
    _GraphNode<_TpVertice, _TpEdge>* _AdjMatrix<_TpVertice, _TpEdge>::_get_node (const _TpVertice &_vertice)
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

  template<typename _TpVertice, typename _TpEdge>
    void _AdjMatrix<_TpVertice, _TpEdge>::_insert_node (const _TpVertice &_vertice)
    {
      insert (_GraphNode<_TpVertice, _TpEdge> (_vertice));
    }

  template<typename _TpVertice, typename _TpEdge>
    void _AdjMatrix<_TpVertice, _TpEdge>::_insert_vertice (const _TpVertice &_vertice)
    {
      _Node *_ptr = _get_node (_vertice);

      if (! _ptr)
        _insert_node (_vertice);
    }

  template<typename _TpVertice, typename _TpEdge>
    void _AdjMatrix<_TpVertice, _TpEdge>::_insert_edge (const _TpEdge &_e, const _TpVertice &_v1, const _TpVertice &_v2)
    {
      _Node *_ptr_n1 = _get_node (_v1);

      if (_ptr_n1)
      {
        _Node *_ptr_n2 = _get_node (_v2);

        if (_ptr_n2)
        {
          _Vertice<_TpVertice>& _vertice2 = _ptr_n2->vertice ();

          _ptr_n1->insert (_e, _vertice2);
        }
      }
    }
}

#endif
