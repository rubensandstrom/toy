#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "include/lexer.h"

token_t eat_token(file_t *file) {

  char c = file->src[file->i];
  char l = file->src[file->i + 1];

  while ( c != '\0' ) {
    if ( ( c >= 'a' && c <= 'z' ) || ( c >= 'A' && c <= 'Z' ) || c == '_' ) { // change to utf-8 later.
      return eat_token_id( file );
    }
    if (c >= '0' && c <= '9') {
      return eat_token_number( file );
    }
    switch ( c ) {

      case ' ' :
      case '\t' : {
        file->i += 1;
        file->col += 1;
        c = file->src[file->i];
        l = file->src[file->i + 1];
        continue;
      }

      case '\n' : {
        file->i += 1;
        file->col = 0;
        file->row += 1;
        c = file->src[file->i];
        l = file->src[file->i + 1];
        continue;
      }

      case '=' : {
        if ( l == '=' ) {
          token_t token = {
            .type = TOKEN_EQUALS_EQUALS,
            .id = "==",
            .col = file->col,
            .row = file->row,
            .base = 0,
            .exponent = 0,
          };
          file->i += 2;
          file->col += 2;
          return token;
        }

        else {
          token_t token = {
            .type = TOKEN_EQUALS,
            .id = "=",
            .col = file->col,
            .row = file->row,
            .base = 0,
            .exponent = 0,
          };
          file->i += 1;
          file->col += 1;
          return token;
        }
      }

      case '+' : {
        if ( l == '+' ) {
          token_t token = {
            .type = TOKEN_PLUS_PLUS,
            .id = "++",
            .col = file->col,
            .row = file->row,
            .base = 0,
            .exponent = 0,
          };
          file->i += 2;
          file->col += 2;
          return token;
        }

        if ( l == '=' ) {
          token_t token = {
            .type = TOKEN_PLUS_EQUALS,
            .id = "+=",
            .col = file->col,
            .row = file->row,
            .base = 0,
            .exponent = 0,
          };
          file->i += 2;
          file->col += 2;
          return token;
        }
        
        else {
          token_t token = {
            .type = TOKEN_PLUS,
            .id = "+",
            .col = file->col,
            .row = file->row,
            .base = 0,
            .exponent = 0,
          };
          file->i += 1;
          file->col += 1;
          return token;
        }
      }

      case '-' : {
        if ( l == '-' ) {
          token_t token = {
            .type = TOKEN_MINUS_MINUS,
            .id = "--",
            .col = file->col,
            .row = file->row,
            .base = 0,
            .exponent = 0,
          };
          file->i += 2;
          file->col += 2;
          return token;
        }

        if ( l == '=' ) {
          token_t token = {
            .type = TOKEN_MINUS_EQUALS,
            .id = "-=",
            .col = file->col,
            .row = file->row,
            .base = 0,
            .exponent = 0,
          };
          file->i += 2;
          file->col += 2;
          return token;
        }

        else {
          token_t token = {
            .type = TOKEN_MINUS,
            .id = "-",
            .col = file->col,
            .row = file->row,
            .base = 0,
            .exponent = 0,
          };
          file->i += 1;
          file->col += 1;
          return token;
        }
      }

      case '<' : {
        if ( l == '=' ) {
          token_t token = {
            .type = TOKEN_LESS_EQUALS,
            .id = "<=",
            .col = file->col,
            .row = file->row,
            .base = 0,
            .exponent = 0,
          };
          file->i += 2;
          file->col += 2;
          return token;
        }
        
        else {
          token_t token = {
            .type = TOKEN_LESS,
            .id = "<",
            .col = file->col,
            .row = file->row,
            .base = 0,
            .exponent = 0,
          };
          file->i += 1; 
          file->col += 1; 
          return token;
        }
      }

      case '>' : {
        if ( l == '=' ){
          token_t token = {
            .type = TOKEN_GREATER_EQUALS,
            .id = ">=",
            .col = file->col,
            .row = file->row,
            .base = 0,
            .exponent = 0,
          };
          file->i += 2;
          file->col += 2;
          return token;
        }

        else {
          token_t token = {
            .type = TOKEN_GREATER,
            .id = ">",
            .col = file->col,
            .row = file->row,
            .base = 0,
            .exponent = 0,
          };
          file->i += 1;
          file->col += 1;
          return token;
        }
      }

      case '(' : {
        token_t token = {
          .type = TOKEN_LPAREN,
          .id = "(",
          .col = file->col,
          .row = file->row,
          .base = 0,
          .exponent = 0,
        };
        file->i += 1;
        file->col += 1;
        return token;
      }

      case ')' : {
        token_t token = {
          .type = TOKEN_RPAREN,
          .id = ")",
          .col = file->col,
          .row = file->row,
          .base = 0,
          .exponent = 0,
        };
        file->i += 1;
        file->col += 1;
        return token;
      }

      case '[' : {
        token_t token = {
          .type = TOKEN_LBRACKET,
          .id = "[",
          .col = file->col,
          .row = file->row,
          .base = 0,
          .exponent = 0,
        };
        file->i += 1;
        file->col += 1;
        return token;
      }

      case ']' : {
        token_t token = {
          .type = TOKEN_RBRACKET,
          .id = "]",
          .col = file->col,
          .row = file->row,
          .base = 0,
          .exponent = 0,
        };
        file->i += 1;
        file->col += 1;
        return token;
      }

      case '{' : {
        token_t token = {
          .type = TOKEN_LBRACE,
          .id = "{",
          .col = file->col,
          .row = file->row,
          .base = 0,
          .exponent = 0,
        };
        file->i += 1;
        file->col += 1;
        return token;
      }

      case '}' : {
        token_t token = {
          .type = TOKEN_RBRACE,
          .id = "}",
          .col = file->col,
          .row = file->row,
          .base = 0,
          .exponent = 0,
        };
        file->i += 1;
        file->col += 1;
        return token;
      }

      case '.' : {
        token_t token = {
          .type = TOKEN_DOT,
          .id = ",",
          .col = file->col,
          .row = file->row,
          .base = 0,
          .exponent = 0,
        };
        file->i += 1;
        file->col += 1;
        return token;
      }

      case ',' : {
        token_t token = {
          .type = TOKEN_COMMA,
          .id = ",",
          .col = file->col,
          .row = file->row,
          .base = 0,
          .exponent = 0,
        };
        file->i += 1;
        file->col += 1;
        return token;
      }


      case ':' : {
        token_t token = {
          .type = TOKEN_COLON,
          .id = ":",
          .col = file->col,
          .row = file->row,
          .base = 0,
          .exponent = 0,
        };
        file->i += 1;
        file->col += 1;
        return token;
      }

      case ';' : {
        token_t token = {
          .type = TOKEN_SEMICOLON,
          .id = ";",
          .col = file->col,
          .row = file->row,
          .base = 0,
          .exponent = 0,
        };
        file->i += 1;
        file->col += 1;
        return token;
      }

      case '\'' : {
        token_t token = {
          .type = TOKEN_SINGLE_QUOTE,
          .id = "\'",
          .col = file->col,
          .row = file->row,
          .base = 0,
          .exponent = 0,
        };
        file->i += 1;
        file->col += 1;
        return token;
      }

      case '\"' : {
        token_t token = {
          .type = TOKEN_DOUBLE_QUOTE,
          .id = "\"",
          .col = file->col,
          .row = file->row,
          .base = 0,
          .exponent = 0,
        };
        file->i += 1;
        file->col += 1;
        return token;
      }

      default : {

        fprintf(stderr, "Unknown token.\n");
        exit(1);
      }

    }
  }

  token_t token = {
    .type = TOKEN_EOF,
    .id = "EOF",
    .col = file->col,
    .row = file->row,
    .base = 0,
    .exponent = 0,
  };
  return token;
}


