/*#include "token.h"*/
/*#include "lexer.h"*/

#include <stdint.h>
#include <stdbool.h>
#include "string.h"
int main() {

	string_builder sb = sb_init();
	sb_read_file(&sb, "main.c");
	string *input = (string *)&sb;
	print(input);

	return 0;
}
