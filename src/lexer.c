#include "include/lexer.h"

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
  while (c >= 'a' && c <= 'z') {
    if (c != word[i]) {
      return false;
    }
    i += 1;
    c = peek_char(file, i);
  }
  return true;
}

token_t eat_token(file_t *file) {

  char c;
  while ( (c = peek_char(file, 0)) != '\0' ) {

    if ( ( c >= 'a' && c <= 'z' ) || ( c >= 'A' && c <= 'Z' ) || c == '_' ) { // change to utf-8 later.
      switch (c) {
        case 'a' : {}
        case 'b' : {
          if (is_keyword(file, "break")) return make_token(file, TOKEN_BREAK, 5);
        }
        case 'c' : {
          if (is_keyword(file, "continue")) return make_token(file, TOKEN_CONTINUE, 8);
        }
        case 'd' : {}
        case 'e' : {
          if (is_keyword(file, "else")) return make_token(file, TOKEN_ELSE, 4);
          if (is_keyword(file, "enum")) return make_token(file, TOKEN_ENUM, 4);
        }
        case 'f' : {
        case 'g' : {}
        case 'h' : {}
        case 'i' : {
          if (is_keyword(file, "if")) return make_token(file, TOKEN_IF, 2);
        }
        case 'j' : {}
        case 'k' : {}
        case 'l' : {
          if (is_keyword(file, "loop")) return make_token(file, TOKEN_LOOP, 4);
        }
        case 'm' : {}
        case 'n' : {}
        case 'o' : {}
        case 'p' : {}
        case 'q' : {}
        case 'r' : {}
        case 's' : {
          if (is_keyword(file, "struct")) return make_token(file, TOKEN_STRUCT, 6);
        }
        case 't' : {
          if (is_keyword(file, "typedef")) return make_token(file, TOKEN_TYPEDEF, 7);
        }
        case 'u' : {
          if (is_keyword(file, "union")) return make_token(file, TOKEN_UNION, 5);
        }
        case 'v' : {}
        case 'w' : {
        case 'x' : {}
        case 'y' : {}
        case 'z' : {}
      }
    }

    if (c >= '0' && c <= '9') {
      return make_token_number( file );
    }

    switch ( c ) {

      case ' ' :
      case '\r' :
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

        return make_token(file, TOKEN_ERROR, 50);
      }

    }
  }

  return make_token(file, TOKEN_EOF, 1);
}


// If the first character of the token is an alphabetical uppercase or owercase or an underline, then it is an id.
// At this point it does not matter if it is the name (of a variable, function etc) or a keyword. This will be
// handled later.
token_t make_token_id(file_t *file) {
  token_t token = {
    .type = TOKEN_ID,
    .id = "",
    .col = file->col,
    .row = file->row,
    .coefficient = 0,
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

token_t make_token_number(file_t *file) {

}

void print_token(token_t *token) {

  char *token_type;

  switch (token->type) {
    
    case TOKEN_IDENTIFIER:              token_type = "TOKEN_ID"; break;
    case TOKEN_NUMBER:          token_type = "TOKEN_NUMBER"; break;
    case TOKEN_EQUALS:          token_type = "TOKEN_EQUALS"; break;
    case TOKEN_EQUALS_EQUALS:   token_type = "TOKEN_EQUALS_EQUALS"; break;
    case TOKEN_PLUS:            token_type = "TOKEN_PLUS"; break;
    case TOKEN_PLUS_EQUALS:     token_type = "TOKEN_PLUS_EQUALS"; break;
    case TOKEN_MINUS:           token_type = "TOKEN_MINUS"; break;
    case TOKEN_MINUS_EQUALS:    token_type = "TOKEN_MINUS_EQUALS"; break;
    case TOKEN_LESS:            token_type = "TOKEN_LESS"; break;
    case TOKEN_LESS_EQUALS:     token_type = "TOKEN_LESS_EQUALS"; break;
    case TOKEN_GREATER:         token_type = "TOKEN_GREATER"; break;
    case TOKEN_GREATER_EQUALS:  token_type = "TOKEN_GREATER_EQUALS"; break;
    case TOKEN_LPAREN:          token_type = "TOKEN_LPAREN"; break;
    case TOKEN_RPAREN:          token_type = "TOKEN_RPAREN"; break;
    case TOKEN_LBRACKET:        token_type = "TOKEN_LBRACKET"; break;
    case TOKEN_RBRACKET:        token_type = "TOKEN_RBRACKET"; break;
    case TOKEN_LBRACE:          token_type = "TOKEN_LBRACE"; break;
    case TOKEN_RBRACE:          token_type = "TOKEN_RBRACE"; break;
    case TOKEN_DOT:             token_type = "TOKEN_DOT"; break;
    case TOKEN_COMMA:           token_type = "TOKEN_COMMA"; break;
    case TOKEN_COLON:           token_type = "TOKEN_COLON"; break;
    case TOKEN_SEMICOLON:       token_type = "TOKEN_SEMICOLON"; break;
    case TOKEN_SINGLE_QUOTE:    token_type = "TOKEN_SINGLE_QUOTE"; break;
    case TOKEN_DOUBLE_QUOTE:    token_type = "TOKEN_DOUBLE_QUOTE"; break;
    case TOKEN_EOF:             token_type = "TOKEN_EOF"; break;
  }

  printf(
      "<ID: `%s`, TYPE: `%s`, ROW: `%d`, COL: `%d`, COEFFICIENT: `%d`, EXPONENT: `%d`>\n", 
      token, token_type, token->row, token->col, token->coefficient, token->exponent
      );

  
} 
