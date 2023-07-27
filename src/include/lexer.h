#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "file.h"

#ifndef LEXER_H
#define LEXER_H
typedef enum {
    // Literals.
    TOKEN_IDENTIFIER,
    TOKEN_CHARACTER,
    TOKEN_STRING,
    TOKEN_NUMBER,

    // ARITHMETIC OPERATORj 
    TOKEN_EQUALS,
    TOKEN_PLUS,
    TOKEN_MINUS,
    TOKEN_STAR,
    TOKEN_SLASH,
    TOKEN_MODULO,
    
    // BITWISE OPERATORS
    TOKEN_AND,
    TOKEN_OR,
    TOKEN_XOR,
    TOKEN_TILDE, // Bitwise not = ~
    TOKEN_TILDE_AND,
    TOKEN_TILDE_OR,
    TOKEN_TILDE_XOR,

    // LOGICAL OPERATORS
    TOKEN_AND_AND,
    TOKEN_OR_OR,
    TOKEN_XOR_XOR,
    TOKEN_TILDE_TILDE,
    TOKEN_TILDE_AND_AND,
    TOKEN_TILDE_OR_OR,
    TOKEN_TILDE_XOR_XOR,

    // ASIGNMENTS
    TOKEN_PLUS_EQUALS,
    TOKEN_MINUS_EQUALS,
    TOKEN_STAR_EQUALS,
    TOKEN_SLASH_EQUALS,
    TOKEN_MODULO_EQUALS,
    TOKEN_AND_EQUALS,
    TOKEN_OR_EQUALS,
    TOKEN_XOR_EQUALS,
    TOKEN_TILDE_AND_EQUALS,
    TOKEN_TILDE_OR_EQUALS,
    TOKEN_TILDE_XOR_EQUALS,

    // COPMPARISONS
    TOKEN_EQUALS_EQUALS,
    TOKEN_LESS,
    TOKEN_LESS_EQUALS,
    TOKEN_GREATER,
    TOKEN_GREATER_EQUALS,
    TOKEN_TILDE_EQUALS,

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

    TOKEN_FAT_ARROW, // return type follows
    TOKEN_LARROW, // bitshift left
    TOKEN_RARROW, // bitshift right

    TOKEN_BANG, // dereference if used on identifyer or address literal
    TOKEN_ROOF, // address of if used on identifyer, pointer if used in type
    TOKEN_QMARK, // type of if used on identifyer, generic if used in type
    TOKEN_AT,
    TOKEN_HASH,

    TOKEN_ENUM,
    TOKEN_STRUCT,
    TOKEN_UNION,

    // KEYWORDS
    TOKEN_FOR,
    TOKEN_WHILE,
    TOKEN_LOOP,
    TOKEN_BREAK,
    TOKEN_CONTINUE,
    TOKEN_IF,
    TOKEN_ELSE,
    TOKEN_TYPEDEF,


    TOKEN_ERROR,
    TOKEN_EOF
  } token_type_t;

typedef struct {


  token_type_t type;
  struct {
    int start;
    int stop;
  } lexme;

  int row;
  int col;


} token_t;

token_t make_token(file_t *file, token_type_t type, int length);
token_t make_token_number(file_t *file);
bool is_keyword(file_t *file, char *word);
token_t eat_token(file_t *file);
void print_token(file_t *file, token_t *token);

char *get_token_type(token_type_t *type);
#endif
