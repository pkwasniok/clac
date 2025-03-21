#include "lexer.h"
#include <stdlib.h>

#define LEXER_START    0
#define LEXER_OPERATOR 1
#define LEXER_LITERAL  2

size_t tokenize(char *expression, token_t tokens[], size_t len) {
    int state = LEXER_START;
    char *ptr = expression;

    size_t tokens_len = 0;

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
                    token.data.operator = OPERATOR_SUBTRACT;
                    break;
                case OPERATOR_MULTIPLY:
                    token.data.operator = OPERATOR_MULTIPLY;
                    break;
                case OPERATOR_DIVIDE:
                    token.data.operator = OPERATOR_DIVIDE;
                    break;
            }

            tokens[tokens_len++] = token;

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

            tokens[tokens_len++] = token;

            state = LEXER_START;
        }

        if (tokens_len >= len) {
            return tokens_len;
        }

        ptr++;
    }

    return tokens_len;
}

