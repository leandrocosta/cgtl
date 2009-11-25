#include <iostream>
using namespace std;

#include "cgt/base/heap.h"

void _modify (int& i, const int& value)
{
  i = value;
}

int main ()
{
  cgt::base::heap<int> s;

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

  cgt::base::heap<int>::const_iterator it = s.begin ();
  cgt::base::heap<int>::const_iterator itEnd = s.end ();

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

  it = s.find (4);
  s.modify_by (it, _modify, 40);;

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

  /*
  cout << "ptr_heap:" << endl << endl;

  cgt::base::ptr_heap<int*> si;

  cout << "push 1" << endl;
  si.push (new int (1));
  cout << "push 6" << endl;
  si.push (new int (6));
  cout << "push 2" << endl;
  si.push (new int (2));
  cout << "push 5" << endl;
  si.push (new int (5));
  cout << "push 3" << endl;
  si.push (new int (3));

  cgt::base::ptr_heap<int*>::const_iterator iti = si.begin ();
  cgt::base::ptr_heap<int*>::const_iterator itiEnd = si.end ();

  cout << "heap (" << *(*iti);
  for (++iti; iti != itiEnd; ++iti)
    cout << ", " << *(*iti);
  cout << ")" << endl;

  while (! si.empty ())
  {
    int** pInt = si.pop ();
    cout << "pop: " << **pInt << endl;
    delete pInt;

    if (! si.empty ())
    {
      iti = si.begin ();
      itiEnd = si.end ();
      cout << "heap (" << **iti;
      for (++iti; iti != itiEnd; ++iti)
        cout << ", " << **iti;
      cout << ")" << endl;
    }
  }
*/

  return 0;
}
