#ifndef AST_H
#define AST_H
#include <stdint.h>
#include "string.h"
#include "token.h"
#include "darray.h"

// Expressions
typedef union expression {} expression;

// Statements

typedef struct return_statement { 
	expression *value; 
} return_statement;

typedef struct decl_statement {
	token name;
	token type;
	expression *value;
} decl_statement;

typedef union statement {
	return_statement *rs;
	decl_statement *ds;
} statement;

typedef struct program {
	dynamic_array s; //statements
} program;


#endif // AST_H
