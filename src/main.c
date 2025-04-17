#include "token.h"
#include "cli/args.h"
#include "frontend/tokenizer.h"
#include "backend/interpreter.h"

int main(int argc, char** argv) {
    char expression[1024];
    parse_args(argc, argv, expression);

    int tokens_len = 0;
    Token tokens[1024];
    tokens_len = tokenize(expression, tokens, 1024);

    interprete(tokens, tokens_len);

    return 0;
}

