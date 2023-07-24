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
    if (c >= '0' && c <= 9) {
      eat_token_number( file );
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
            .row = file->row
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
            .row = file->row
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
            .row = file->row
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
            .row = file->row
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
            .row = file->row
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
            .row = file->row
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
            .row = file->row
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
            .row = file->row
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
            .row = file->row
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
            .row = file->row
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
            .row = file->row 
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
            .row = file->row
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
          .row = file->row
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
          .row = file->row
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
          .row = file->row
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
          .row = file->row
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
          .row = file->row
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
          .row = file->row
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
          .row = file->row
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
          .row = file->row
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
          .row = file->row
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
          .row = file->row
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
    .row = file->row
  };
  return token;
}


// If the first character of the token is an alphabetical uppercase or owercase or an underline, then it is an id.
// At this point it does not matter if it is the name (of a variable, function etc) or a keyword. This will be
// handled later.
token_t eat_token_id(file_t *file) {
  token_t token;

  token.type = TOKEN_ID;
  token.col = file->col;
  token.row = file->row;

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

  char c = file->src[file->i];
  token_t token = {
    .type = TOKEN_NUMBER,
    .col = file->col,
    .row = file->row,
  };

  int exp10;
  int exp2;
  int i = 0;
  int j = 0;

  while((c >= '0' && c <= 9) || c == '_' || c == '.') {
    switch (c) {
      case '_' : {
        file->i += 1;
        file->col += 1;
        continue;
      }
      case '.' : {
      }
    }
  }

}
