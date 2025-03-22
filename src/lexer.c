#include "lexer.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define LEXER_START           0
#define LEXER_OPERATOR        1
#define LEXER_LITERAL_NUMBER  2

size_t tokenize(char *expression, token_t tokens[], size_t len) {
    int state = LEXER_START;
    char *ptr = expression;

    size_t tokens_len = 0;

    tokens = tokens;
    len = len;

    int literal_ptr = 0;
    char literal[1024];

    while (*ptr != '\0') {
        switch (state) {

            case LEXER_START:

                if (strchr("+-*/^", *ptr) != NULL && (*(ptr+1) == ' ' || *(ptr+1) == '\0')) {
                    state = LEXER_OPERATOR;
                    ptr--;
                } else if (strchr("+-0123456789", *ptr) != NULL) {
                    state = LEXER_LITERAL_NUMBER;
                    ptr--;
                }

                break;

            case LEXER_OPERATOR:

                char operator = *ptr;

                token_t token;
                token.type = OPERATOR;
                token.data.operator = operator;

                *(tokens++) = token;

                state = LEXER_START;
                tokens_len++;

                break;

            case LEXER_LITERAL_NUMBER:

                literal[literal_ptr++] = *ptr;

                if (*(ptr+1) == ' ' || *(ptr+1) == '\0') {
                    literal[literal_ptr] = '\0';
                    literal_ptr = 0;

                    float literal_number = atof(literal);

                    token_t token;
                    token.type = LITERAL_NUMBER;
                    token.data.literal_number = literal_number;

                    *(tokens++) = token;
                    tokens_len++;

                    state = LEXER_START;
                }

                break;

        }

        if (tokens_len >= len) {
            return tokens_len;
        }

        ptr++;
    }

    return tokens_len;
}

