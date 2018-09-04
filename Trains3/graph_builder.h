/*
 * GraphBuilder.h
 *
 *  Created on: Dec 23, 2013
 *      Author: jacob
 */

#ifndef GRAPHBUILDER_H_
#define GRAPHBUILDER_H_

#include "vertex.h"

typedef struct graph {
	int number_vertices;
	vertex **vertices;
} graph;

/* Build the graph representing the input in the <filename> input
    One way to do it, is read all lines in the file and store vertices in a linked list, while you
    add external edges.
    After this, you know how many nodes you need and you can turn the list into an array of vertex
    pointers.

    Then you can use qsort with a comparator to sort the array before adding internal edges.
    You will also need a method that converts time in format hh:mm to minutes from midnight
 */
graph *build_graph(char *filename);

#endif /* GRAPHBUILDER_H_ */
