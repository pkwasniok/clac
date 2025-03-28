#include "tokenizer.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define STATE_START          0
#define STATE_OPERATOR       1
#define STATE_MACRO          2
#define STATE_LITERAL_NUMBER 3
#define STATE_END            4

int tokenize(char *expression, token_t tokens[], int len) {
    int state, tokens_len, buffer_len;
    char buffer[1024];
    token_t token;

    tokens_len = 0;
    buffer_len = 0;
    state = STATE_START;

    while (state != STATE_END) {
        char c = *(expression++);

        switch (state) {
            
            case STATE_START:
                buffer_len = 0;

                if (strchr("+-./^", c))
                    state = STATE_OPERATOR;
                else if (c == '@')
                    state = STATE_MACRO;
                else if (isdigit(c))
                    state = STATE_LITERAL_NUMBER;

                break;

            case STATE_OPERATOR:

                if (isspace(c) || c == '\0') {
                    buffer[buffer_len++] = '\0';

                    token.type = OPERATOR;
                    token.value.operator = buffer[0];
                    tokens[tokens_len++] = token;
                }

                break;

            case STATE_MACRO:

                if (isspace(c) || c == '\0') {
                    buffer[buffer_len++] = '\0';

                    // This leaks memory!!!
                    char *macro = malloc(sizeof(char) * buffer_len);
                    strcpy(macro, buffer);

                    token.type = MACRO;
                    token.value.macro = macro;
                    tokens[tokens_len++] = token;
                }

                break;

            case STATE_LITERAL_NUMBER:

                if (isspace(c) || c == '\0') {
                    buffer[buffer_len++] = '\0';

                    token.type = LITERAL_NUMBER;
                    token.value.literal_number = atof(buffer);
                    tokens[tokens_len++] = token;
                }

                break;
        }

        // Common transitions
        if (isspace(c))
            state = STATE_START;
        else if (c == '\0')
            state = STATE_END;

        // Buffer overflows
        if (tokens_len >= len)
            state = STATE_END;

        buffer[buffer_len++] = c;
    }

    return tokens_len;
}

