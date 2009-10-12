#ifndef _DEPTH_ITERATOR_H_
#define _DEPTH_ITERATOR_H_


namespace cgt
{
  namespace list
  {
    template<typename _TpItem>
      class _ListIterator;
  }


  template<typename _TpVertice, typename _TpEdge>
    class _depth_iterator : public _ListIterator<_GraphNode<_TpVertice, _TpEdge> >
    {
      private:
        typedef _ListIterator<_GraphNode<_TpVertice, _TpEdge> > _Base;
        typedef _depth_iterator<_TpVertice, _TpEdge>            _Self;
        typedef _GraphNode<_TpVertice, _TpEdge>                 _Node;

      private:
        class _DepthReg
        {
          public:
            typedef enum { WHITE, GRAY, BLACK } _color_t;

          public:
            _DepthReg (const _Node *_ptr_n, const _Node *_ptr_pren) : _ptr_node (_ptr_n), _ptr_prenode (_ptr_pren), _color (WHITE) { }
            _DepthReg (const _Node *_ptr_n, const _Node *_ptr_pren, const _color_t &_c) : _ptr_node (_ptr_n), _ptr_prenode (_ptr_pren), _color (_c) { }

          private:
            const _Node*   _ptr_node;
            const _Node*   _ptr_prenode;
            _color_t       _color;
        };

      public:
        _depth_iterator () { }
        _depth_iterator (const _ListIterator<_Node> &_iterator) : _ListIterator<_Node> (_iterator), _ptr_n (_Base::operator->()), _adj_list (_ptr_n->get_adj_list ())
        {
          _reg_list.insert (_DepthReg (_ptr_n, NULL, _DepthReg::GRAY));
          _adj_iterator = _adj_list.begin ();
        }

      public:
        _Self& operator++();

      private:
        _List<_DepthReg>                                      _reg_list;

        const _Node*                                          _ptr_n;
        const _AdjList<_TpVertice, _TpEdge>&                  _adj_list;
        _ListConstIterator<_Adjacency<_TpVertice, _TpEdge> >  _adj_iterator;
    };


    template<typename _TpVertice, typename _TpEdge>
      _depth_iterator<_TpVertice, _TpEdge>& _depth_iterator<_TpVertice, _TpEdge>::operator++()
      {
        assert (_Base::_ptr != NULL);

/*
        if (_adj_iterator == _adj_list.end ())
        {
          _Base::operator++();
        }
        else
        {
          _ptr_n = _adj_iterator->node ();
        }
*/

        return *this;
      }
}

#endif
