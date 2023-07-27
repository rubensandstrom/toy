#include "include/lexer.h"


int main(int argc, char **argv) {

  if ( argc != 2 ) {
    fprintf(stderr, "Must provide a file as argument.\n");
    return 1;
  }
  
  file_t file;
  if (!init_file(&file, argv[1])) {
    return 1;
  }
  
  
  
  token_t token;
  while ((token = eat_token(&file)).type != TOKEN_EOF) {
    print_token(&file, &token);
  }
  print_token(&file, &token);
  return 0;
}

