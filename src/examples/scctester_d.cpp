#include <assert.h>

#include <string>
#include <sstream>
#include <iostream>
#include <iomanip>
using namespace std;

#include "cgt/graph.h"
using namespace cgt;

#include "util.h"

typedef graph<string, int> mygraph;

int main ()
{
  mygraph g;

  cout << "=== creating graph ===" << endl << endl;
  create_graph_1<string, int> (g);

  mygraph::scciterator it;
  mygraph::scciterator itEnd = g.stconncomp_end ();

  for (it = g.stconncomp_begin (); it != itEnd; ++it)
  {
  }

  return 0;
}
