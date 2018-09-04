/*
 travelplanning.c
 */

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>

#include "linked_list.h"
#include "vertex.h"
#include "graph_builder.h"
#include "heap.h"
#include "dijkstra.h"
#include "edge.h"

heap* init_single_source(graph *g, char *start) {
	int i;
	printf("in init, g: %d\n", g);
	fflush(stdout);
	for (i = 0; i < g->number_vertices; i++) {
		if (strcmp(g->vertices[i]->name, start) == 0) {
			g->vertices[i]->key = 0;
		} else {
			g->vertices[i]->key = 1000000;
		}
	}
	printf("for run done\n");
	fflush(stdout);
	return initialize_heap(g, start);
}

int main(int argc, char *argv[]) {

	struct heap *queue = 0;
	struct graph *graph = 0;
	char *start = argv[2];
	char *end = argv[3];
	int done = 0;
	vertex *last = 0;
	//TODO Validate input ?
	printf("%d \n", argc);
	fflush(stdout);
	printf("%s, %s \n", start, end);
	fflush(stdout);

	// Build the graph
	graph = build_graph(argv[1]);
	// Initialize the heap from the graph
	queue = init_single_source(graph, start);


	// Run dijkstra on the heap
	last = dijkstra(queue, end);
	printf("Init single source finished\n");
	fflush(stdout);

	int minutes = 0;
	minutes = (last->key - (15 * last->trainshifts));
	printf("%d %d", minutes, last->trainshifts);

	return EXIT_SUCCESS;
}
