#include "../src/include/file.h"
#include "../src/include/lexer.h"
#include <stdio.h>
#include <stdlib.h>

// Dont forget to free after use.
char *substring(char *string, int start, int stop) {
  char *rv = (char *)malloc((stop - start) * sizeof(char) );
  int i = 0;
  for (int j = start; j <= stop; j++) {
    rv[i] = string[j];
    i += 1;
  }
  rv[i] = '\0';
  return rv;
}

void verify_next_token(file_t *file, token_type_t type, char *lexme) {
  token_t token = eat_token(file);
  if (token.type != type) {
    printf("[FAIL] expexted %s, got %s\n", get_token_type(&type), get_token_type(&token.type));
    return;
  }
  int i = 0;
  while (lexme[i] != '\0' && token.lexme.start + i <= token.lexme.stop) {
    if (lexme[i] != file->src[token.lexme.start + i]) {
      char *s = substring(file->src, token.lexme.start, token.lexme.stop);
      printf("[FAIL] expexted `%s` got `%s`\n", lexme, s);
      free(s);
      return;
    }
    i += 1;
  }
  char *s = substring(file->src, token.lexme.start, token.lexme.stop);
  printf("[PASS] `%s`, `%s`\n", get_token_type(&token.type), s);
  free(s);
}
int main(int argc, char **argv) {

  printf("TEST 1.\n");
  // SETUP
  char *src = "main: (argc: int, argv: @s8) => (int) : {\n\treturn 0;\n}";
  file_t file = {
    .index = 0,
    .col = 0,
    .row = 0,
    .src = src
  };
  printf("This is a test of the lexer that will test that the right tokens are produced from the following test string:\n");
  printf("\n%s\n\n", src);

  // TEST
  verify_next_token(&file, TOKEN_IDENTIFIER, "main");
  verify_next_token(&file, TOKEN_COLON, ":");
  verify_next_token(&file, TOKEN_LPAREN, "(");
  verify_next_token(&file, TOKEN_IDENTIFIER, "argc");
  verify_next_token(&file, TOKEN_COLON, ":");
  verify_next_token(&file, TOKEN_IDENTIFIER, "int");
  verify_next_token(&file, TOKEN_COMMA, ",");
  verify_next_token(&file, TOKEN_IDENTIFIER, "argv");
  verify_next_token(&file, TOKEN_COLON, ":");
  verify_next_token(&file, TOKEN_AT, "@");
  verify_next_token(&file, TOKEN_IDENTIFIER, "s8");
  verify_next_token(&file, TOKEN_RPAREN, ")");
  verify_next_token(&file, TOKEN_FAT_ARROW, "=>");
  verify_next_token(&file, TOKEN_LPAREN, "(");
  verify_next_token(&file, TOKEN_IDENTIFIER, "int");
  verify_next_token(&file, TOKEN_RPAREN, ")");
  verify_next_token(&file, TOKEN_COLON, ":");
  verify_next_token(&file, TOKEN_LBRACE, "{");
  verify_next_token(&file, TOKEN_IDENTIFIER, "return");
  verify_next_token(&file, TOKEN_NUMBER, "0");
  verify_next_token(&file, TOKEN_SEMICOLON, ";");
  verify_next_token(&file, TOKEN_RBRACE, "}");
  verify_next_token(&file, TOKEN_EOF, "");

  return 0;
}
