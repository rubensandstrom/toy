#include <stddef.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <stdbool.h>
#include <stdint.h>
#include "darray.h"
#include "string.h"
#include "ast.h"
#include "arena.h"
#include "parser.h"
#include "token.h"
#include "lexer.h"

#define MIN_CAPACITY (4*1024)
parser new_parser(lexer *l, arena *a) {
	parser p = {
		.l = l,
		.a = a,
		.token_index = 0,
	};
	token t;
	for (int i = 0; i < BUFFER_LENGTH; i++) {
		t = next_token(l);
		p.buffer[i] = t;
		if (t.type == END) break; }
	return p;
}

token peek_token(parser *p, uint32_t offset) {
	// TODO: bounds check.
	return p->buffer[ (p->token_index + offset) % BUFFER_LENGTH ];
}


token eat_token(parser *p) {
	token t = p->buffer[ p->token_index % BUFFER_LENGTH ];
	p->buffer[ p->token_index % BUFFER_LENGTH ] = next_token(p->l);
	p->token_index++;
	return t;
}

bool match_token(parser *p, token_type tt) {
	token t = eat_token(p);
	if (t.type != tt) {
		sb_write_fmt(&p->errors, "Expected %s, got %s\t: %d,%d.\n", token_debug[tt], token_debug[t.type], t.row, t.col);
		return false;
	}
	return true;
}

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

return_statement *parse_return_statement(parser *p) { // TODO: Use arena allocator.
	token t;
	return_statement *rs = (return_statement *)arena_alloc(p->a, sizeof(return_statement));

	match_token(p, RETURN);
	rs->value = parse_expression(p);
	return rs;
}

decl_statement *parse_decl_statement(parser *p) {
	token t;
	decl_statement *ds = (decl_statement *)arena_alloc(p->a, sizeof(decl_statement));
	
	t = eat_token(p);
	if (t.type != ID) {
		sb_write_fmt(&p->errors, "Expected %s, got %s\t: %d,%d\n", token_debug[ID], token_debug[t.type], t.row, t.col);
	}
	ds->name = t;
	t = eat_token(p);
	if (t.type != ID) {
		sb_write_fmt(&p->errors, "Expected %s, got %s\t: %d,%d\n", token_debug[ID], token_debug[t.type], t.row, t.col);
	}
	ds->type = t;

	if ( peek_token(p, 1).type == ASSIGN ) {
		p->token_index++;
		ds->value = parse_expression(p);
	} else {
		ds->value = NULL;
	}
	return ds;
	return NULL;
}

program *parse_program(parser *p) {
	statement *s;
	program prg;
	prg.s = da_init();
	while ((s = parse_statement(p)) != NULL) {
		*(statement *)da_push(&prg.s, sizeof(statement)) = *s;
	}

	return NULL;
}
