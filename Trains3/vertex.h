/*
 * Vertex.h
 *
 *  Created on: Dec 23, 2013
 *      Author: jacob
 */

#ifndef VERTEX_H_
#define VERTEX_H_

#include "linked_list.h"

typedef struct vertex {
	int time;
	char *name;
	linked_list *edges;
	int key; // the distance -> For use in dijkstra
	int trainshifts;
} vertex;

/* Adds an edge to the linked list in the vertex */
void add_edge_to_vertex(vertex *v, 	int weight, int change, vertex *to);

#endif /* VERTEX_H_ */
