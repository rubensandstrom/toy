#include "include/lexer.h"
#include <stdio.h>
#include <sys/types.h>

token_t make_token(file_t *file, token_type_t type, int length) {

  token_t token = {
    .type = type,
    .col = file->col,
    .row = file->row,
    .lexme = {
      .start = file->index,
      .stop = file->index + length -1
    }
  };
  file->index += length;
  file->col += length;
  return token;
}

token_t make_token_number(file_t *file) {

  int i = 0;
  if ( peek_char(file, 0) == '0' && peek_char(file, 1) == 'b' ) {
    i = 2;
    char c = peek_char(file, i);
    while ( c == '0' || c == '1' || c == '_') {
      i += 1;
      c = peek_char(file, i);
    }
    return make_token(file, TOKEN_NUMBER, i);
  }

  if ( peek_char(file, 0) == '0' && peek_char(file, 1) == 'o' ) {
    i = 2;
    char c = peek_char(file, i);
    while ( ( c >= '0' && c <= '7' ) || c == '_' ) {
      i += 1;
      c = peek_char(file, i);
    }
    return make_token(file, TOKEN_NUMBER, i);
  }

  if ( peek_char(file, 0) == '0' && peek_char(file, 1) == 'x' ) {
    i = 2;
    char c = peek_char(file, i);
    while ( ( c >= '0' && c <= '9' ) || ( c >= 'a' && c <= 'f' ) || ( c >= 'A' && c <= 'F' ) || c == '_' ) {
      i += 1;
      c = peek_char(file, i);
    }
    return make_token(file, TOKEN_NUMBER, i);
  }

  int dots = 0;
  char c = peek_char(file, i);
  while ( ( c >= '0' && c <= '9' ) || c == '.' || c == '_' ) {
    if ( c == '.' ) {
      dots += 1;
    }
    i += 1;
    c = peek_char(file, i);
  }
  if ( dots > 1 ) {
    return make_token(file, TOKEN_ERROR, i);
  }
  return make_token(file, TOKEN_NUMBER, i);
}

bool is_keyword(file_t *file, char *word) {
  char c = peek_char(file, 0);
  int i = 0;
  while ( word[i] != '\0' ) {
    if (c != word[i]) {
      return false;
    }
    i += 1;
    c = peek_char(file, i);
  }
  if ((c >= 'a' && c <= 'z' ) || ( c >= 'A' && c <= 'Z' ) || c == '_') return false;
  return true;
}

