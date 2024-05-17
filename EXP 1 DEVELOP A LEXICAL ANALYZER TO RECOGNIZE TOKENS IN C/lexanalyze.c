#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define MAX_CODE_LENGTH 1000
#define MAX_TOKEN_LENGTH 100

typedef enum {
    KEYWORD,
    IDENTIFIER,
    CONSTANT,
    OPERATOR,
    PUNCTUATION,
    INVALID
} TokenType;

const char *keywords[] = {"int", "float", "void", "if", "else", "while", "for"};
const char *operators = "+-*/=<>!";
const char *punctuation = ";(),{}";

int is_keyword(const char *token) {
    for (int i = 0; i < sizeof(keywords) / sizeof(keywords[0]); ++i) {
        if (strcmp(token, keywords[i]) == 0) {
            return 1;
        }
    }
    return 0;
}

int is_operator(char token) {
    return strchr(operators, token) != NULL;
}

int is_punctuation(char token) {
    return strchr(punctuation, token) != NULL;
}

TokenType get_token_type(const char *token) {
    if (is_keyword(token)) {
        return KEYWORD;
    } else if (isdigit(token[0])) {
        return CONSTANT;
    } else if (isalpha(token[0]) || token[0] == '_') {
        return IDENTIFIER;
    } else if (is_operator(token[0])) {
        return OPERATOR;
    } else if (is_punctuation(token[0])) {
        return PUNCTUATION;
    } else {
        return INVALID;
    }
}

void tokenize(const char *code) {
    char token[MAX_TOKEN_LENGTH];
    int i = 0;

    while (*code != '\0') {
        if (isspace(*code)) {
            code++;
            continue;
        }

        if (is_operator(*code)) {
            printf("(%c, OPERATOR)\n", *code);
            code++;
            continue;
        }

        if (is_punctuation(*code)) {
            printf("(%c, PUNCTUATION)\n", *code);
            code++;
            continue;
        }

        if (isalpha(*code) || *code == '_') {
            while (isalnum(*code) || *code == '_') {
                token[i++] = *code++;
            }
            token[i] = '\0';
            i = 0;
            printf("(%s, %s)\n", token, is_keyword(token) ? "KEYWORD" : "IDENTIFIER");
            continue;
        }

        if (isdigit(*code)) {
            while (isdigit(*code) || *code == '.') {
                token[i++] = *code++;
            }
            token[i] = '\0';
            i = 0;
            printf("(%s, CONSTANT)\n", token);
            continue;
        }

        printf("(%c, INVALID)\n", *code);
        code++;
    }
}

int main() {
    char code[MAX_CODE_LENGTH];
    printf("Enter your C code:\n");
    fgets(code, MAX_CODE_LENGTH, stdin);
    tokenize(code);
    return 0;
}
