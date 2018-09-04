#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "heap.h"

int get_placement_for_vertex(heap *heap, vertex *vertex) {
	return -1;
}

void build_min_heap(heap * h) {
	int i;
	if (!heap_is_empty(h)) {
		int n = h->number_of_elements;
		for (i = (n / 2); i > 0; i--) {
			min_heapify(h, i);
		}
	}
}

int heap_is_empty(heap *heap) {
	if (heap->number_of_elements > 0) {
		return 0;
	}
	return 1;
}

heap *initialize_heap(graph *graph, char *start) {
	int i;
	heap* my_heap = malloc(sizeof(heap));
	my_heap->number_of_elements = graph->number_vertices;
	my_heap->max_elements = graph->number_vertices;
	my_heap->vertices = malloc(sizeof(vertex*) * (graph->number_vertices+1));
	for(i = 1; i <= graph->number_vertices; i++)
	{
		my_heap->vertices[i] = graph->vertices[i-1];
	}
	build_min_heap(my_heap);
	return my_heap;
}

vertex *heap_extract_min(heap *heap) {
	vertex *min;

	if (!heap_is_empty(heap)) {
		min = heap->vertices[1];
		if (heap->number_of_elements > 1) {
			swap(heap->vertices, 1, heap->number_of_elements);
			heap->number_of_elements--;
			min_heapify(heap, 1);
		}
		return min;
	}
	return NULL;
}

void heap_decrease_key(heap *heap, int i, int key) {
	if (heap->vertices[i]->key > key) {
		heap->vertices[i]->key = key;
		while (i > 1 && heap->vertices[parent(i)]->key > key) {
			swap(heap->vertices, i, parent(i));
			i = parent(i);
		}
	}
}

void min_heapify(heap* h, int i) {
	int leftkey;
	int rightkey;
	int rootkey;
	int maxIndex = h->number_of_elements;
	if ((maxIndex > 1) && (left(i) <= maxIndex)) {
		/* Then we know it has a root and a left child at least */
		leftkey = h->vertices[left(i)]->key;
		rootkey = h->vertices[i]->key;
		if (right(i) >= maxIndex) {
			/* The case where it only has a left child */
			if (rootkey > leftkey) {
				swap(h->vertices, i, left(i));
				/* Normally we would have to heapify the left tree now,
				 * but since there only was two vertices, they are ordered now.
				 */
			}
			/*
			 * Whether we swapped or not, in this case the (sub)heap is ordered now
			 */
			return;
		} else {
			rightkey = h->vertices[right(i)]->key;
			if (leftkey <= rightkey) {
				if (leftkey < rootkey) {
					swap(h->vertices, i, left(i));
					min_heapify(h, left(i));
				}
			} else if (rightkey < rootkey) {
				swap(h->vertices, i, right(i));
				min_heapify(h, right(i));
			}
		}
	}
	/* If there are 0 or 1 element, the heap is ordered by default, and we are done*/
}

/* Convenient for debugging. */
void print_heap(heap* heap) {
	int i;
	for (i = 1; i <= heap->number_of_elements; i++) { // Remember heap is 1 indexed in cormen ;)
		printf("%i -> %i\n", i, heap->vertices[i]->key);
	}
}

int parent(int i) {
	if ((i % 2) == 0)
		return i / 2;
	else
		return (i - 1) / 2;
}

int left(int i) {
	return 2 * i;
}

int right(int i) {
	return 2 * i + 1;
}

void swap(vertex **vertices, int a, int b) {
	vertex *ata = vertices[a];
	vertex *atb = vertices[b];

	vertices[a] = atb;
	vertices[b] = ata;
}