token_t eat_token(file_t *file) {

  char c;
  while ( (c = peek_char(file, 0)) != '\0' ) {

    if ( ( c >= 'a' && c <= 'z' ) || ( c >= 'A' && c <= 'Z' ) || c == '_' ) { // change to utf-8 later.
      switch (c) {
        case 'b' : {
          if (is_keyword(file, "break")) return make_token(file, TOKEN_BREAK, 5);
          break;
        }
        case 'c' : {
          if (is_keyword(file, "continue")) return make_token(file, TOKEN_CONTINUE, 8);
          break;
        }
        case 'e' : {
          if (is_keyword(file, "else")) return make_token(file, TOKEN_ELSE, 4); 
          if (is_keyword(file, "enum")) return make_token(file, TOKEN_ENUM, 4); 
          break;
        }
        case 'i' : {
          if (is_keyword(file, "if")) return make_token(file, TOKEN_IF, 2);
          break;
        }
        case 'l' : {
          if (is_keyword(file, "loop")) return make_token(file, TOKEN_LOOP, 4);
          break;
        }
        case 's' : {
          if (is_keyword(file, "struct")) return make_token(file, TOKEN_STRUCT, 6);
          break;
        }
        case 't' : {
          if (is_keyword(file, "typedef")) return make_token(file, TOKEN_TYPEDEF, 7);
          break;
        }
        case 'u' : {
          if (is_keyword(file, "union")) return make_token(file, TOKEN_UNION, 5);
          break;
        }
      }
      int i = 0;
      while ((c >= 'a' && c <= 'z' ) || ( c >= 'A' && c <= 'Z' ) || ( c >= '0' && c <= '9' ) || c == '_') {
        i += 1;
        c = peek_char(file, i);
      }
      return make_token(file, TOKEN_IDENTIFIER, i);
    }

    if (c >= '0' && c <= '9') {
      return make_token_number( file );
    }

    switch ( c ) {

      case ' ' :
        file->index += 1;
        file->col += 1;
        continue;
      case '\r' :
        file->index += 1;
        file->col += 1;
        continue;
      case '\t' : {
        file->index += 1;
        file->col += 1;
        continue;
      }

      case '\n' : {
        file->index += 1;
        file->col = 0;
        file->row += 1;
        continue;
      }

      case '=' : {

        if ( peek_char(file, 1) == '>' ) {
          return make_token(file, TOKEN_FAT_ARROW, 2);
        }

        if ( peek_char(file, 1) == '=' ) {
          return make_token(file, TOKEN_EQUALS_EQUALS, 2);
        }

        else {
          return make_token(file, TOKEN_EQUALS, 1);
        }
      }

      case '+' : {
        if ( peek_char(file, 1) == '=' ) {
          return make_token(file, TOKEN_PLUS_EQUALS, 2);
        }
        
        else {
          return make_token(file, TOKEN_PLUS, 1);
        }
      }

      case '-' : {
        if ( peek_char(file, 1) == '=' ) {
          return make_token(file, TOKEN_MINUS_EQUALS, 2);
        }
        
        else {
          return make_token(file, TOKEN_MINUS, 1);
        }
      }

      case '*' : {
        if ( peek_char(file, 1) == '=' ) {
          return make_token(file, TOKEN_STAR_EQUALS, 2);
        }

        else {
          return make_token(file, TOKEN_STAR, 1);
        }
      }

      case '/' : {
        /* if ( peek_char(file, 1) == '/') { */
        /*   return make_comment(file, TOKEN_COMMENT, "\n"); */
        /* } */
        /*  */
        /* if ( peek_char(file, 1) == '*' ) { */
        /*   return make_comment(file, TOKEN_COMMENT, ""); */
        /* } */

        if ( peek_char(file, 1) == '=' ) {
          return make_token(file, TOKEN_SLASH_EQUALS, 2);
        }

        else {
          return make_token(file, TOKEN_SLASH, 1);
        }
      }

       

      case '<' : {
        if (peek_char(file, 1) == '<') {
          if (peek_char(file, 2) == '=') {
            return make_token(file, TOKEN_LSHIFT_EQUALS, 3);
          }
          return make_token(file, TOKEN_LSHIFT, 2);
        }
        
        if ( peek_char(file, 1) == '=' ) {
          return make_token(file, TOKEN_LESS_EQUALS, 2);
        }

        else {
          return make_token(file, TOKEN_LESS, 1);
        }
      }

      case '>' : {
        if ( peek_char(file, 1) == '>' ) {
          if ( peek_char(file, 2) == '=' ) {
            return make_token(file, TOKEN_RSHIFT_EQUALS, 3);
          }
          return make_token(file, TOKEN_RSHIFT, 2);
        }

        if ( peek_char(file, 1) == '=' ){
          return make_token(file, TOKEN_GREATER_EQUALS, 2);
        }

        else {
          return make_token(file, TOKEN_GREATER, 1);
        }
      }

      case '&' : {
        if ( peek_char(file, 1) == '&' ) {
          return make_token(file, TOKEN_AND_AND, 2);
        }

        if ( peek_char(file, 1) == '=' ) {
          return make_token(file, TOKEN_AND_EQUALS, 2);
        }

        else {
          return make_token(file, TOKEN_AND, 1);
        }
      }

      case '|' : {
        if ( peek_char(file, 1) == '|' ) {
          return make_token(file, TOKEN_OR_OR, 2);
        }

        if ( peek_char(file, 1) == '=' ) {
          return make_token(file, TOKEN_OR_EQUALS, 2);
        }

        else {
          return make_token(file, TOKEN_OR, 1);
        }
      }

      case '^' : {
        if ( peek_char(file, 1) == '^' ) {
          return make_token(file, TOKEN_XOR_XOR, 2);
        }

        if ( peek_char(file, 1) == '=' ) {
          return make_token(file, TOKEN_XOR_EQUALS, 2);
        }

        else {
          return make_token(file, TOKEN_XOR, 1);
        }
      }

      case '~' : {
        if ( peek_char(file, 1) == '&' ) {
          if ( peek_char(file, 2) == '&' ) {
            return make_token(file, TOKEN_TILDE_AND_AND, 3);
          }

          if ( peek_char(file, 2) == '=' ) {
            return make_token(file, TOKEN_TILDE_AND_EQUALS, 3);
          }

          else {
            return make_token(file, TOKEN_TILDE_AND, 2);
          }
        }      

        if ( peek_char(file, 1) == '|' ) {
          if ( peek_char(file, 2) == '|' ) {
            return make_token(file, TOKEN_TILDE_OR_OR, 3);
          }

          if ( peek_char(file, 2) == '=' ) {
            return make_token(file, TOKEN_TILDE_OR_EQUALS, 3);
          }

          else {
            return make_token(file, TOKEN_TILDE_OR, 2);
          }
        }

        if ( peek_char(file, 1) == '^' ) {
          if ( peek_char(file, 2) == '^' ) {
            return make_token(file, TOKEN_TILDE_XOR_XOR, 3);
          }

          if ( peek_char(file, 2) == '=' ) {
            return make_token(file, TOKEN_TILDE_XOR_EQUALS, 3);
          }

          else return make_token(file, TOKEN_TILDE_XOR, 2);
        }

        if ( peek_char(file, 1) == '~' ) {
          return make_token(file, TOKEN_TILDE_TILDE, 2);
        }

        else {
          return make_token(file, TOKEN_TILDE, 1);
        }
      }

      case '(' : {
        return make_token(file, TOKEN_LPAREN, 1);
      }

      case ')' : {
        return make_token(file, TOKEN_RPAREN, 1);
      }

      case '[' : {
        return make_token(file, TOKEN_LBRACKET, 1);
      }

      case ']' : {
        return make_token(file, TOKEN_RBRACKET, 1);
      }

      case '{' : {
        return make_token(file, TOKEN_LBRACE, 1);
      }

      case '}' : {
        return make_token(file, TOKEN_RBRACE, 1);
      }

      case '.' : {
        return make_token(file, TOKEN_DOT, 1);
      }

      case ',' : {
        return make_token(file, TOKEN_COMMA, 1);
      }

      case ':' : {
        return make_token(file, TOKEN_COLON, 1);
      }

      case ';' : {
        return make_token(file, TOKEN_SEMICOLON, 1);
      }

      case '?' : {
        return make_token(file, TOKEN_QMARK, 1);
      }

      case '!' : {
        return make_token(file, TOKEN_BANG, 1);
      }

      case '@' : {
        return make_token(file, TOKEN_AT, 1);
      }

      case '#' : {
        return make_token(file, TOKEN_HASH, 1);
      }

      /* case '\'' : { */
      /*   return make_char_token(file, TOKEN_CHARACTER); */
      /* } */
      /*  */
      /* case '\"' : { */
      /*   return make_str_token(file, TOKEN_STRING); */
      /* } */

      default : {

        return make_token(file, TOKEN_ERROR, 1);
      }

    }
  }

  return make_token(file, TOKEN_EOF, 1);
}

