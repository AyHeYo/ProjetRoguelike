/**
 * @file utility/list.c
 * Fichier implémentant une liste en utilisant la mise en oeuvre par pointeur.
 * @author Hector Basset
 * @date 12 décembre 2014
 */

//librairies du système
#include <stdlib.h>
#include <string.h>

//librairies utilitaires
#include "boolean.h"
#include "list.h"

typedef struct ListElement ListElement;

struct List {
	ListElement * first;
	ListElement * last;
	ListElement * current;
	unsigned int size;
	unsigned int size_of_elements;
};

struct ListElement {
	void * value;
	ListElement * previous;
	ListElement * next;
};

static ListElement * new_element(List * list, void * value) {
	ListElement * element = malloc(sizeof(ListElement));
	element->value = malloc(list->size_of_elements);
	memcpy(element->value, value, list->size_of_elements);
	return element;
}

static void first_element(List * list, ListElement * element) {
	list->first = list->last = list->current = element;
	element->previous = element->next = NULL;
	list->size = 1;
}

static ListElement * element_free(ListElement * element) {
	ListElement * next = element->next;
	free(element->value);
	free(element);
	return next;
}

List * new_list(unsigned int size_of_elements) {
	List * list = malloc(sizeof(List));
	list->first = NULL;
	list->last = NULL;
	list->current = NULL;
	list->size = 0;
	list->size_of_elements = size_of_elements;
	return list;
}

void list_free(List * list) {
	for (list_begin(list) ; !list_out(list) ; list->current = element_free(list->current)) {
	}
	free(list);
}

boolean list_empty(List * list) {
	return list->size == 0;
}

unsigned int list_size(List * list) {
	return list->size;
}

void list_begin(List * list) {
	list->current = list->first;
}

void list_end(List * list) {
	list->current = list->last;
}

void list_previous(List * list) {
	list->current = list->current->previous;
}

void list_next(List * list) {
	list->current = list->current->next;
}

boolean list_at_begin(List * list) {
	return list->current == list->first;
}

boolean list_at_end(List * list) {
	return list->current == list->last;
}

boolean list_out(List * list) {
	return list->current == NULL;
}

void list_add_before(List * list, void * value) {
	ListElement * element = new_element(list, value);
	if (list_empty(list)) {
		first_element(list, element);
	} else {
		element->previous = list->current->previous;
		if (list_at_begin(list)) {
			list->first = element;
		} else {
			list->current->previous->next = element;
		}
		element->next = list->current;
		list->current->previous = element;
		list->size++;
	}
}

void list_add_after(List * list, void * value) {
	ListElement * element = new_element(list, value);
	if (list_empty(list)) {
		first_element(list, element);
	} else {
		element->next = list->current->next;
		if (list_at_end(list)) {
			list->last = element;
		} else {
			list->current->next->previous = element;
		}
		element->previous = list->current;
		list->current->next = element;
		list->size++;
	}
}

void list_add_begin(List * list, void * value) {
	ListElement * element = new_element(list, value);
	if (list_empty(list)) {
		first_element(list, element);
	} else {
		element->previous = NULL;
		element->next = list->first;
		list->first->previous = element;
		list->first = element;
		list->size++;
	}
}

void list_add_end(List * list, void * value) {
	ListElement * element = new_element(list, value);
	if (list_empty(list)) {
		first_element(list, element);
	} else {
		element->next = NULL;
		element->previous = list->last;
		list->last->next = element;
		list->last = element;
		list->size++;
	}
}

void list_remove(List * list) {
	if (list_at_begin(list)) {
		list->first = list->current->next;
	} else {
		list->current->previous->next = list->current->next;
	}
	if (list_at_end(list)) {
		list->last = list->current->previous;
	} else {
		list->current->next->previous = list->current->previous;
	}
	list->current = element_free(list->current);
	list->size--;
}

void list_remove_first(List * list) {
	ListElement * current = list_at_begin(list) ? list->first->next : list->current;
	list_begin(list);
	list_remove(list);
	list->current = current;
}

void list_remove_last(List * list) {
	ListElement * current = list_at_end(list) ?  NULL : list->current;
	list_end(list);
	list_remove(list);
	list->current = current;
}

void list_remove_value(List * list, void * value) {
	ListElement * current = list->current;
	for (list_begin(list) ; !list_out(list) ; ) {
		if (memcmp(list->current->value, value, list->size_of_elements) == 0) {
			if (list->current == current) {
				list->current = current->next;
			}
			list_remove(list);
		} else {
			list_next(list);
		}
	}
	list->current = current;
}

void list_clear(List * list) {
	for (list_begin(list) ; !list_out(list) ; list->current = element_free(list->current)) {
	}
	list->size = 0;
}

void list_get_value(List * list, void * pointer) {
	memcpy(pointer, list->current->value, list->size_of_elements);
}

void list_get_first(List * list, void * pointer) {
	memcpy(pointer, list->first->value, list->size_of_elements);
}

void list_get_last(List * list, void * pointer) {
	memcpy(pointer, list->last->value, list->size_of_elements);
}
