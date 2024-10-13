#define _GNU_SOURCE
#include <sys/mman.h>
#include "darray.h"
#include <stdio.h>
#include <stdint.h>
#define PAGESIZE (4096)

dynamic_array da_init() {
	return (dynamic_array) {
		.data = mmap(0, PAGESIZE, PROT_READ|PROT_WRITE, MAP_ANONYMOUS|MAP_PRIVATE, -1, 0),
		.length = 0,
		.capacity = PAGESIZE,
	};
}

void *da_push(dynamic_array *da, size_t size) {
	while (da->length + size >= da->capacity) {
		if (da->capacity > SIZE_MAX >> 1) {

		}
		da->data = mremap(da->data, da->capacity, da->capacity << 1, MREMAP_MAYMOVE);
		da->capacity <<= 1;
	}
	void *ptr = da->data + da->length;
	da->length += size;
	return ptr;
}

void *da_pop(dynamic_array *da, size_t size) {
	while (da->length - size < da->capacity >> 2 ) {
		if (da->capacity >> 2 < PAGESIZE) break;
		da->data = mremap(da->data, da->capacity, da->capacity >> 1, MREMAP_MAYMOVE);
		da->capacity >>= 1;
	}
	da->length -= size;
	return da->data + da->length;
}

void da_free(dynamic_array *da) {
	munmap(da->data, da->capacity);
}
