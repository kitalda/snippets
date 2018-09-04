/*
 * vertex.c
 *
 *  Created on: Dec 30, 2013
 *      Author: jacob
 */

#include "vertex.h"
#include "edge.h"
#include "linked_list.h"
#include <stdlib.h>
#include <stdio.h>

void add_edge_to_vertex(vertex *v, 	int weight, int change, vertex *to) {
    // Allocate memory for edge
	struct edge *temp;
	temp = malloc(sizeof(edge));
	// Set values correctly
	temp->weight = weight;
	temp->change = change;
	temp->to = to;

    // Add element to edge list
	add_element(v->edges, temp);
}
