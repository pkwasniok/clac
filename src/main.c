#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "args.h"
#include "lexer.h"
#include "interpreter.h"

int main(int argc, char **argv) {
    char expression[1024];
    token_t tokens[1024];

    parse_args(argc, argv, expression);

    int tokens_len = tokenize(expression, tokens, 1024);

    float result = interprete(tokens, tokens_len);

    if (errno == EZERO) {
        printf("Cannot divide by zero!\n");
    } else {
        printf("%f\n", result);
    }

    return 0;
}

