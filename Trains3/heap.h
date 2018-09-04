#ifndef HEAP_H_
#define HEAP_H_

#include "vertex.h"
#include "graph_builder.h"


/* Define Heap element  */
typedef struct heap {
	int number_of_elements;
	int max_elements;
	vertex **vertices;
} heap;

/* Define methods operating on the heap */

void build_min_heap(heap *h);

vertex *heap_extract_min(heap *heap);

int heap_is_empty(heap *heap);

void heap_decrease_key(heap *heap, int i, int key);

/* Initialize the heap based on the graph input and the starting city.
    The starting cities vertices can be initialized to 0 distance.
 */
heap *initialize_heap(graph *graph, char *start);


/* A dirty method that kills running times, but lets you use the already made heap easier.
    Should return the index in the heap array that has this vertex stored.
    This makes it much easier to call the heap_decrease_key function and
    avoids a lot of bookkeeping in the heap.
*/
int get_placement_for_vertex(heap *heap, vertex *vertex);

/* Helper methods - would usually not go into header, but we include them here for testing purposes */

/*
 * Assumes subtrees rootet at left(i) and right(i) are heaps
 */
void min_heapify(heap * h, int i);

int parent(int i);

int left(int i);

int right(int i);


/*
 * Swap the elements at location a and b in the array v
 */
void swap(vertex **vertices, int a, int b);

void print_heap(heap* heap);

#endif /* HEAP_H_ */
