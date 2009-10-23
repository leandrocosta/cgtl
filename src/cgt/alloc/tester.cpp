#include <iostream>
using namespace std;

#include "allocator.h"
using namespace cgt::alloc;


template<typename _Tp>
class node
{
  public:
    node ()
    {
      cout << "node ()" << endl; 
    }
    node (_Tp &v) : value (v)
    {
      cout << "node (_Tp&)" << endl; 
    }
    node (const node& _n)
    {
      cout << "node (node&)" << endl; 
      *this = _n;
    }
    virtual ~node ()
    {
      cout << "~node ()" << endl; 
    }

    node& operator=(const node& _other)
    {
      cout << "node::operator=()" << endl; 
      value = _other.value;
      return *this;
    }

    _Tp value;
};

template<typename _Tp, typename _Alloc = _Allocator<_Tp> >
class list
{
  typedef node<_Tp> _Node;
  typedef typename _Alloc::template rebind<_Node>::other allocator_type;

  public:
    list (_Tp v)
    {
      cout << "before _alloc.allocate ()" << endl;
      _ptr_node = _alloc.allocate (1);
      cout << "before _alloc.construct ()" << endl;
      _alloc.construct (_ptr_node, _Node (v));
    }
    virtual ~list()
    {
      cout << "before _alloc.destroy ()" << endl;
      _alloc.destroy (_ptr_node);
      cout << "before _alloc.deallocate ()" << endl;
      _alloc.deallocate (_ptr_node, 1);
    }
    void hello () { cout << "_ptr_node->value: " << _ptr_node->value << endl; }

    _Node*          _ptr_node;
    allocator_type  _alloc;
};

int main ()
{
  /*
  list<int> l(1);
  l.hello ();
  */

  list<int> *pList = new list<int>(1);
  pList->hello ();
  delete pList;

//  char [sizeof (int)] c;

  char c[sizeof (int)];

  return 0;
}
