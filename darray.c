#define _GNU_SOURCE
#include <sys/mman.h>
#include "darray.h"
#include <stdio.h>
#define PAGESIZE (1024)

dynamic_array da_init() {
	return (dynamic_array) {
		.data = mmap(0, PAGESIZE, PROT_READ|PROT_WRITE, MAP_ANONYMOUS|MAP_PRIVATE, -1, 0),
		.length = 0,
		.capacity = PAGESIZE,
	};
}

void *da_push(dynamic_array *da, size_t size) {
	while (da->length + size >= da->capacity) {
		da->data = mremap(da->data, da->capacity, da->capacity * 2, MREMAP_MAYMOVE);
		da->capacity *= 2;
	}
	void *ptr = da->data + da->length;
	da->length += size;
	return ptr;
}

void *da_pop(dynamic_array *da, size_t size) {
	while (da->length - size < da->capacity >> 2) {
		da->data = mremap(da->data, da->capacity, da->capacity >> 1, MREMAP_MAYMOVE);
		da->capacity >>= 1;
	}
	da->length -= size;
	return da->data + da->length;
}

void da_free(dynamic_array *da) {
	munmap(da->data, da->capacity);
}

int main() {


	dynamic_array da = da_init();
	*(int *)da_push(&da, sizeof(int)) = 5;
	int a = *(int *)da_pop(&da, sizeof(int));
	da_free(&da);

	printf("%d\n", a);

}
