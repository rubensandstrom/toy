#ifndef PARSER_H
#define PARSER_H

#include <stdint.h>
#include "string.h"
#include "token.h"
#include "lexer.h"
#include "ast.h"

#define BUFFER_LENGTH 100

typedef struct parser {
	lexer *l;
	token buffer[BUFFER_LENGTH];
	size_t token_index;
} parser;

parser new_parser(lexer *l);

statement *parse_statement(parser *p);
decl_statement *parse_decl_statement(parser *p);
return_statement *parse_return_statement(parser *p);
program *parse_program(parser *p);
expression *parse_expression(parser *p);

token peek_token(parser *p, uint32_t offset);
token eat_token(parser *p);

#endif
