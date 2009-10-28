#include <iostream>
using namespace std;

#include "../cgt/vector/vector.h"
using namespace cgt::vector;

int main ()
{
  vector<int> s;

//  s.push_heap (1);
//  s.pop_heap ();
//  s.push_heap (1);

  int *p;
  vector<int>::const_iterator it;
  vector<int>::const_iterator itEnd;


  s.push_back (2);
  s.push_back (1);
  s.make_heap ();
  delete s.pop_back ();
  delete s.pop_back ();
  s.push_heap (1);

  s.push_back (7);
  s.push_back (5);

  while (! s.empty ())
    delete s.pop_back ();

  s.push_heap (2);

  it = s.begin ();
  itEnd = s.end ();
  cout << "heap: (" << *it;
  for (++it; it != itEnd; ++it)
    cout << ", " << *it;
  cout << ")" << endl;

  s.push_heap (3);

  it = s.begin ();
  itEnd = s.end ();
  cout << "heap: (" << *it;
  for (++it; it != itEnd; ++it)
    cout << ", " << *it;
  cout << ")" << endl;

  s.push_back (3);
  s.push_back (1);
  s.push_back (6);
  s.push_back (4);
  s.push_back (2);

  itEnd = s.end ();
  it = s.begin ();
  cout << "vector: (" << *it;
  for (++it; it != itEnd; ++it)
    cout << ", " << *it;
  cout << ")" << endl;

  p = s.pop_back ();
  cout << "pop: " << *p << endl;
  delete p;

  itEnd = s.end ();
  it = s.begin ();
  cout << "vector: (" << *it;
  for (++it; it != itEnd; ++it)
    cout << ", " << *it;
  cout << ")" << endl;


  itEnd = s.end ();
  it = s.begin ();
  cout << "vector: (" << *it;
  for (++it; it != itEnd; ++it)
    cout << ", " << *it;
  cout << ")" << endl;

  while (! s.empty ())
  {
    int *p = s.pop_heap ();
    cout << "pop_heap: " << *p << endl;
    delete p;

    if (! s.empty ())
    {
      itEnd = s.end ();
      it = s.begin ();
      cout << "vector: (" << *it;
      for (++it; it != itEnd; ++it)
        cout << ", " << *it;
      cout << ")" << endl;
    }
  }

  for (size_t i = 10; i > 0; i--)
  {
    cout << "push_heap: " << i << endl;
    s.push_heap (i);
  }

  itEnd = s.end ();
  it = s.begin ();
  cout << "heap: (" << *it;
  for (++it; it != itEnd; ++it)
    cout << ", " << *it;
  cout << ")" << endl;

  return 0;
}
