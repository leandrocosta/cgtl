#ifndef _GRAPH_TYPE_H_
#define _GRAPH_TYPE_H_


namespace cgt
{
  typedef struct _GraphTypeDirected
  {
    enum { _directed = true };
  } _Directed;

  typedef struct _GraphTypeUndirected
  {
    enum { _directed = false };
  } _Undirected;
}

#endif
