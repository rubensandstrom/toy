#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

// can't stand unfixed type sizes anymore.
// will be used when is a number. char is stil char.
typedef int8_t s8;
typedef int16_t s16;
typedef int32_t s32;
typedef int64_t s64;

typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;

char c; // current char.

void error(char *msg) {
    printf("\nError: %s Expected\n", msg);
    exit(0);
}

char * tokenizer (char *c) {
    return "";
}

void printOpp(char c) {
    if (c >= '0' && c <= '9') printf("#%c ", c);
    else if (c == '+') printf("ADD ");
    else if (c == '-') printf("SUB ");
    else if (c == '*') printf("MUL ");
    else if (c == '/') printf("DIV ");
}

// Shunting yard algorithm.
void revpol(char c) {

    char stack [64];
    s8 top = -1; // index of top of stack.

    printf("#0 "); // all expressions should start with a 0

    while (c != EOF) {
        if (c >= '0' && c <= '9') {
            printOpp(c);
        }
        switch(c) {
            case '+': {
                while (top >= 0 && (stack[top] == '*' | stack[top] == '/' | stack[top] == '-')) {
                    printOpp(stack[top--]);
                }
                stack[++top] = c;
                break;
            }
            case '-': {
                while (top >= 0 && (stack[top] == '*' | stack[top] == '/' | stack[top] == '+')) {
                    printOpp(stack[top--]);
                }
                stack[++top] = c;
                break;
            }
            case '*': {
                while (top >= 0 && (stack[top] == '/')) {
                    printOpp(stack[top--]);
                }
                stack[++top] = c;
                break;
            }
            case '/': {
                while (top >= 0 && (stack[top] == '*')) {
                    printOpp(stack[top--]);
                }
                stack[++top] = c;
                break;
            }
            case '(': {
                stack[++top] = c;
                break;
            }
            case ')': {
                while (stack[top] != '(') {
                    printOpp(stack[top--]);
                }
                top--;
            }
        }

        c = getchar();
    }
    while (top >= 0) {
        printOpp(stack[top--]);
    }
    printf("\n");
}

u8 main(u8 argc, char *argv[]) {

    // INIT
   c = getchar(); 
   revpol(c);
}
