#include <stdbool.h>
#include <stdint.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <stdio.h>
#include <sys/stat.h>

#ifndef FILE_H
#define FILE_H

typedef struct {
  int index;
  int row;
  int col;
  char *src;
} file_t;

bool init_file(file_t *file, char *path);
char peek_char(file_t *file, int offset);
#endif
