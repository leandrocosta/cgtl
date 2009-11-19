#ifndef _KRUSKAL_ITERATOR_H_
#define _KRUSKAL_ITERATOR_H_

#include "kruskal_edge_heap.h"
#include "../../base/iterator/iterator_ptr.h"
#include "../../base/hash.h"


namespace cgt
{
  namespace base
  {
    template<typename _TpVertex, typename _TpEdge>
      class _HeapInvariant<_GraphEdge<_TpVertex, _TpEdge>*>
      {
        private:
          typedef _GraphEdge<_TpVertex, _TpEdge> _Edge;
          typedef _Edge*                         _EdgePtr;

        public:
          static const bool _less_than (const _EdgePtr& _child, const _EdgePtr& _parent)
          {
            return (_child->value () < _parent->value ());
          }
      };
  }

  template<typename _TpVertex, typename _TpEdge, template<typename> class _TpIterator>
    class _VertexIterator;

  namespace minspantree
  {
    namespace kruskal
    {
      template<typename _TpVertex, typename _TpEdge, template<typename> class _TpIterator = cgt::base::iterator::_TpCommon>
        class _KruskalIterator : public cgt::base::iterator::_IteratorPtr<_GraphEdge<_TpVertex, _TpEdge>, _TpIterator>
        {
          private:
            class _SetInfo;

          private:
            typedef _KruskalIterator<_TpVertex, _TpEdge, _TpIterator>  _Self;
            typedef _KruskalIterator<_TpVertex, _TpEdge, cgt::base::iterator::_TpCommon>    _SelfCommon;

          private:
            typedef _GraphNode<_TpVertex, _TpEdge>      _Node;
            typedef _GraphEdge<_TpVertex, _TpEdge>      _Edge;
            typedef _GraphVertex<_TpVertex>             _Vertex;
            typedef cgt::base::iterator::_IteratorPtr<_Edge, _TpIterator>    _Base;

            typedef _VertexIterator<_TpVertex, _TpEdge>       _viterator;
            typedef typename cgt::base::list<_Edge>::iterator _eiterator;

            typedef cgt::base::list<_Node>        _NodeList;
            typedef typename _NodeList::iterator  _NodeIterator;

          private:
//            typedef _KruskalEdgeHeap<_Edge*>            _EdgeHeap;
            typedef cgt::base::heap<_Edge*>             _EdgeHeap;
            typedef cgt::base::vector<_SetInfo>         _SetVector;
//            typedef cgt::base::hash<_Vertex*, _SetInfo> _VertexSetHash;
            typedef cgt::base::hash<_Vertex*, size_t> _VertexSetHash;

          private:
            using _Base::_ptr;

          private:
            struct _SetInfo
            {
              /*
              _SetInfo ()
              {
                _set = this;
                _rank = 0;
              }
              */

              _SetInfo (const size_t& _pos) { _set = _pos; _rank = 0; }

              /*
              _SetInfo (const _SetInfo& _s) { *this = _s; }

              _SetInfo& operator=(const _SetInfo& _s)
              {
                if (_s._set == &_s)
                  _set = this;
                else
                {
                  cout << "ops.." << endl;
                  _set = _s._set;
                } 

                _rank = _s._rank;

                return *this;
              }
              */

              const _SetInfo* operator()() { return this; }

              /*
              static void _union (_SetInfo* _s1, _SetInfo* _s2)
              {
                if (_s1 && _s2)
                {
                  cout << "  union (" << _s1 << ", " << _s2 << ")" << endl;

                  while (_s1->_set != _s1)
                    _s1 = _s1->_set;

                  while (_s2->_set != _s2)
                    _s2 = _s2->_set;

                  if (_s1 != _s2)
                  {
                    if (_s1->_rank > _s2->_rank)
                    {
                      _s2->_set = _s1;
                      cout << "    _s2 [" << _s2 << "]._set = _s1 [" << _s1 << "]" << endl;
                    }
                    else
                    {
                      _s1->_set = _s2;
                      cout << "    _s1 [" << _s1 << "]._set = _s2 [" << _s2 << "]" << endl;

                      if (_s1->_rank == _s2->_rank)
                        _s2->_rank++;
                    }
                  }
                }
              }
              */

              /*
              static const bool _same_set (_SetInfo* _s1, _SetInfo* _s2)
              {
                bool _ret = false;

                if (_s1 && _s2)
                {
                  while (_s1->_set != _s1)
                    _s1 = _s1->_set;

                  while (_s2->_set != _s2)
                    _s2 = _s2->_set;

                  _ret = (_s1 == _s2);
                }

                return _ret;
              }
              */

//              _SetInfo* _set;
              size_t  _set;
              size_t  _rank;
            };

          public:
            _KruskalIterator () { }
            _KruskalIterator (_Node* const _ptr_n) { }
            _KruskalIterator (_Node* const _ptr_n, _viterator _vit, _viterator _vitEnd, _eiterator _eit, _eiterator _eitEnd)
            {
              if (_ptr_n)
                _init (*_ptr_n, _vit, _vitEnd, _eit, _eitEnd);
            }
            _KruskalIterator (const _NodeIterator& _it, _viterator _vit, _viterator _vitEnd, _eiterator _eit, _eiterator _eitEnd) { _init (*_it, _vit, _vitEnd, _eit, _eitEnd); }
            _KruskalIterator (const _SelfCommon& _it) { }
            virtual ~_KruskalIterator () { }

