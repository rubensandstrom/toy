#include <stddef.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <stdbool.h>
#include <stdint.h>
#include "string.h"
#include "ast.h"
#include "parser.h"
#include "token.h"
#include "lexer.h"

#define MIN_CAPACITY (4*1024)
parser new_parser(lexer *l) {
	parser p = {
		.l = l,
		.token_index = 0,
	};
	token t;
	for (int i = 0; i < BUFFER_LENGTH; i++) {
		t = next_token(l);
		p.buffer[i] = t;
		if (t.type == END) break;
	}
	return p;
}

token peek_token(parser *p, uint32_t offset) {
	// TODO: bounds check.
	return p->buffer[ (p->token_index + offset) % 100 ];
}


token eat_token(parser *p) {
	token t = p->buffer[ p->token_index % BUFFER_LENGTH ];
	p->buffer[ p->token_index % BUFFER_LENGTH ] = next_token(p->l);
	p->token_index++;
	return t;
}
/**/
/*statement *parse_statement(parser *p) {*/
/*	switch (peek_token(p, 0).type) {*/
/*		case RETURN:*/
/*			return parse_return_statement(p);*/
/*		case ID:*/
/*			return parse_decl_statement(p);*/
/*		default: // TODO: Error*/
/*			return NULL;*/
/*	}*/
/*	return NULL;*/
/*}*/
/**/
/*return_statement *parse_return_statement(parser *p) { // TODO: Use arena allocator.*/
/*	return_statement *rs = (return_statement *)malloc(sizeof(return_statement));*/
/*	rs->value = parse_expression(p);*/
/*	return rs;*/
/*}*/
/**/
/*decl_statement *parse_decl_statement(parser *p) {*/
/*	return NULL;*/
/*}*/
/**/
/*program *parse_program(parser *p) {*/
/*	return NULL;*/
/*}*/
