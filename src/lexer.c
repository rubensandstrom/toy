#include "include/lexer.h"
#include <stdio.h>

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
        case 'a' : break;
        case 'b' : {
          if (is_keyword(file, "break")) return make_token(file, TOKEN_BREAK, 5);
          break;
        }
        case 'c' : {
          if (is_keyword(file, "continue")) return make_token(file, TOKEN_CONTINUE, 8);
          break;
        }
        case 'd' : break;
        case 'e' : {
          if (is_keyword(file, "else")) return make_token(file, TOKEN_ELSE, 4); 
          if (is_keyword(file, "enum")) return make_token(file, TOKEN_ENUM, 4); 
          break;
        }
        case 'f' : break;
        case 'g' : break;
        case 'h' : break;
        case 'i' : {
          if (is_keyword(file, "if")) return make_token(file, TOKEN_IF, 2);
          break;
        }
        case 'j' : break;
        case 'k' : break;
        case 'l' : {
          if (is_keyword(file, "loop")) return make_token(file, TOKEN_LOOP, 4);
          break;
        }
        case 'm' : break;
        case 'n' : break;
        case 'o' : break;
        case 'p' : break;
        case 'q' : break;
        case 'r' : break;
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
        case 'v' : break;
        case 'w' : break;
        case 'x' : break;
        case 'y' : break;
        case 'z' : break;
      }
      int i = 0;
      while ((c >= 'a' && c <= 'z' ) || ( c >= 'A' && c <= 'Z' ) || ( c >= '0' && c <= '9' ) || c == '_') {
        i += 1;
        c = peek_char(file, i);
      }
      return make_token(file, TOKEN_IDENTIFIER, i);
    }

    /* if (c >= '0' && c <= '9') { */
    /*   return make_token_number( file ); */
    /* } */

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
        
        if ( peek_char(file, 1) == '>') {
          return make_token(file, TOKEN_RARROW, 2);
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
        if ( peek_char(file, 1) == '=' ) {
          return make_token(file, TOKEN_LESS_EQUALS, 2);
        }
        
        if (peek_char(file, 1) == '-') {
          return make_token(file, TOKEN_LARROW, 2);
        }

        else {
          return make_token(file, TOKEN_LESS, 1);
        }
      }

      case '>' : {
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

  char *token_type;

  switch (token->type) {
    

    // Literals.
    case TOKEN_IDENTIFIER : token_type = "TOKEN_IDENTIFIER"; break;
    case TOKEN_CHARACTER : token_type = "TOKEN_CHARACTER"; break;
    case TOKEN_STRING : token_type = "TOKEN_STRING"; break;
    case TOKEN_NUMBER : token_type = "TOKEN_NUMBER"; break;

    // ARITHMETIC OPERATORj 
    case TOKEN_EQUALS : token_type = "TOKEN_EQUALS"; break;
    case TOKEN_PLUS : token_type = "TOKEN_PLUS"; break;
    case TOKEN_MINUS : token_type = "TOKEN_MINUS"; break; case TOKEN_STAR : token_type = "TOKEN_STAR"; break; case TOKEN_SLASH : token_type = "TOKEN_SLASH"; break;
    case TOKEN_MODULO : token_type = "TOKEN_MODULO"; break;
    
    // BITWISE OPERATORS
    case TOKEN_AND : token_type = "TOKEN_AND"; break;
    case TOKEN_OR : token_type = "TOKEN_OR"; break;
    case TOKEN_XOR : token_type = "TOKEN_XOR"; break;
    case TOKEN_TILDE : token_type = "TOKEN_TILDE"; break;
    case TOKEN_TILDE_AND : token_type = "TOKEN_TILDE_AND"; break;
    case TOKEN_TILDE_OR : token_type = "TOKEN_TILDE_OR"; break;
    case TOKEN_TILDE_XOR : token_type = "TOKEN_TILDE_XOR"; break;

    // LOGICAL OPERATORS
    case TOKEN_AND_AND : token_type = "TOKEN_AND_AND"; break;
    case TOKEN_OR_OR : token_type = "TOKEN_OR_OR"; break;
    case TOKEN_XOR_XOR : token_type = "TOKEN_XOR_XOR"; break;
    case TOKEN_TILDE_TILDE : token_type = "TOKEN_TILDE_TILDE"; break;
    case TOKEN_TILDE_AND_AND : token_type = "TOKEN_TILDE_AND_AND"; break;
    case TOKEN_TILDE_OR_OR : token_type = "TOKEN_TILDE_OR_OR"; break;
    case TOKEN_TILDE_XOR_XOR : token_type = "TOKEN_TILDE_XOR_XOR"; break;

    // ASIGNMENTS
    case TOKEN_PLUS_EQUALS : token_type = "TOKEN_PLUS_EQUALS"; break;
    case TOKEN_MINUS_EQUALS : token_type = "TOKEN_MINUS_EQUALS"; break;
    case TOKEN_STAR_EQUALS : token_type = "TOKEN_STAR_EQUALS"; break;
    case TOKEN_SLASH_EQUALS : token_type = "TOKEN_SLASH_EQUALS"; break;
    case TOKEN_MODULO_EQUALS : token_type = "TOKEN_MODULO_EQUALS"; break;
    case TOKEN_AND_EQUALS : token_type = "TOKEN_AND_EQUALS"; break;
    case TOKEN_OR_EQUALS : token_type = "TOKEN_OR_EQUALS"; break;
    case TOKEN_XOR_EQUALS : token_type = "TOKEN_XOR_EQUALS"; break;
    case TOKEN_TILDE_AND_EQUALS : token_type = "TOKEN_TILDE_AND_EQUALS"; break;
    case TOKEN_TILDE_OR_EQUALS : token_type = "TOKEN_TILDE_OR_EQUALS"; break;
    case TOKEN_TILDE_XOR_EQUALS : token_type = "TOKEN_TILDE_XOR_EQUALS"; break;

    // COPMPARISONS
    case TOKEN_EQUALS_EQUALS : token_type = "TOKEN_EQUALS_EQUALS"; break;
    case TOKEN_LESS : token_type = "TOKEN_LESS"; break;
    case TOKEN_LESS_EQUALS : token_type = "TOKEN_LESS_EQUALS"; break;
    case TOKEN_GREATER : token_type = "TOKEN_GREATER"; break;
    case TOKEN_GREATER_EQUALS : token_type = "TOKEN_GREATER_EQUALS"; break;
    case TOKEN_TILDE_EQUALS : token_type = "TOKEN_TILDE_EQUALS"; break;

    case TOKEN_LPAREN : token_type = "TOKEN_LPAREN"; break;
    case TOKEN_RPAREN : token_type = "TOKEN_RPAREN"; break;
    case TOKEN_LBRACKET : token_type = "TOKEN_LBRACKET"; break;
    case TOKEN_RBRACKET : token_type = "TOKEN_RBRACKET"; break;
    case TOKEN_LBRACE : token_type = "TOKEN_LBRACE"; break;
    case TOKEN_RBRACE : token_type = "TOKEN_RBRACE"; break;

    case TOKEN_DOT : token_type = "TOKEN_DOT"; break;
    case TOKEN_COMMA : token_type = "TOKEN_COMMA"; break;
    case TOKEN_COLON : token_type = "TOKEN_COLON"; break;
    case TOKEN_SEMICOLON : token_type = "TOKEN_SEMICOLON"; break;

    case TOKEN_FAT_ARROW : token_type = "TOKEN_FAT_ARROW"; break;
    case TOKEN_LARROW : token_type = "TOKEN_LARROW"; break;
    case TOKEN_RARROW : token_type = "TOKEN_RARROW"; break;

    case TOKEN_BANG :  token_type = "TOKEN_BANG"; break;
    case TOKEN_ROOF : token_type = "TOKEN_ROOF"; break;
    case TOKEN_QMARK : token_type = "TOKEN_QMARK"; break;
    case TOKEN_AT : token_type = "TOKEN_AT"; break;
    case TOKEN_HASH : token_type = "TOKEN_HASH"; break;


    case TOKEN_ENUM : token_type = "TOKEN_ENUM"; break;
    case TOKEN_STRUCT : token_type = "TOKEN_STRUCT"; break;
    case TOKEN_UNION : token_type = "TOKEN_UNION"; break;

    // KEYWORDS
    case TOKEN_FOR : token_type = "TOKEN_FOR"; break;
    case TOKEN_WHILE : token_type = "TOKEN_WHILE"; break;
    case TOKEN_LOOP : token_type = "TOKEN_LOOP"; break;
    case TOKEN_BREAK : token_type = "TOKEN_BREAK"; break;
    case TOKEN_CONTINUE : token_type = "TOKEN_CONTINUE"; break;
    case TOKEN_IF : token_type = "TOKEN_IF"; break;
    case TOKEN_ELSE : token_type = "TOKEN_ELSE"; break;
    case TOKEN_TYPEDEF : token_type = "TOKEN_TYPEDEF"; break;


    case TOKEN_ERROR : token_type = "TOKEN_ERROR"; break;
    case TOKEN_EOF : token_type = "TOKEN_EOF"; break;
  }

  printf (
    "<ID: `%d`, TYPE: `%s`, LEXME: ", 
    token->type, token_type
  );
  for (int i = token->lexme.start; i <= token->lexme.stop; i++) {
    printf("%c", file->src[i]);
  }
  printf(", ROW: %d, COL: %d\n", token->row, token->col);

} 
