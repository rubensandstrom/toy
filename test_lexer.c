#include <stdbool.h>
#include <stdint.h>
#include <assert.h>
#include "string.h"
#include "token.h"
#include "lexer.h"
#include "parser.h"

int main() {

	string_builder sb = sb_init();


	string input = STRING(
		"a (      b,c u32x4424 f32=0)error u32=NOFILE{}a<<<=5<= >=return for else ++"
	);
	lexer l = new_lexer(input);
	parser p = new_parser(&l);

	assert(eat_token(&p).type == ID);
	assert(eat_token(&p).type == LPAREN);
	assert(eat_token(&p).type == ID);
	assert(eat_token(&p).type == COMMA);
	assert(eat_token(&p).type == ID);
	assert(eat_token(&p).type == UINTVEC);
	assert(eat_token(&p).type == FLOAT);
	assert(eat_token(&p).type == ASSIGN);
	assert(eat_token(&p).type == NUMBER);
	assert(eat_token(&p).type == RPAREN);
	assert(eat_token(&p).type == ID);
	assert(eat_token(&p).type == UINT);
	assert(eat_token(&p).type == ASSIGN);
	assert(eat_token(&p).type == ID);
	assert(eat_token(&p).type == LBRACE);
	assert(eat_token(&p).type == RBRACE);
	assert(eat_token(&p).type == ID);
	assert(eat_token(&p).type == LROTEQ);
	assert(eat_token(&p).type == NUMBER);
	assert(eat_token(&p).type == LTEQ);
	assert(eat_token(&p).type == GTEQ);
	assert(eat_token(&p).type == RETURN);
	assert(eat_token(&p).type == FOR);
	assert(eat_token(&p).type == ELSE);
	assert(eat_token(&p).type == INC);

	return 0;
	
}
