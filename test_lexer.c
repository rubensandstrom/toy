#include <stdbool.h>
#include <stdint.h>
#include <assert.h>
#include "string.h"
#include "token.h"
#include "lexer.h"
#include "arena.h"
#include "parser.h"

int main() {

	string_builder sb = sb_init();


	string input = STRING(
		"aaa (      \nb,c u32x4424 f32=0)error u32=NOFILE{}a<<<=5<= >=return for else ++"
	);
	lexer l = new_lexer(input);
	arena a = arena_init(4*1024);
	parser p = new_parser(&l, &a);

	string_builder output = sb_init();

	token t;

	/*t = eat_token(&p);*/
	/*sb_write_fmt(&output, "type: %s\tlexeme: %s\t: %d,%d\n", token_debug[t.type], t.lexeme, t.row, t.col);*/
	/*t = eat_token(&p);*/
	/*sb_write_fmt(&output, "type: %s\tlexeme: %s\t: %d,%d\n", token_debug[t.type], t.lexeme, t.row, t.col);*/
	/*t = eat_token(&p);*/
	/*sb_write_fmt(&output, "type: %s\tlexeme: %s\t: %d,%d\n", token_debug[t.type], t.lexeme, t.row, t.col);*/
	/*t = eat_token(&p);*/
	/*sb_write_fmt(&output, "type: %s\tlexeme: %s\t: %d,%d\n", token_debug[t.type], t.lexeme, t.row, t.col);*/

	assert(eat_token(&p).type == ID);
	assert(eat_token(&p).type == LPAREN);
	assert(eat_token(&p).type == NEWLINE);
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



	
	print(sb_string(&output));
	return 0;
	
}
