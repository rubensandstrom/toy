#ifndef LEXER_H
#define LEXER_H

typedef struct lexer {
	string input;
	uint32_t input_index;
	uint32_t row;
	uint32_t col;
} lexer;

lexer new_lexer(string input);
char peek_char(lexer *l, uint32_t offset);

token new_token(lexer *l, token_type t, uint32_t length);
token next_token(lexer *l);
bool is_number(char c);
bool is_alpha(char c);

#define RETURN_IF_KEY(CP, I) \
if (string_eq(&(string){CP, sizeof(CP)}, &(string){l->input.data + l->input_index, I})) {	\
	return new_token(l, FOR, sizeof(CP));													\
}																							\

bool _try_keyword(lexer *l, const char *keyword, int length);
#define try_keyword(L, CP) _try_keyword(L, CP, sizeof(CP))

bool is_uint(string *s);
#endif
