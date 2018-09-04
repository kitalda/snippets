/*
 * linked_list.h
 *
 *  Created on: Dec 24, 2013
 *      Author: jacob
 */

#ifndef LINKED_LIST_H_
#define LINKED_LIST_H_


typedef struct  linked_list{
	void *data;
	struct linked_list *next;
	struct linked_list *previous;
} linked_list;

linked_list *init_linked_list();

void add_element( linked_list *list, void *element);

int linked_list_size(linked_list *list);

void destroy_list(linked_list *list);

#endif /* LINKED_LIST_H_ */
