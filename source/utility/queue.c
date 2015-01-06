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
#include "queue.h"

typedef struct QueueElement QueueElement;

struct Queue {
	QueueElement * first;
	QueueElement * last;
	unsigned int size;
	unsigned int size_of_elements;
};

struct QueueElement {
	void * value;
	QueueElement * next;
};

static QueueElement * element_free(QueueElement * element) {
	QueueElement * next = element->next;
	free(element->value);
	free(element);
	return next;
}

Queue * new_queue(unsigned int size_of_elements) {
	Queue * queue = malloc(sizeof(Queue));
	queue->first = NULL;
	queue->last = NULL;
	queue->size = 0;
	queue->size_of_elements = size_of_elements;
	return queue;
}

void queue_free(Queue * queue) {
	for ( ; queue->first != NULL ; queue->first = element_free(queue->first)) {
	}
	free(queue);
}

boolean queue_empty(Queue * queue) {
	return queue->size == 0;
}

unsigned int queue_size(Queue * queue) {
	return queue->size;
}

void queue_add(Queue * queue, void * value) {
	QueueElement * element = malloc(sizeof(QueueElement));
	element->value = malloc(queue->size_of_elements);
	memcpy(element->value, value, queue->size_of_elements);
	element->next = NULL;
	if (queue_empty(queue)) {
		queue->first = element;
	} else {
		queue->last->next = element;
	}
	queue->last = element;
	queue->size++;
}

void queue_pop(Queue * queue, void * pointer) {
	memcpy(pointer, queue->first->value, queue->size_of_elements);
	queue->first = element_free(queue->first);
	if (queue->first == NULL) {
		queue->last = NULL;
	}
	queue->size--;
}

void queue_remove(Queue * queue) {
	queue->first = element_free(queue->first);
	if (queue->first == NULL) {
		queue->last = NULL;
	}
	queue->size--;
}

void queue_get(Queue * queue, void * pointer) {
	memcpy(pointer, queue->first->value, queue->size_of_elements);
}

void queue_clear(Queue * queue) {
	for ( ; queue->first != NULL ; queue->first = element_free(queue->first)) {
	}
	queue->last = NULL;
	queue->size = 0;
}
