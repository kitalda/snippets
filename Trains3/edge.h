/*
 * Edge.h
 *
 *  Created on: Dec 23, 2013
 *      Author: jacob
 */

#ifndef EDGE_H_
#define EDGE_H_

#include "vertex.h"

typedef struct edge{
	int weight;
	int change;     // Is this a change of train
	vertex *to;
} edge;

#endif /* EDGE_H_ */
