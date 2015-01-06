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
#include "stack.h"

typedef struct StackElement StackElement;

struct Stack {
	StackElement * top;
	unsigned int size;
	unsigned int size_of_elements;
};

struct StackElement {
	void * value;
	StackElement * next;
};

static StackElement * element_free(StackElement * element) {
	StackElement * next = element->next;
	free(element->value);
	free(element);
	return next;
}

Stack * new_stack(unsigned int size_of_elements) {
	Stack * stack = malloc(sizeof(Stack));
	stack->top = NULL;
	stack->size = 0;
	stack->size_of_elements = size_of_elements;
	return stack;
}

void stack_free(Stack * stack) {
	for ( ; stack->top != NULL ; stack->top = element_free(stack->top)) {
	}
	free(stack);
}

boolean stack_empty(Stack * stack) {
	return stack->size == 0;
}

unsigned int stack_size(Stack * stack) {
	return stack->size;
}

void stack_push(Stack * stack, void * value) {
	StackElement * element = malloc(sizeof(StackElement));
	element->value = malloc(stack->size_of_elements);
	memcpy(element->value, value, stack->size_of_elements);
	element->next = stack->top;
	stack->top = element;
	stack->size++;
}

void stack_pop(Stack * stack, void * pointer) {
	memcpy(pointer, stack->top->value, stack->size_of_elements);
	stack->top = element_free(stack->top);
	stack->size--;
}

void stack_remove(Stack * stack) {
	stack->top = element_free(stack->top);
	stack->size--;
}

void stack_get(Stack * stack, void * pointer) {
	memcpy(pointer, stack->top->value, stack->size_of_elements);
}

void stack_clear(Stack * stack) {
	for ( ; stack->top != NULL ; stack->top = element_free(stack->top)) {
	}
	stack->size = 0;
}
