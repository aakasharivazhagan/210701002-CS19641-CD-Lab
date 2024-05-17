%{
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

int num1 = 0, num2 = 0;
char op;
%}

%int yywrap

%%
[0-9]+ { printf("\033[0;32mNumber: %s\033[0m\n", yytext); }
[-+*/] { op = *yytext; printf("\033[0;32mOperator: %c\033[0m\n", op); }
\n { printf("\033[0;34mEnter arithmetic expression (e.g., 2 + 3 * 4):\033[0m\n"); }
[ \t] { /* ignore whitespace */ }
. { printf("\033[0;31mInvalid character: %s\033[0m\n", yytext); }
%%

int yywrap(void) {
    return 1;
}

int main() {
    char input[100];

    printf("\033[0;34mEnter arithmetic expression (e.g., 2 + 3 * 4):\033[0m\n");
    while (fgets(input, sizeof(input), stdin)) {
        YY_BUFFER_STATE buffer = yy_scan_string(input);
        yylex();
        yy_delete_buffer(buffer);

        if (sscanf(input, "%d %c %d", &num1, &op, &num2) == 3) {
            switch(op) {
                case '+':
                    printf("\033[0;34mResult: %d\n\033[0m", num1 + num2);
                    break;
                case '-':
                    printf("\033[0;34mResult: %d\n\033[0m", num1 - num2);
                    break;
                case '*':
                    printf("\033[0;34mResult: %d\n\033[0m", num1 * num2);
                    break;
                case '/':
                    if (num2 != 0)
                        printf("\033[0;34mResult: %.2f\n\033[0m", (float)num1 / num2);
                    else
                        printf("\033[0;31mError: Division by zero\n\033[0m");
                    break;
                default:
                    printf("\033[0;31mError: Invalid operator\n\033[0m");
                    break;
            }
        } else {
            printf("\033[0;31mError: Invalid input format\n\033[0m");
        }
    }
    return 0;
}
