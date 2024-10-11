#define _GNU_SOURCE
#include <sys/mman.h>
#include <stdio.h>
#include <assert.h>
#include "arena.h"

#define KB (1<<10)
#define MB (1<<20)
#define GB (1<<30)
#define TB (1<<40)

#define PAGESIZE (1024)
arena arena_init(size_t capacity) {
	arena a = {
		.data = (region *)mmap(0, PAGESIZE * sizeof(region), PROT_READ|PROT_WRITE, MAP_ANONYMOUS|MAP_PRIVATE, -1, 0),
		.length = 0,
		.capacity = PAGESIZE,
	};
	size_t region_capacity = ((capacity / (PAGESIZE + 1) ) + 1 ) * PAGESIZE;
	a.data[0].data = mmap(0, region_capacity, PROT_READ|PROT_WRITE, MAP_ANONYMOUS|MAP_PRIVATE, -1, 0);
	a.data[0].length = 0;
	a.data[0].capacity = region_capacity;
	a.length++;
	return a;
}

void *arena_alloc(arena *a, size_t size) {
	assert(size < a->data[0].capacity);
	region *current; 
	for (int i = 0; i < a->length; i++) {
		current = &a->data[i];
		if (current->length + size < current->capacity) {
			void *ptr = current->data + current->length;
			current->length += size;
			return ptr;
		}
	}
	if (a->length == a->capacity) {
		a->data = mremap(a->data, a->capacity * sizeof(region), a->capacity * sizeof(region) * 2, MREMAP_MAYMOVE);
		a->capacity *= 2;
	}
	current = &a->data[a->length];
	current->data = mmap(0, a->data[0].capacity, PROT_READ|PROT_WRITE, MAP_ANONYMOUS|MAP_PRIVATE, -1, 0);
	current->capacity = a->data[0].capacity;
	a->length++;

	void *ptr = current->data + current->length;
	current->length += size;
	return ptr;
}

void arena_reset(arena *a) {
	region *current;
	for (int i = 0; i < a->length; i++) {
		current = &a->data[i];
		current->length = 0;
	}
}

void arena_free(arena *a) {
	region *current;
	for (int i = 0; i < a->length; i++) {
		current = &a->data[i];
		munmap(current->data, current->capacity);
		current->length = 0;
		current->capacity = 0;
	}
	munmap(a->data, a->capacity * sizeof(region));
	a->data = NULL;
	a->length = 0;
	a->capacity = 0;
}

void arena_print(arena *a) {
	region *current;
	for (int i = 0; i < a->length; i++) {
		current = &a->data[i];
		printf("data: %p, length: %zu, capacity: %zu\n", current->data, current->length, current->capacity);
	}
}