          private:
            void _init (_Node& _n, _viterator _vit, _viterator _vitEnd, _eiterator _eit, _eiterator _eitEnd);
            void _incr ();
            const bool _set_same (size_t _pos1, size_t _pos2) const
            {
              bool _ret = false;

              if (_pos1 < _setVector.size () && _pos2 < _setVector.size ())
              {
                while (_setVector [_pos1]._set != _pos1)
                  _pos1 = _setVector [_pos1]._set;

                while (_setVector [_pos2]._set != _pos2)
                  _pos2 = _setVector [_pos2]._set;

                _ret = (_pos1 == _pos2);
              }

              return _ret;
            }

            void _set_union (size_t _pos1, size_t _pos2)
            {
              if (_pos1 < _setVector.size () && _pos2 < _setVector.size ())
              {
//                cout << "  union (" << _pos1 << ", " << _pos2 << ")" << endl;

                while (_setVector [_pos1]._set != _pos1)
                  _pos1 = _setVector [_pos1]._set;

                while (_setVector [_pos2]._set != _pos2)
                  _pos2 = _setVector [_pos2]._set;

                if (_pos1 != _pos2)
                {
                  if (_setVector [_pos1]._rank > _setVector [_pos2]._rank)
                  {
                    _setVector [_pos2]._set = _pos1;
//                    cout << "    _pos2 [" << _pos2 << "]._set = _pos1 [" << _pos1 << "]" << endl;
                  }
                  else
                  {
                    _setVector [_pos1]._set = _pos2;
//                    cout << "    _pos1 [" << _pos1 << "]._set = _pos2 [" << _pos2 << "]" << endl;

                    if (_setVector [_pos1]._rank == _setVector [_pos2]._rank)
                      _setVector [_pos2]._rank++;
                  }
                }
              }
            }

          public:
            _Edge& operator*() const { return *_ptr; }
            _Edge* operator->() const { return _ptr; }
            _Self& operator++();
            const _Self operator++(int);

          private:
            _EdgeHeap       _edgeHeap;
            _SetVector      _setVector;
            _VertexSetHash  _vertexSetHash;
        };


      template<typename _TpVertex, typename _TpEdge, template<typename> class _TpIterator>
        void _KruskalIterator<_TpVertex, _TpEdge, _TpIterator>::_init (_Node& _n, _viterator _vit, _viterator _vitEnd, _eiterator _eit, _eiterator _eitEnd)
        {
          while (_vit != _vitEnd)
          {
            _vertexSetHash.insert (&(*_vit), _setVector.size ());
            _setVector.push_back (_SetInfo (_setVector.size ()));
//            cout << "hash [" << &(*_vit) << "] = " << _vertexSetHash [&(*_vit)] << endl;
            ++_vit;
          }

          while (_eit != _eitEnd)
          {
            _edgeHeap.push (&(*_eit));
            ++_eit;
          }

          _Edge** _p = _edgeHeap.pop ();
          _ptr = *_p;
          delete _p;

          /*
          typename _VertexSetHash::iterator it = _vertexSetHash.begin ();
          typename _VertexSetHash::iterator itEnd = _vertexSetHash.end ();
          if (it != itEnd)
          {
            cout << "_vertexSetHash: (" << it->first << ", " << it->second << ")";
            while (++it != itEnd)
              cout << ", (" << it->first << ", " << it->second << ")";
            cout << endl;
          }
          */

//          cout << "  joining " << _ptr->v1 ().value () << " [" << &(_ptr->v1 ()) << "] and " << _ptr->v2 ().value () << " [" << &(_ptr->v2 ()) << "]" << endl;
          _set_union (*(_vertexSetHash [&(_ptr->v1 ())]), *(_vertexSetHash [&(_ptr->v2 ())]));
        }

      template<typename _TpVertex, typename _TpEdge, template<typename> class _TpIterator>
        void _KruskalIterator<_TpVertex, _TpEdge, _TpIterator>::_incr ()
        {
          _ptr = NULL;

          while (! _edgeHeap.empty ())
          {
            _Edge** _p = _edgeHeap.pop ();
            _ptr = *_p;
            delete _p;

            if (! _set_same (*(_vertexSetHash [&(_ptr->v1 ())]), *(_vertexSetHash [&(_ptr->v2 ())])))
            {
              /*
              typename _VertexSetHash::iterator it = _vertexSetHash.begin ();
              typename _VertexSetHash::iterator itEnd = _vertexSetHash.end ();
              if (it != itEnd)
              {
                cout << "_vertexSetHash: (" << it->first << ", " << it->second << ")";
                while (++it != itEnd)
                  cout << ", (" << it->first << ", " << it->second << ")";
                cout << endl;
              }
              */

//              cout << "  joining " << _ptr->v1 ().value () << " [" << &(_ptr->v1 ()) << "] and " << _ptr->v2 ().value () << " [" << &(_ptr->v2 ()) << "]" << endl;
              _set_union (*(_vertexSetHash [&(_ptr->v1 ())]), *(_vertexSetHash [&(_ptr->v2 ())]));
              break;
            }
            else
              _ptr = NULL;
          }
        }

      template<typename _TpVertex, typename _TpEdge, template<typename> class _TpIterator>
        _KruskalIterator<_TpVertex, _TpEdge, _TpIterator>& _KruskalIterator<_TpVertex, _TpEdge, _TpIterator>::operator++()
        {
          _incr ();
          return *this;
        }

      template<typename _TpVertex, typename _TpEdge, template<typename> class _TpIterator>
        const _KruskalIterator<_TpVertex, _TpEdge, _TpIterator> _KruskalIterator<_TpVertex, _TpEdge, _TpIterator>::operator++(int)
        {
          _Self _it = *this;
          _incr ();
          return _it;
        }
    }
  }
}

#endif
