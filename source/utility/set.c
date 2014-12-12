
#include <stdlib.h>
#include <string.h>

#include "boolean.h"
#include "set.h"

typedef struct SetElement SetElement;

struct Set {
	SetElement * first;
	int size;
	unsigned int size_of_elements;
};

struct SetElement {
	void * value;
	SetElement * next;
};

SetElement * free_element(SetElement * element) {
	SetElement * next = element->next;
	free(element->value);
	free(element);
	return next;
}

Set * new_set(unsigned int size_of_elements) {
	Set * set = (Set *) malloc(sizeof(Set));
	set->first = NULL;
	set->size = 0;
	set->size_of_elements = size_of_elements;
	return set;
}

boolean set_empty(Set * set) {
	return set->size == 0;
}

int set_size(Set * set) {
	return set->size;
}

void set_add(Set * set, void * value) {
	SetElement * element = (SetElement *) malloc(sizeof(SetElement));
	element->value = malloc(set->size_of_elements);
	memcpy(element->value, value, set->size_of_elements);
	element->next = set->first;
	set->first = element;
	set->size++;
}

void set_remove(Set * set, void * value) {
	SetElement * element = set->first;
	while (element != NULL) {
		if (memcmp(element->value, value, set->size_of_elements)) {
			element = free_element(element);
			set->size--;
		} else {
			element = element->next;
		}
	}
}

void set_clear(Set * set) {
	SetElement * element;
	for (element = set->first ; element != NULL ; element = free_element(element)) {
	}
	set->size = 0;
}

void set_foreach(Set * set, void (* function)(void *)) {
	SetElement * element;
	for (element = set->first ; element != NULL ; element = element->next) {
		function(element->value);
	}
}

void set_free(Set * set) {
	SetElement * element;
	for (element = set->first ; element != NULL ; element = free_element(element)) {
	}
	free(set);
}
