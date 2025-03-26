#include <stdio.h>
#include "token.h"
#include "cli/args.h"
#include "frontend/tokenizer.h"
#include "backend/interpreter.h"

int main(int argc, char **argv) {
    char expression[1024];
    parse_args(argc, argv, expression);

    int tokens_len = 0;
    token_t tokens[1024];
    tokens_len = tokenize(expression, tokens, 1024);

    /*for (int i = 0; i < tokens_len; i++) {*/
    /*    print_token(tokens[i]);*/
    /*}*/

    interprete(tokens, tokens_len);

    return 0;
}

