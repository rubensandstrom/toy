#include <stdint.h>
#include <stdbool.h>
#include "string.h"
#include "token.h"
#include "lexer.h"

// TODO: 
// - Clean up some hard to read parts.
// - More extensive testing.
// - Constants and private.

lexer new_lexer(string input) {
	return (lexer){
		.input = input,
		.input_index = 0,
		.row = 0,
		.col = 0
	};
}

token next_token(lexer *l) {
	while (peek_char(l, 0) == ' ' || peek_char(l, 0) == '\n' || peek_char(l, 0) == '\r') l->input_index++;
	while (l->input_index < l->input.length) {

		char c = peek_char(l, 0);

		if (is_number(c)) {
			// TODO: Hex, oct, bin, float and scientific notation numbers
			int i = 0;
			while (is_number(peek_char(l, i))) i++;
			return new_token(l, NUMBER, i);
		} 

		if (c == 'u') {
			int i = 1;
			if (is_number(peek_char(l, i))) {
				while (is_number(peek_char(l, i))) i++;
				if (peek_char(l, i) == 'x') {
					i++;
					if (is_number(peek_char(l, i))) {
						while (is_number(peek_char(l, i))) i++;
						return new_token(l, UINTVEC, i);
					}
				}
				return new_token(l, UINT, i);
			}
		}

		if (c == 'i') {
			int i = 1;
			if (is_number(peek_char(l, i))) {
				while (is_number(peek_char(l, i))) i++;
				if (peek_char(l, i) == 'x') {
					i++;
					if (is_number(peek_char(l, i)))  {
						while (is_number(peek_char(l, i))) i++;
						return new_token(l, INTVEC, i);
					}
				}
				return new_token(l, INT, i);
			}
		}

		if (c == 'f') {
			int i = 1;
			if (is_number(peek_char(l, i))) {
				while (is_number(peek_char(l, i))) i++;
				if (peek_char(l, i) == 'x') {
					i++;
					if (is_number(peek_char(l, i))) {
						while (is_number(peek_char(l, i))) i++;
						return new_token(l, FLOATVEC, i);
					}
				}
				return new_token(l, FLOAT, i);
			}
		}

		if (c == 'b') {
			int i = 1;
			if (is_number(peek_char(l, i))) {
				while (is_number(peek_char(l, i))) i++;
				return new_token(l, BITS, i);
			}
		}

		if (c == '_' && !is_alpha(c)) return new_token(l, VOID, 1);

		if (c == '_' || is_alpha(c)) {
			// TODO: Private if starts with _, Constant if all uppercase.
			int i = 0;
			while (is_alpha(peek_char(l, i))) i++;
			string s = {l->input.data + l->input_index, i};
			
			switch(c) {
				case 'b': 
					if (string_eq(&s, &STRING("break"))) return new_token(l, BREAK, 5);
				case 'c':
					if (string_eq(&s, &STRING("continue"))) return new_token(l, CONTINUE, 8);
				case 'e':
					if (string_eq(&s, &STRING("else"))) return new_token(l, ELSE, 4);
					if (string_eq(&s, &STRING("enum"))) return new_token(l, ENUM, 4);
				case 'f':
					if (string_eq(&s, &STRING("false"))) return new_token(l, FALSE, 5);
					if (string_eq(&s, &STRING("for"))) return new_token(l, FOR, 3);
					if (string_eq(&s, &STRING("flags"))) return new_token(l, FLAGS, 5);
				case 'i':
					if (string_eq(&s, &STRING("if"))) return new_token(l, IF, 2);
				case 'j':
					if (string_eq(&s, &STRING("jump"))) return new_token(l, JUMP, 4);
				case 'l':
					if (string_eq(&s, &STRING("loop"))) return new_token(l, LOOP, 4);
				case 'r':
					if (string_eq(&s, &STRING("return"))) return new_token(l, RETURN, 6);
				case 's':
					if (string_eq(&s, &STRING("struct"))) return new_token(l, STRUCT, 6);
				case 't':
					if (string_eq(&s, &STRING("tagged"))) return new_token(l, TAGGED, 6);
					if (string_eq(&s, &STRING("true"))) return new_token(l, TRUE, 4);
					if (string_eq(&s, &STRING("type"))) return new_token(l, TYPE, 4);
				case 'u': 
					if (string_eq(&s, &STRING("union"))) return new_token(l, UNION, 5);
				case 'w': 
					if (string_eq(&s, &STRING("while"))) return new_token(l, WHILE, 5);
			}
			
			return new_token(l, ID, i);
		}


		switch (c) {
			case '=':
				if (peek_char(l, 1) == '=') {
					return new_token(l, EQ, 2);
				}
				return new_token(l, ASSIGN, 1);
			case '!':
				if (peek_char(l, 1) == '=') {
					return new_token(l, NEQ, 2);
				}
				return new_token(l, BNOT, 1);
			case '+':
				switch (peek_char(l, 1)) {
					case '+': return new_token(l, INC, 2);
					case '=': return new_token(l, PLUSEQ, 2);
				}
				return new_token(l, PLUS, 1);
			case '-':
				switch (peek_char(l, 1)) {
					case '-': return new_token(l, DEC, 2);
					case '=': return new_token(l, MINUSEQ, 2);
				}
				return new_token(l, MINUS, 1);
			case '*':
				if (peek_char(l, 1) == '=') {
					return new_token(l, TIMESEQ, 2);
				}
				return new_token(l, TIMES, 1);
			case '/':
				if (peek_char(l, 1) == '=') {
					return new_token(l, DIVEQ, 2);
				}
				return new_token(l, DIV, 1);
			case '%':
				if (peek_char(l, 1) == '=') {
					return new_token(l, MODEQ, 2);
				}
				return new_token(l, MOD, 1);
			case '&':
				switch (peek_char(l, 1)) {
					case '=': return new_token(l, BANDEQ, 2);
					case '&': return new_token(l, LAND, 2);
				}
				return new_token(l, BAND, 1);
			case '|':
				switch (peek_char(l, 1)) {
					case '=': return new_token(l, BOREQ, 2);
					case '|': return new_token(l, LOR, 2);
				}
				return new_token(l, BOR, 1);
			case '^': 
				switch (peek_char(l, 1)) {
					case '=': return new_token(l, BXOREQ, 2);
					case '^': return new_token(l, LXOR, 2);
				}
				return new_token(l, BXOR, 1);
			case '(': return new_token(l, LPAREN, 1);
			case ')': return new_token(l, RPAREN, 1);
			case '[': return new_token(l, LBRACKET, 1);
			case ']': return new_token(l, RBRACKET, 1);
			case '{': return new_token(l, LBRACE, 1);
			case '}': return new_token(l, RBRACE, 1);
			case '.':
				if (peek_char(l, 1) == '.') {
					if (peek_char(l, 2) == '.') {
						return new_token(l, TDOT, 3);
					}
					return new_token(l, DDOT, 2);
				}
				return new_token(l, DOT, 1);
			case ',': return new_token(l, COMMA, 1);
			case ';': return new_token(l, SEMICOLON, 1);
			case '<':
				switch (peek_char(l, 1)) {
					case '<': 
						switch (peek_char(l, 2)) {
							case '<':
								if (peek_char(l, 3) == '=') {
									return new_token(l, LROTEQ, 4);
								}
								return new_token(l, LROT, 3);
							case '=':
								return new_token(l, LSHIFTEQ, 3);
						
						}
						return new_token(l, LSHIFT, 2);
					case '=':
						return new_token(l, LTEQ, 2);
				}
				return new_token(l, LT, 1);
			case '>':
				switch (peek_char(l, 1)) {
					case '>': 
						switch (peek_char(l, 2)) {
							case '>':
								if (peek_char(l, 3) == '=') {
									return new_token(l, RROTEQ, 4);
								}
								return new_token(l, RROT, 3);
							case '=':
								return new_token(l, RSHIFTEQ, 3);
						
						}
						return new_token(l, RSHIFT, 2);
					case '=':
						return new_token(l, GTEQ, 2);
				}
				return new_token(l, GT, 1);
			case '@': return new_token(l, AT, 1);
			case '~': return new_token(l, TILDE, 1);
			case '\\': return new_token(l, BACKSLASH, 1);
			case '#': return new_token(l, HASH, 1);
			case '?': return new_token(l, QMARK, 1);
			case '$': return new_token(l, DOLLAR, 1);
			case '`': return new_token(l, BACKTICK, 1);
		}

	l->input_index++; // TODO: We should do error handling here.
	}
	return (token){.type = END, .lexeme.data = "", .lexeme.length = 0, .row = l->row, .col = l->col};
}

// Returns the next found token in lexer input buffer and increments the input index.
token new_token(lexer *l, token_type type, uint32_t length) {
	token t = {
		.type = type,
		.lexeme.data = &l->input.data[l->input_index],
		.lexeme.length = length,
		.row = l->row,
		.col = l->col
	};
	l->col += length;
	l->input_index += length;
	return t;
}

char peek_char(lexer *l, uint32_t offset) {
	// TODO: make bounds check.
	return l->input.data[l->input_index + offset];
}

bool is_number(char c) {
	return (c >= '0' && c <= '9');
}

bool is_alpha(char c) {
	return (c >= 'a' && c <= 'z' || c >= 'A' && c <= 'Z' || c == '_');
}

bool is_alpha_upper(char c) {
	return (c >= 'A' && c <= 'Z' || c == '_');
}

bool is_alpha_lower(char c) {
	return (c >= 'a' && c <= 'z' || c == '_');
}
