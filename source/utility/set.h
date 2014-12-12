
#ifndef UTILITY_SET_H

#define UTILITY_SET_H

#include "boolean.h"

typedef struct Set Set;

Set * new_set(unsigned int size_of_elements);

boolean set_empty(Set * set);

int set_size(Set * set);

void set_add(Set * set, void * value);

void set_remove(Set * set, void * value);

void set_clear(Set * set);

void set_foreach(Set * set, void (* function)(void *));

void set_free(Set * set);

#endif