// If the first character of the token is an alphabetical uppercase or owercase or an underline, then it is an id.
// At this point it does not matter if it is the name (of a variable, function etc) or a keyword. This will be
// handled later.
token_t eat_token_id(file_t *file) {
  token_t token = {
    .type = TOKEN_ID,
    .id = "",
    .col = file->col,
    .row = file->row,
    .base = 0,
    .exponent = 0
  };


  char c = file->src[file->i];
  int i = 0;
  
  while ( ( c >= 'a' && c <= 'z' ) || ( c >= 'A' && c <= 'Z' ) || ( c >= '0' && c <= '9' ) || c == '_' ) {
    token.id[i] = c;
    i += 1;
    file->i += 1;
    file->col += 1;
    c = file->src[file->i];
  }
  token.id[i] = '\0';

  return token;
}

token_t eat_token_number(file_t *file) {

  token_t token = {
    .type = TOKEN_NUMBER,
    .col = file->col,
    .row = file->row,
    .base = 0,
    .exponent = 0,
  };

  int first = file->i;
  char c = file->src[file->i];
  int i = 0; 
  while (c >= '0' && c <= '9') {

    token.id[i] = c;
    i += 1;

    file->i += 1;
    file->col += 1;
    c = file->src[file->i];
  }

  int pos = 0;
  for (int i = file->i -1; i >= first; i--) {
    
    char c = file->src[i];

    token.base += (int)(c - '0') * power(10, pos);
    pos ++;

  }
  return token;

}

