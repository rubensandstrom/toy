#include <stdbool.h>
#include <stdint.h>
#include "string.h"
#include "token.h"

string token_debug[] = {
	[ASSIGN] = STRING("ASSIGN"),
	[EQ] = STRING("EQ"),
	[BNOT] = STRING("BNOT"),
	[NEQ] = STRING("NEQ"),
	[PLUS] = STRING("PLUS"),
	[INC] = STRING("INC"),
	[PLUSEQ] = STRING("PLUSEQ"),
	[MINUS] = STRING("MINUS"),
	[DEC] = STRING("DEC"),
	[MINUSEQ] = STRING("MINUSEQ"),
	[TIMES] = STRING("TIMES"),
	[TIMESEQ] = STRING("TIMESEQ"),
	[DIV] = STRING("DIV"),
	[DIVEQ] = STRING("DIVEQ"),
	[MOD] = STRING("MOD"),
	[MODEQ] = STRING("MODEQ"),
	[BAND] = STRING("BAND"),
	[BANDEQ] = STRING("BANDEQ"),
	[LAND] = STRING("LAND"),
	[BOR] = STRING("BOR"),
	[BOREQ] = STRING("BOREQ"),
	[LOR] = STRING("LOR"),
	[LNOT] = STRING("LNOT"),
	[BXOR] = STRING("BXOR"),
	[BXOREQ] = STRING("BXOREQ"),
	[LXOR] = STRING("LXOR"),
	[LPAREN] = STRING("LPAREN"),
	[RPAREN] = STRING("RPAREN"),
	[LBRACKET] = STRING("LBRACKET"),
	[RBRACKET] = STRING("RBRACKET"),
	[LBRACE] = STRING("LBRACE"),
	[RBRACE] = STRING("RBRACE"),
	[DOT] = STRING("DOT"),
	[DDOT] = STRING("DDOT"),
	[TDOT] = STRING("TDOT"),
	[COMMA] = STRING("COMMA"),
	[SEMICOLON] = STRING("SEMICOLON"),
	[COLON] = STRING("COLON"),
	[LT] = STRING("LT"),
	[LTEQ] = STRING("LTEQ"),
	[LSHIFT] = STRING("LSHIFT"),
	[LSHIFTEQ] = STRING("LSHIFTEQ"),
	[LROT] = STRING("LROT"),
	[LROTEQ] = STRING("LROTEQ"),
	[GT] = STRING("GT"),
	[GTEQ] = STRING("GTEQ"),
	[RSHIFT] = STRING("RSHIFT"),
	[RSHIFTEQ] = STRING("RSHIFTEQ"),
	[RROT] = STRING("RROT"),
	[RROTEQ] = STRING("RROTEQ"),
	[AT] = STRING("AT"),
	[BACKSLASH] = STRING("BACKSLASH"),
	[TILDE] = STRING("TILDE"),
	[HASH] = STRING("HASH"),
	[QMARK] = STRING("QMARK"),
	[DOLLAR] = STRING("DOLLAR"),
	[BACKTICK] = STRING("BACKTICK"),
	[NUMBER] = STRING("NUMBER"),
	[VOID] = STRING("VOID"),
	[ID] = STRING("ID"),
	[CID] = STRING("CID"),
	[PID] = STRING("PID"),
	[PCID] = STRING("PCID"),
	[FOR] = STRING("FOR"),
	[WHILE] = STRING("WHILE"),
	[LOOP] = STRING("LOOP"),
	[BREAK] = STRING("BREAK"),
	[CONTINUE] = STRING("CONTINUE"),
	[JUMP] = STRING("JUMP"),
	[IF] = STRING("IF"),
	[ELSE] = STRING("ELSE"),
	[TRUE] = STRING("TRUE"),
	[FALSE] = STRING("FALSE"),
	[TYPE] = STRING("TYPE"),
	[STRUCT] = STRING("STRUCT"),
	[ENUM] = STRING("ENUM"),
	[FLAGS] = STRING("FLAGS"),
	[UNION] = STRING("UNION"),
	[TAGGED] = STRING("TAGGED"),
	[UINT] = STRING("UINT"),
	[UINTVEC] = STRING("UINTVEC"),
	[INT] = STRING("SINT"),
	[INTVEC] = STRING("SINTVEC"),
	[FLOAT] = STRING("FLOAT"),
	[FLOATVEC] = STRING("FLOATVEC"),
	[BITS] = STRING("BITS"),
	[RETURN] = STRING("RETURN"),
	[ASM] = STRING("ASM"),
	[NEWLINE] = STRING("NEWLINE"),
	[END] = STRING("END"),
};