void print_token(file_t *file, token_t *token) {


  printf (
    "<ID: `%d`, TYPE: `%s`, LEXME: `", 
    token->type, get_token_type(token->type)
  );
  for (int i = token->lexme.start; i <= token->lexme.stop; i++) {
    printf("%c", file->src[i]);
  }
  printf("`, ROW: %d, COL: %d\n", token->row, token->col);

} 

char *get_token_type(token_type_t type) {
    // Literals.
    switch( type ) {
      case TOKEN_IDENTIFIER : return "TOKEN_IDENTIFIER";
      case TOKEN_CHARACTER : return "TOKEN_CHARACTER";
      case TOKEN_STRING : return "TOKEN_STRING";
      case TOKEN_NUMBER : return "TOKEN_NUMBER";

      // ARITHMETIC OPERATORj 
      case TOKEN_EQUALS : return "TOKEN_EQUALS";
      case TOKEN_PLUS : return "TOKEN_PLUS";
      case TOKEN_MINUS : return "TOKEN_MINUS";
      case TOKEN_STAR : return "TOKEN_STAR";
      case TOKEN_SLASH : return "TOKEN_SLASH";
      case TOKEN_MODULO : return "TOKEN_MODULO";
      
      // BITWISE OPERATORS
      case TOKEN_AND : return "TOKEN_AND";
      case TOKEN_OR : return "TOKEN_OR";
      case TOKEN_XOR : return "TOKEN_XOR";
      case TOKEN_TILDE : return "TOKEN_TILDE";
      case TOKEN_TILDE_AND : return "TOKEN_TILDE_AND";
      case TOKEN_TILDE_OR : return "TOKEN_TILDE_OR";
      case TOKEN_TILDE_XOR : return "TOKEN_TILDE_XOR";

      // LOGICAL OPERATORS
      case TOKEN_AND_AND : return "TOKEN_AND_AND";
      case TOKEN_OR_OR : return "TOKEN_OR_OR";
      case TOKEN_XOR_XOR : return "TOKEN_XOR_XOR";
      case TOKEN_TILDE_TILDE : return "TOKEN_TILDE_TILDE";
      case TOKEN_TILDE_AND_AND : return "TOKEN_TILDE_AND_AND";
      case TOKEN_TILDE_OR_OR : return "TOKEN_TILDE_OR_OR";
      case TOKEN_TILDE_XOR_XOR : return "TOKEN_TILDE_XOR_XOR";

      // ASIGNMENTS
      case TOKEN_PLUS_EQUALS : return "TOKEN_PLUS_EQUALS";
      case TOKEN_MINUS_EQUALS : return "TOKEN_MINUS_EQUALS";
      case TOKEN_STAR_EQUALS : return "TOKEN_STAR_EQUALS";
      case TOKEN_SLASH_EQUALS : return "TOKEN_SLASH_EQUALS";
      case TOKEN_MODULO_EQUALS : return "TOKEN_MODULO_EQUALS";
      case TOKEN_AND_EQUALS : return "TOKEN_AND_EQUALS";
      case TOKEN_OR_EQUALS : return "TOKEN_OR_EQUALS";
      case TOKEN_XOR_EQUALS : return "TOKEN_XOR_EQUALS";
      case TOKEN_TILDE_AND_EQUALS : return "TOKEN_TILDE_AND_EQUALS";
      case TOKEN_TILDE_OR_EQUALS : return "TOKEN_TILDE_OR_EQUALS";
      case TOKEN_TILDE_XOR_EQUALS : return "TOKEN_TILDE_XOR_EQUALS";

      // COPMPARISONS
      case TOKEN_EQUALS_EQUALS : return "TOKEN_EQUALS_EQUALS";
      case TOKEN_LESS : return "TOKEN_LESS";
      case TOKEN_LESS_EQUALS : return "TOKEN_LESS_EQUALS";
      case TOKEN_GREATER : return "TOKEN_GREATER";
      case TOKEN_GREATER_EQUALS : return "TOKEN_GREATER_EQUALS";
      case TOKEN_TILDE_EQUALS : return "TOKEN_TILDE_EQUALS";

      case TOKEN_LPAREN : return "TOKEN_LPAREN";
      case TOKEN_RPAREN : return "TOKEN_RPAREN";
      case TOKEN_LBRACKET : return "TOKEN_LBRACKET";
      case TOKEN_RBRACKET : return "TOKEN_RBRACKET";
      case TOKEN_LBRACE : return "TOKEN_LBRACE";
      case TOKEN_RBRACE : return "TOKEN_RBRACE";

      case TOKEN_DOT : return "TOKEN_DOT";
      case TOKEN_COMMA : return "TOKEN_COMMA";
      case TOKEN_COLON : return "TOKEN_COLON";
      case TOKEN_SEMICOLON : return "TOKEN_SEMICOLON";

      case TOKEN_FAT_ARROW : return "TOKEN_FAT_ARROW";
      case TOKEN_LSHIFT_EQUALS : return "TOKEN_LSHIFT_EQUALS";
      case TOKEN_LSHIFT : return "TOKEN_LSHIFT";
      case TOKEN_RSHIFT_EQUALS : return "TOKEN_RSHIFT_EQUALS";
      case TOKEN_RSHIFT : return "TOKEN_RSHIFT";

      case TOKEN_BANG :  return "TOKEN_BANG";
      case TOKEN_ROOF : return "TOKEN_ROOF";
      case TOKEN_QMARK : return "TOKEN_QMARK";
      case TOKEN_AT : return "TOKEN_AT";
      case TOKEN_HASH : return "TOKEN_HASH";


      case TOKEN_ENUM : return "TOKEN_ENUM";
      case TOKEN_STRUCT : return "TOKEN_STRUCT";
      case TOKEN_UNION : return "TOKEN_UNION";

      // KEYWORDS
      case TOKEN_FOR : return "TOKEN_FOR";
      case TOKEN_WHILE : return "TOKEN_WHILE";
      case TOKEN_LOOP : return "TOKEN_LOOP";
      case TOKEN_BREAK : return "TOKEN_BREAK";
      case TOKEN_CONTINUE : return "TOKEN_CONTINUE";
      case TOKEN_IF : return "TOKEN_IF";
      case TOKEN_ELSE : return "TOKEN_ELSE";
      case TOKEN_TYPEDEF : return "TOKEN_TYPEDEF";


      case TOKEN_ERROR : return "TOKEN_ERROR";
      case TOKEN_EOF : return "TOKEN_EOF";
    }
    return "UNKNOWN_ERROR";
}
