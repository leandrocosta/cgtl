#include <iostream>
using namespace std;

#include "cgt/base/hash.h"
using namespace cgt::base;

int main ()
{
  cgt::base::hash<int, string> s;
  s.insert (1, "A");
  s.insert (2, "B");
  s.insert (3, "C");
  s.insert (4, "D");
  s.insert (5, "E");

  /*
  cout << "hash [1]: " << *(s[1]) << endl;
  cout << "hash [2]: " << *(s[2]) << endl;
  cout << "hash [3]: " << *(s[3]) << endl;
  cout << "hash [4]: " << *(s[4]) << endl;
  cout << "hash [5]: " << *(s[5]) << endl;
  */

  s.dump ();

  hash<int, string>::const_iterator it;
  hash<int, string>::const_iterator itEnd = s.end ();

  for (it = s.begin (); it != itEnd; ++it)
  {
//    cout << "hash [" << it->key () << "]: " << it->value () << endl;
//    cout << "hash []: " << *it << endl;
    cout << "hash [" << it->first << "]: " << it->second << endl;
//    it->second = "a";
  }

  return 0;
}
