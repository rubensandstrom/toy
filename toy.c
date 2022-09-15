#include <stdlib.h>
#include <stdio.h>

char c; // current char.

void error(char *msg) {
    printf("\nError: %s Expected\n", msg);
    exit(0);
}

void revpol(char c) {
    char stack [64];
    char que [64];

    char top = -1; // index of top of stack.
    char end = -1; // index of end of que.
    while (c != EOF) {
        if (c >= '0' && c <= '9') {
            end += 1;
            que[end] = c;
        }
        switch(c) { // we need to do an exeption for when stack and que is empty.
            case '+': {
                while (top >= 0 && (stack[top] == '*' | stack[top] == '/' | stack[top] == '-')) {
                    end += 1;
                    que[end] = stack[top];
                    top -= 1;
                }
                top += 1;
                stack[top] = c;
                break;

            }
            case '-': {
                while (top >= 0 && (stack[top] == '*' | stack[top] == '/' | stack[top] == '+')) {
                    end += 1;
                    que[end] = stack[top];
                    top -= 1;
                }
                top += 1;
                stack[top] = c;
                break;
            }
            case '*': {
                while (top >= 0 && (stack[top] == '/')) {
                    end += 1;
                    que[end] = stack[top];
                    top -= 1;
                }
                top += 1;
                stack[top] = c;
                break;
            }
            case '/': {
                while (top >= 0 && (stack[top] == '*')) {
                    end += 1;
                    que[end] = stack[top];
                    top -= 1;
                }
                top += 1;
                stack[top] = c;
                break;
            }

        }

        c = getchar();
                   /*
        case '%': {
            break;   
        }
        case '|': {
            break;
        }
        case '&': {
            break;            
        }
        */

    }
    while (top >= 0) {
        end += 1;
        que[end] = stack[top];
        top -= 1;
    }
    for (char i = 0; i <= end; i++) {

        printf("%c", que[i]);
    }
    printf("\n");
}



int main(int argc, char *argv[]) {

    // INIT
    c = getchar();

    revpol(c);
    printf("hello world\n");
}
