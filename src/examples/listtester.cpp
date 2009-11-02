#include <iostream>
using namespace std;

#include "../cgt/base/list/list.h"
using namespace cgt::base::list;

const bool is_even (const int& i) { return ! (i % 2); }
const bool is_odd (const int& i) { return (i % 2); }
const bool is_less_then (const int& i, const int& parm) { return (i < parm); }
const bool is_greater_then (const int& i, const int& parm) { return (i > parm); }

int main ()
{
  cgt::base::list::list<int> s;

  cout << "push_back 3" << endl;
  s.push_back (3);
  cout << "push_front 2" << endl;
  s.push_front (2);
  cout << "insert 1" << endl;
  s.insert (1);

  cout << "---" << endl;
  list<int>::const_iterator itfind = s.find (2);
  cout << "itfind (2): " << *itfind << endl;
  cout << "---" << endl;

  list<int>::const_iterator it = s.begin ();
  list<int>::const_iterator itEnd = s.end ();

  cout << "list (" << *it;
  for (++it; it != itEnd; ++it)
    cout << ", " << *it;
  cout << ")" << endl;

  it = cgt::base::list::find_if (s.begin (), s.end (), is_even);
  if (it != s.end ())
    cout << "is_even: " << *it << endl;
  it = cgt::base::list::find_if (s.begin (), s.end (), is_odd);
  if (it != s.end ())
    cout << "is_odd: " << *it << endl;
  it = cgt::base::list::find_if (s.begin (), s.end (), is_less_then, 2);
  if (it != s.end ())
    cout << "is_less_then 2: " << *it << endl;
  it = cgt::base::list::find_if (s.begin (), s.end (), is_greater_then, 2);
  if (it != s.end ())
    cout << "is_greater_then 2: " << *it << endl;

  while (! s.empty ())
  {
    cout << "front: " << *(s.front ()) << endl;
    int *_ptr = s.pop_front ();
    cout << "pop_front: " << *_ptr << endl;
    delete _ptr;
  }

  itEnd = s.end ();
  cout << "list: (";
  for (it = s.begin (); it != itEnd; ++it)
    cout << ", " << *it;
  cout << ")" << endl;

  return 0;
}
