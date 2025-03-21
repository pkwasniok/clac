#pragma once
#include <stdlib.h>

#define OPERATOR_ADD      '+'
#define OPERATOR_SUBTRACT '-'
#define OPERATOR_MULTIPLY '*'
#define OPERATOR_DIVIDE   '/'

typedef struct token {
    enum {
        OPERATOR,
        LITERAL_NUMBER,
    } type;
    union {
        int operator;
        float literal_number;
    } data;
} token_t;

size_t tokenize(char *expression, token_t tokens[], size_t len);

