#include "include/lexer.h"
#include <stdint.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <stdio.h>
#include <sys/stat.h>

int i = 0;

int main(int argc, char **argv) {

  if ( argc != 2 ) {
    printf("Must provide a file as argument.\n");
    return 0;
  }
  
  int fd = open(argv[1], O_RDONLY, S_IRUSR | S_IWUSR );
  if (fd < 0) {
    fprintf(stderr, "Couldn't open file %s.\n", argv[1]);
    return 1;
  }
  
  struct stat stat;
  if (fstat(fd, &stat) == -1) {
    fprintf(stderr, "Couldn't get the size of file %s.\n", argv[1]);
    return 1;
  }
  
  printf("File size is %ld.\n", stat.st_size);
  
  char *src = mmap(NULL, stat.st_size, PROT_READ, MAP_PRIVATE, fd, 0);
  if (src == MAP_FAILED) {
    fprintf(stderr, "Couldn't map file %s.\n", argv[1]);
    return 1;
  }
  
  file_t file = {
    .src = src,
    .col = 0,
    .row = 0,
    .i = 0
  };
  
  
  
  token_t token;
  while ((token = eat_token(&file)).type != TOKEN_EOF) {
    printf("<ID: `%s`, BASE: `%d`, TYPE: `%s`, COLUMN: `%d`, ROW: `%d`>\n", token.id, token.base, token_to_string(&token), token.col, token.row);
  }
  return 0;
}

