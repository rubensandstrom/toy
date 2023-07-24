#ifndef LEXER_H
#define LEXER_H

typedef struct {
  int i;
  int col;
  int row;
  char *src;
} file_t;

typedef struct {

  enum {
    TOKEN_ID,
    TOKEN_NUMBER,
    TOKEN_EQUALS,
    TOKEN_EQUALS_EQUALS,
    TOKEN_PLUS,
    TOKEN_PLUS_EQUALS,
    TOKEN_PLUS_PLUS,
    TOKEN_MINUS,
    TOKEN_MINUS_EQUALS,
    TOKEN_MINUS_MINUS,
    TOKEN_LESS,
    TOKEN_LESS_EQUALS,
    TOKEN_GREATER,
    TOKEN_GREATER_EQUALS,
    TOKEN_LPAREN,
    TOKEN_RPAREN,
    TOKEN_LBRACKET,
    TOKEN_RBRACKET,
    TOKEN_LBRACE,
    TOKEN_RBRACE,
    TOKEN_DOT,
    TOKEN_COMMA,
    TOKEN_COLON,
    TOKEN_SEMICOLON,
    TOKEN_EOF
  } type;

  char id[50];
  int value;
  int exponent;

  int row;
  int col;

} token_t;

token_t eat_token(file_t *file);
token_t eat_token_id(file_t *file);
token_t eat_token_number(file_t *file);
#endif
