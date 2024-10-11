#ifndef AST_H
#define AST_H

#include "token.h"

// Expressions
typedef union expression {} expression;

// Statements

typedef struct return_statement { 
	expression *value; 
} return_statement;

typedef struct decl_statement {
	token name;
	expression *value;
} decl_statement;

typedef union statement {
	return_statement *rs;
	decl_statement *ds;
} statement;

typedef struct program {
	statement *s;
} program;


#endif // AST_H
