#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define OPERATOR_ADD      '+'
#define OPERATOR_SUBTRACT '-'
#define OPERATOR_MULTIPLY '*'
#define OPERATOR_DIVIDE   '/'

#define TOKEN_LITERAL_NUMBER    0
#define TOKEN_OPERATOR_ADD      1
#define TOKEN_OPERATOR_SUBTRACT 2
#define TOKEN_OPERATOR_MULTIPLY 3
#define TOKEN_OPERATOR_DIVIDE   4

#define LEXER_START 0
#define LEXER_OPERATOR 1
#define LEXER_LITERAL 2
#define LEXER_END 3

struct token {
    enum {
        OPERATOR,
        LITERAL_NUMBER,
    } type;
    union {
        int operator;
        float literal_number;
    } data;
};

typedef struct token token_t;

void parse_args(int argc, char **argv, char *expression);
void parse_expression(char *expression, token_t *tokens);
void parse_tokens(token_t tokens[], size_t len);
void print_token(token_t token);

int main(int argc, char **argv) {
    if (argc == 1) {
        return 0;
    }

    char expression[1024];
    token_t tokens[1024];

    parse_args(argc, argv, expression);

    parse_expression(expression, tokens);

    parse_tokens(tokens, 3);

    return 0;
}

void parse_args(int argc, char **argv, char *expression) {
    for (int i = 1; i < argc; i++) {
        for (int j = 0; j < strlen(argv[i]); j++) {
            *(expression++) = argv[i][j];
        }
        *(expression++) = ' ';
    }
    *(--expression) = '\0';
}

void parse_expression(char *expression, token_t *tokens) {
    int state = LEXER_START;
    char *ptr = expression;

    while (*ptr != '\0') {
        if (state == LEXER_START)
        {
            if (*ptr == '+' || *ptr == '-' || *ptr == '*' || *ptr == '/') {
                ptr--;
                state = LEXER_OPERATOR;
            } else if (*ptr >= '0' && *ptr <= '9') {
                ptr--;
                state = LEXER_LITERAL;
            }
        }
        else if (state == LEXER_OPERATOR)
        {
            token_t token;

            token.type = OPERATOR;

            switch (*ptr) {
                case OPERATOR_ADD:
                    token.data.operator = OPERATOR_ADD;
                    break;
                case OPERATOR_SUBTRACT:
                    token.data.operator = OPERATOR_ADD;
                    break;
                case OPERATOR_MULTIPLY:
                    token.data.operator = OPERATOR_ADD;
                    break;
                case OPERATOR_DIVIDE:
                    token.data.operator = OPERATOR_ADD;
                    break;
            }

            *(tokens++) = token;

            state = LEXER_START;
        }
        else if (state == LEXER_LITERAL)
        {
            token_t token;

            token.type = LITERAL_NUMBER;

            int len = 0;
            char literal[1024];
            while ((*ptr >= '0' && *ptr <= '9') || *ptr == '.') {
                literal[len++] = *ptr;
                ptr++;
            }
            literal[len] = '\0';

            token.data.literal_number = atof(literal);

            *(tokens++) = token;

            state = LEXER_START;
        }

        ptr++;
    }
}

void parse_tokens(token_t tokens[], size_t len) {
    int stack_ptr = 0;
    float stack[1024];

    for (size_t i = 0; i < len; i++) {
        token_t token = tokens[i];

        if (token.type == LITERAL_NUMBER) {
            stack[stack_ptr++] = token.data.literal_number;
        }

        print_token(tokens[i]);

        printf("\n");

        printf("stack: [ ");
        for (int i = 0; i < stack_ptr; i++) {
            printf("%f ", stack[i]);
        }
        printf("]\n");
    }
}

void print_token(token_t token) {
    if (token.type == OPERATOR) {
        printf("{%c}", token.data.operator);
    } else if (token.type == LITERAL_NUMBER) {
        printf("{%f}", token.data.literal_number);
    }
}

