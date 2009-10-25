#include <iostream>
using namespace std;

#include "../cgt/list/list.h"
using namespace cgt::list;

int main ()
{
  list<int> s;

  cout << "insert 12" << endl;
  s.insert (12);
  cout << "insert 11" << endl;
  s.insert (11);
  cout << "insert 10" << endl;
  s.insert (10);
  cout << "insert 9" << endl;
  s.insert (9);
  cout << "insert 7" << endl;
  s.insert (7);
  cout << "insert 4" << endl;
  s.insert (4);
  cout << "insert 8" << endl;
  s.insert (8);
  cout << "insert 1" << endl;
  s.insert (1);
  cout << "insert 2" << endl;
  s.insert (2);
  cout << "insert 6" << endl;
  s.insert (6);
  cout << "insert 5" << endl;
  s.insert (5);
  cout << "insert 3" << endl;
  s.insert (3);

  s.make_heap ();

  list<int>::const_iterator it = s.begin ();
  list<int>::const_iterator itEnd = s.end ();

  cout << "list (" << *it;
  for (++it; it != itEnd; ++it)
    cout << ", " << *it;
  cout << ")" << endl;

  int* pInt = s.pop_heap ();
  cout << "pop_heap: " << *pInt << endl;
  delete pInt;

  it = s.begin ();
  itEnd = s.end ();

  cout << "list (" << *it;
  for (++it; it != itEnd; ++it)
    cout << ", " << *it;
  cout << ")" << endl;

  return 0;
}
