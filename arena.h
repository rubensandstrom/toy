#ifndef ALLOC_H
#define ALLOC_H

typedef struct {
	void *data;
	size_t length;
	size_t capacity;
} region;

typedef struct {
	region *data;
	size_t length;
	size_t capacity;
} arena;


arena arena_init(size_t capacity);
void *arena_alloc(arena *a, size_t size);
void arena_reset(arena *a);
void arena_free(arena *a);
void arena_print(arena *a);
#endif // ALLOC_H
