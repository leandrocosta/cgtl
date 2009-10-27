#include <iostream>
using namespace std;

#include "../cgt/vector/vector.h"
using namespace cgt::vector;

int main ()
{
  vector<int> s;
  s.push_back (1);
  s.push_back (2);
  s.push_back (3);
  s.push_back (4);
  s.push_back (5);
  s.push_back (6);
  s.push_back (7);

  vector<int>::const_iterator it;
  vector<int>::const_iterator itEnd = s.end ();

  it = s.begin ();
  cout << "vector: (" << *it;
  for (++it; it != itEnd; ++it)
    cout << ", " << *it;
  cout << ")" << endl;

  /*
  cout << "push_back 3" << endl;
  cout << "push_front 2" << endl;
  s.push_front (2);
  cout << "insert 1" << endl;
  s.insert (1);

  cout << "---" << endl;
  vector<int>::const_iterator itfind = s.find (2);
  cout << "itfind (2): " << *itfind << endl;
  cout << "---" << endl;

  vector<int>::const_iterator it = s.begin ();
  vector<int>::const_iterator itEnd = s.end ();

  cout << "vector (" << *it;
  for (++it; it != itEnd; ++it)
    cout << ", " << *it;
  cout << ")" << endl;

  while (! s.empty ())
  {
    cout << "front: " << *(s.front ()) << endl;
    int *_ptr = s.pop_front ();
    cout << "pop_front: " << *_ptr << endl;
    delete _ptr;
  }

  itEnd = s.end ();
  cout << "vector: (";
  for (it = s.begin (); it != itEnd; ++it)
    cout << ", " << *it;
  cout << ")" << endl;
  */

  return 0;
}
