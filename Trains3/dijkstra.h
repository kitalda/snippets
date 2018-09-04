/*
 * dijkstra.h
 */
#ifndef DIJKSTRA_H_
#define DIJKSTRA_H_

#include "heap.h"

/* Run the dijkstra algorithm on the graph represented in the <heap> submitted as argument
   As soon as you see the <to> city, you should output in the correct format and end.
 */
vertex* dijkstra(heap *heap, char *to);


#endif /* DIJKSTRA_H_ */
