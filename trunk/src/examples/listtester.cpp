#include <iostream>
using namespace std;

#include "../cgt/list/list.h"
using namespace cgt::list;

int main ()
{
  list<int> s;

  cout << "push_back 3" << endl;
  s.push_back (3);
  cout << "push_front 2" << endl;
  s.push_front (2);
  cout << "insert 1" << endl;
  s.insert (1);

  list<int>::const_iterator it = s.begin ();
  list<int>::const_iterator itEnd = s.end ();

  cout << "list (" << *it;
  for (++it; it != itEnd; ++it)
    cout << ", " << *it;
  cout << ")" << endl;

  while (! s.empty ())
  {
    cout << "front: " << *(s.front ()) << endl;
    int *_ptr = s.pop_front ();
    cout << "pop_front: " << *_ptr << endl;
    delete _ptr;

    /*
    if (! s.empty ())
    {
      int *_ptr = s.pop_back ();
      cout << "pop_back: " << *_ptr << endl;
      delete _ptr;
    }
    */
  }

  itEnd = s.end ();
  cout << "list: (";
  for (it = s.begin (); it != itEnd; ++it)
    cout << ", " << *it;
  cout << ")" << endl;

  return 0;
}
