#ifndef DARRAY_H
#define DARRAY_H

typedef struct {
	void *data;
	size_t length;
	size_t capacity;
} dynamic_array;

dynamic_array da_init();
void *da_push(dynamic_array *da, size_t size);

void *da_pop(dynamic_array *da, size_t size);

void da_free(dynamic_array *da);
#endif
