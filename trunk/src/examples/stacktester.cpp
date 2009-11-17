#include <iostream>
using namespace std;

#include "../cgt/base/stack.h"
using namespace cgt::base;

int main ()
{
  stack<int> s;

  cout << "push 2" << endl;
  s.push (2);
  cout << "push 3" << endl;
  s.push (3);
  cout << "push 1" << endl;
  s.push (1);

  stack<int>::const_iterator it = s.begin ();
  stack<int>::const_iterator itEnd = s.end ();

  cout << "stack (" << *it;
  for (++it; it != itEnd; ++it)
    cout << ", " << *it;
  cout << ")" << endl;

  while (! s.empty ())
  {
    cout << "top: " << *(s.top ()) << endl;
    int *_ptr = s.pop ();
    cout << "pop: " << *_ptr << endl;
    delete _ptr;
  }

  itEnd = s.end ();
  cout << "stack: (";
  for (it = s.begin (); it != itEnd; ++it)
    cout << ", " << *it;
  cout << ")" << endl;

  return 0;
}
