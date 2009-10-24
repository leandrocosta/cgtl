#include <vector>
#include <list>
#include <iostream>
using namespace std;

#include "allocator.h"
using namespace cgt::alloc;

const unsigned long KBYTE = 1024;
const unsigned long MBYTE = 1024*KBYTE;
const unsigned long GBYTE = 1024*MBYTE;

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

int main (int argc, char *argv[])
{
  std::list<int, _Allocator<int> > vec;
//  std::list<int> vec;

  cout << "num: " << atol (argv [1]) << endl;

  int i;
  for (i = 1; i <= atol (argv [1]); i++)
  {
//    cout << "push_back: " << i << endl;
    vec.push_back (i);
  }

  std::list<int, _Allocator<int> >::const_iterator it;
  std::list<int, _Allocator<int> >::const_iterator itEnd = vec.end ();

  for (it = vec.begin (); it != itEnd; ++it)
    cout << *it << endl;


//  list<int> l(1);
//  l.hello ();

  /*
  unsigned long nums = 512 * KBYTE;
  unsigned long size = KBYTE;
  unsigned long factor = atoi (argv [1]);

  nums /=factor;
  size *=factor;

  char **c = new char* [nums];
  
  unsigned int i;

  try
  {
    for (i = 0; i < nums; i++)
    {
      c [i] = new char [size];

      if (! c [i])
      {
        cout << "stop!";
        break;
      }
    }
  }
  catch (...)
  {
    cout << "catch (...)" << endl;
  }

  cout << "i: " << i << endl;
  */

  return 0;
}
