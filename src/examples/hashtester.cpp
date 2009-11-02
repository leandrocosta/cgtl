#include <iostream>
using namespace std;

#include "../cgt/base/hash/hash.h"
using namespace cgt::base::hash;

int main ()
{
  hash<int, string> s;
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

//  hash<int, string>::const_iterator it;
//  hash<int, string>::const_iterator itEnd = s.end ();


  return 0;
}
