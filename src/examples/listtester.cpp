#include <iostream>
using namespace std;

#include "../cgt/list/list.h"
using namespace cgt::list;

int main ()
{
  list<int> l;

  cout << "insert 2..." << endl;
  l.insert (2);
  cout << "push_back 3..." << endl;
  l.push_back (3);
  cout << "push_front 1..." << endl;
  l.push_front (1);

  list<int>::const_iterator it = l.begin ();
  list<int>::const_iterator itEnd = l.end ();

  cout << "list: " << *it;

  for (++it; it != itEnd; ++it)
    cout << ", " << *it;

  cout << "." << endl;

  return 0;
}
