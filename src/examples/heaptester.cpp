#include <iostream>
using namespace std;

#include "../cgt/heap/heap.h"
using namespace cgt::heap;

int main ()
{
  heap<int> s;

  cout << "push 12" << endl;
  s.push (12);
  cout << "push 11" << endl;
  s.push (11);
  cout << "push 10" << endl;
  s.push (10);
  cout << "push 9" << endl;
  s.push (9);
  cout << "push 7" << endl;
  s.push (7);
  cout << "push 4" << endl;
  s.push (4);
  cout << "push 8" << endl;
  s.push (8);
  cout << "push 1" << endl;
  s.push (1);
  cout << "push 2" << endl;
  s.push (2);
  cout << "push 6" << endl;
  s.push (6);
  cout << "push 5" << endl;
  s.push (5);
  cout << "push 3" << endl;
  s.push (3);

  heap<int>::const_iterator it = s.begin ();
  heap<int>::const_iterator itEnd = s.end ();

  cout << "heap (" << *it;
  for (++it; it != itEnd; ++it)
    cout << ", " << *it;
  cout << ")" << endl;

  it = s.find (3);
  s.modify (it, 20);

  it = s.begin ();
  itEnd = s.end ();
  cout << "heap (" << *it;
  for (++it; it != itEnd; ++it)
    cout << ", " << *it;
  cout << ")" << endl;

  while (! s.empty ())
  {
    int* pInt = s.pop ();
    cout << "pop: " << *pInt << endl;
    delete pInt;

    if (! s.empty ())
    {
      it = s.begin ();
      itEnd = s.end ();
      cout << "heap (" << *it;
      for (++it; it != itEnd; ++it)
        cout << ", " << *it;
      cout << ")" << endl;
    }
  }

  return 0;
}