int power(int base, int exp) {
  int result = 1;
  while (exp > 0) {
    result *= base;
    exp -= 1;
  }
  return result;
}

char *token_to_string(token_t *token) {

  switch (token->type) {
    
    case TOKEN_ID:              return "TOKEN_ID";
    case TOKEN_NUMBER:          return "TOKEN_NUMBER";
    case TOKEN_EQUALS:          return "TOKEN_EQUALS";
    case TOKEN_EQUALS_EQUALS:   return "TOKEN_EQUALS_EQUALS";
    case TOKEN_PLUS:            return "TOKEN_PLUS";
    case TOKEN_PLUS_EQUALS:     return "TOKEN_PLUS_EQUALS";
    case TOKEN_PLUS_PLUS:       return "TOKEN_PLUS_PLUS";
    case TOKEN_MINUS:           return "TOKEN_MINUS";
    case TOKEN_MINUS_EQUALS:    return "TOKEN_MINUS_EQUALS";
    case TOKEN_MINUS_MINUS:     return "TOKEN_MINUS_MINUS";
    case TOKEN_LESS:            return "TOKEN_LESS";
    case TOKEN_LESS_EQUALS:     return "TOKEN_LESS_EQUALS";
    case TOKEN_GREATER:         return "TOKEN_GREATER";
    case TOKEN_GREATER_EQUALS:  return "TOKEN_GREATER_EQUALS";
    case TOKEN_LPAREN:          return "TOKEN_LPAREN";
    case TOKEN_RPAREN:          return "TOKEN_RPAREN";
    case TOKEN_LBRACKET:        return "TOKEN_LBRACKET";
    case TOKEN_RBRACKET:        return "TOKEN_RBRACKET";
    case TOKEN_LBRACE:          return "TOKEN_LBRACE";
    case TOKEN_RBRACE:          return "TOKEN_RBRACE";
    case TOKEN_DOT:             return "TOKEN_DOT";
    case TOKEN_COMMA:           return "TOKEN_COMMA";
    case TOKEN_COLON:           return "TOKEN_COLON";
    case TOKEN_SEMICOLON:       return "TOKEN_SEMICOLON";
    case TOKEN_SINGLE_QUOTE:    return "TOKEN_SINGLE_QUOTE";
    case TOKEN_DOUBLE_QUOTE:    return "TOKEN_DOUBLE_QUOTE";
    case TOKEN_EOF:             return "TOKEN_EOF";
  }
  return "UNKNOWN";
} 
