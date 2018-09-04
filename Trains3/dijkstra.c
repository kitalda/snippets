/*
 * dijkstra.c
 *
 *  Created on: Dec 30, 2013
 *      Author: jacob
 */

#include <stdio.h>
#include <string.h>

#include "dijkstra.h"
#include "vertex.h"
#include "edge.h"


void relax(heap *heap, vertex *from, vertex *to, int weight , int shifts) {
		if (shifts) {
			weight += 15;
		}
		if (to->key > (from->key + weight)) {
			printf("Updating relax\n");
			to->key = from->key + weight;

			printf("Key is now : %d\n", to->key);
			if (shifts) {
				to->trainshifts++;
			}
			build_min_heap(heap);
			//Would probably have been better if heap-decrease_key could be used, but it needs the index
			//of the vertex
		}
}

vertex* dijkstra(heap *heap, char *to) {
	int done = 0;
	while (!heap_is_empty(heap) && !done) {
			vertex *v = heap_extract_min(heap);

			printf("Current v : %d, %s\n", v->key, v->name);

			if (strcmp(v->name, to) != 0) {
				linked_list *iterator = v->edges->next;

				printf("Ed next : %d\n", v->edges->next);
				printf("Ed      : %d\n", v->edges);

				while (v->edges != iterator) {
					printf("checking edge\n");
					edge *e = iterator->data;
					relax(heap, v, e->to, e->weight, e->change);
					iterator = iterator->next;
				}
			}
			else
			{
				return v;
			}

		}
}
