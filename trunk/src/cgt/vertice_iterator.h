#ifndef _VERTICE_ITERATOR_H_
#define _VERTICE_ITERATOR_H_


/*
 * _vertice_iterator
 */

template<typename _TpVertice, typename _TpEdge>
class _vertice_iterator
{
  private:
    typedef _vertice_iterator<_TpVertice, _TpEdge> _Self;

  public:
    _vertice_iterator () : _ptr (NULL) { }
    _vertice_iterator (_AdjMatrixItem<_TpVertice, _TpEdge> *_p) : _ptr (_p) { }

  public:
    const _TpVertice& operator*();
    _Self& operator++();
    const bool operator!=(_Self &_other) const;

  private:
    _AdjMatrixItem<_TpVertice, _TpEdge>*  _ptr;
};

template<typename _TpVertice, typename _TpEdge>
const _TpVertice& _vertice_iterator<_TpVertice, _TpEdge>::operator*()
{
  return _ptr->get_vertice ().get_value ();
}

template<typename _TpVertice, typename _TpEdge>
_vertice_iterator<_TpVertice, _TpEdge>& _vertice_iterator<_TpVertice, _TpEdge>::operator++()
{
  assert (_ptr != NULL);
  _ptr = _ptr->get_next ();
  return *this;
}

template<typename _TpVertice, typename _TpEdge>
const bool _vertice_iterator<_TpVertice, _TpEdge>::operator!=(_vertice_iterator<_TpVertice, _TpEdge> &_other) const
{
  return _ptr != _other._ptr;
}

#endif
