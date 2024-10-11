#ifndef TOKEN_H
#define TOKEN_H

#include <stdint.h>
#include "strings.h"

typedef enum token_type {
	ASSIGN,
	EQ,
	BNOT,
	NEQ,

	PLUS,
	INC,
	PLUSEQ,
	MINUS,
	DEC,
	MINUSEQ,
	TIMES,
	TIMESEQ,
	DIV,
	DIVEQ,
	MOD,
	MODEQ,


	BAND,
	BANDEQ,
	LAND,
	BOR,
	BOREQ,
	LOR,
	LNOT,
	BXOR,
	BXOREQ,
	LXOR,

	LPAREN,
	RPAREN,
	LBRACKET,
	RBRACKET,
	LBRACE,
	RBRACE,

	// SEPARATORS
	DOT,
	DDOT,
	TDOT,

	COMMA,
	SEMICOLON,
	COLON,

	LT,
	LTEQ,
	LSHIFT,
	LSHIFTEQ,
	LROT,
	LROTEQ,
	GT,
	GTEQ,
	RSHIFT,
	RSHIFTEQ,
	RROT,
	RROTEQ,

	AT,
	BACKSLASH,
	TILDE,
	HASH,
	QMARK,
	DOLLAR,
	BACKTICK,


	// OPERATORS

	NUMBER,
	VOID,
	ID,
	CID,
	PID,
	PCID,

	// KEYWORDS
	FOR,
	WHILE,
	LOOP,
	BREAK,
	CONTINUE,
	JUMP,
	IF,
	ELSE,
	TRUE,
	FALSE,

	TYPE,

	STRUCT,
	ENUM,
	FLAGS,
	UNION,
	TAGGED,
	UINT,
	UINTVEC,
	INT,
	INTVEC,
	FLOAT,
	FLOATVEC,
	BITS,

	RETURN,

	ASM,

	END,
} token_type;

extern string token_debug[];

typedef struct token {
	token_type type;
	string lexeme;

	uint32_t row;
	uint32_t col;
} token;

#endif // TOKEN_H
