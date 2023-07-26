
#include "include/file.h"

bool init_file(file_t *file, char *path) {

  int fd = open(path, O_RDONLY, S_IRUSR | S_IWUSR );
  if (fd < 0) {
    fprintf(stderr, "Couldn't open file %s.\n", path);
    return false;
  }
  
  struct stat stat;
  if (fstat(fd, &stat) == -1) {
    fprintf(stderr, "Couldn't get the size of file %s.\n", path);
    return false;
  }
  
  printf("File size is %ld.\n", stat.st_size);
  
  char *src = mmap(NULL, stat.st_size, PROT_READ, MAP_PRIVATE, fd, 0);
  if (src == MAP_FAILED) {
    fprintf(stderr, "Couldn't map file %s.\n", path);
    return false;
  }
  
  file->index = 0;
  file->col = 0;
  file->row = 0;
  file->src = src;

  return true;
}

char peek_char(file_t *file, int offset) {
  return file->src[file->index + offset];
}
