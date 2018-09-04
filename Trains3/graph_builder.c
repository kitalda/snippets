/*
 * graph_builder.c
 */
#include "graph_builder.h"
#include "linked_list.h"
#include "vertex.h"
#include "edge.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STATION 0
#define TIME 1

// This might be handy for you when sorting
int comparator(const void* a, const void* b) {
	const vertex** vertexA = (const vertex**) a;
	const vertex** vertexB = (const vertex**) b;

//	printf("%s, %s\n", (*vertexA)->name, (*vertexB)->name);
	int result = strncmp((*vertexA)->name, (*vertexB)->name, 100);
	if (!result) {
		result = (*vertexA)->time - (*vertexB) ->time;
	}
	return result;
}

int minutesaftermidnight(char time[5]);

void add_internal_edges(int departurecounter, vertex** vertices) {
	int i;
	for (i = 0; i < departurecounter; i++) {

		vertex* v = vertices[i];

		int j;

		for (j = i; j < departurecounter; j++)
		{
			if ((strcmp(v->name, vertices[j]->name) == 0)
					&& ((vertices[j]->time - v->time) >= 5)) {
				add_edge_to_vertex(v, (vertices[j]->time - v->time), 1,
						vertices[j]);
			}
		}
	}
}

graph *build_graph(char *filename) {
	int c, l, departurecounter, state, namecounter, aftermidnight, lasttime;
	int has_last = 0;
	linked_list *departures = init_linked_list();
	graph *graph;
	char time[] = "00:00";
	char stationName[30];
	vertex** vertices;
	FILE* file = fopen(filename, "r");
	char line[256];

	namecounter = 0;
	aftermidnight = 0;
	l = 0;
	departurecounter = 0;
	lasttime = 0;

	while (fgets(line, 256, file) != 0) {
		l = 0;
		state = STATION;
		while ((c = line[l]) != '\0') {
			//printf("LINE: %s\n", line);
			//fflush(stdout);

			if (c == ' ' || c == '\t') {
				//Whitespace, do nothing
			} else if (c == ',') {
//				printf("Found , \n");
//				fflush(stdout);
				state = TIME;
				stationName[namecounter] = '\0';
				departurecounter++;
				namecounter = 0;
			} else if (c == '\n') {
//				printf("Found newline, \n");
//								fflush(stdout);
				if (state == STATION) {
					aftermidnight = 0;
					lasttime = 0;
					has_last = 0;
				} else if (state == TIME) {
					state = STATION;
				}
			} else {
//				printf("Found character \n");
//				fflush(stdout);
				if (state == STATION) {
					stationName[namecounter] = c;
					namecounter++;
				} else if (state == TIME) {
//					printf("Doing time \n");
//					fflush(stdout);
					int i;
					int min;
					vertex* v;
					for (i = 0; i < 5; i++) {
						time[i] = c;
						l++;
						c = line[l];
					}
					min = minutesaftermidnight(time);
					if (aftermidnight) {
						min += 2440;
					} else if ((lasttime != 0) && (min < lasttime)) {
						min += 2440;
						aftermidnight = 1;
					}
					//Make vertex
//					printf("station name length:%d\n", strlen(stationName));
//										fflush(stdout);
					v = malloc(sizeof(vertex));
					v->name = malloc(strlen(stationName) + 1);
					memset(v->name, '\0', strlen(stationName) + 1);
					strcpy(v->name, stationName);
					printf("station name:%s\n", v->name);
					fflush(stdout);
					v->time = min;
					v->key = 0;
					v->trainshifts = 0;
					v->edges = init_linked_list();

					//Add externeal edge to previous station
					if (has_last != 0) {
						printf("Add new edge\n");
//						add_edge_to_vertex(v, (min - lasttime), 0,
//								departures->next->data);
						add_edge_to_vertex(departures->next->data, (min - lasttime), 0, v);

					}
					//Add to departures
					add_element(departures, v);
					lasttime = min;
					has_last = 1;

//					printf("BReaking bad\n");
//					fflush(stdout);
					break;
				}
			}
			l++;
		}
	}

	//Add all vertices to a list of vertex pointers
	vertices = malloc(sizeof(vertex*) * departurecounter);
//	printf("departures %d\n", departurecounter);
//	fflush(stdout);
	int i;
	linked_list* current = departures->next;

	for (i = 0; i < departurecounter; i++) {

		vertices[i] = (vertex*) (current->data);
//		printf("%d name: %s, id %d\n", i, vertices[i]->name, vertices[i]);
//		fflush(stdout);
		current = current->next;
	}

	printf("sorting\n");
	fflush(stdout);
	qsort(vertices, departurecounter, sizeof(vertex*), comparator);
	printf("sorted\n");
	fflush(stdout);


	//Add internal edges;
	add_internal_edges(departurecounter, vertices);
	graph = malloc(sizeof(struct graph));
	graph->vertices = vertices;
	graph->number_vertices = departurecounter;
	return graph;
}

int minutesaftermidnight(char time[5]) {
	int i = 0;
	i = (time[4] - '0');
	i += ((time[3] - '0') * 10);
	i += ((time[1] - '0') * 60);
	i += ((time[0] - '0') * 600);
	return i;
}

