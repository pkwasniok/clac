#include "tokenizer.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define LEXER_START          0
#define LEXER_OPERATOR       1
#define LEXER_MACRO          2
#define LEXER_LITERAL_NUMBER 3
#define LEXER_END            4

size_t tokenize(char *expression, token_t tokens[], size_t len) {
    int state = LEXER_START;
    char *ptr = expression;

    size_t tokens_len = 0;

    int literal_ptr = 0;
    char literal[1024];

    while (state != LEXER_END) {
        switch (state) {

            case LEXER_START:

                if (strchr("+-*/^.", *ptr) != NULL && (*(ptr+1) == ' ' || *(ptr+1) == '\0')) {
                    state = LEXER_OPERATOR;
                    ptr--;
                } else if (strchr("+-0123456789", *ptr) != NULL) {
                    state = LEXER_LITERAL_NUMBER;
                    ptr--;
                } else if (strchr("@", *ptr) != NULL) {
                    state = LEXER_MACRO;
                } else {
                    state = LEXER_END;
                }

                break;

            case LEXER_OPERATOR:

                char operator = *ptr;

                token_t token;
                token.type = OPERATOR;
                token.value.operator = (operator == '.') ? '*' : operator;

                *(tokens++) = token;

                state = LEXER_START;
                tokens_len++;

                break;

            case LEXER_MACRO:
                if (!isspace(*ptr)) {
                    literal[literal_ptr++] = *ptr;
                } else {
                    literal[literal_ptr] = '\0';
                    literal_ptr = 0;

                    printf("%s\n", literal);

                    state = LEXER_START;
                }

                break;

            case LEXER_LITERAL_NUMBER:

                literal[literal_ptr++] = *ptr;

                if (*(ptr+1) == ' ' || *(ptr+1) == '\0') {
                    literal[literal_ptr] = '\0';
                    literal_ptr = 0;

                    float literal_number = atof(literal);

                    token_t token;
                    token.type = LITERAL_NUMBER;
                    token.value.literal_number = literal_number;

                    *(tokens++) = token;
                    tokens_len++;

                    state = LEXER_START;
                }

                break;

            case LEXER_END:
                break;
        }

        if (tokens_len >= len) {
            return tokens_len;
        }

        ptr++;
    }

    return tokens_len;
}

