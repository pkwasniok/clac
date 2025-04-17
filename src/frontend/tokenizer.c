#include "tokenizer.h"
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define STATE_START          0
#define STATE_OPERATOR       1
#define STATE_LITERAL_NUMBER 2
#define STATE_END            3

int tokenize(char *expression, Token tokens[], int len) {
    int state, tokens_len, buffer_len;
    char buffer[1024];
    Token token;

    tokens_len = 0;
    buffer_len = 0;
    state = STATE_START;

    while (state != STATE_END) {
        char c = *(expression++);

        switch (state) {
            
            case STATE_START:
                buffer_len = 0;

                if (strchr("+-x/", c))
                    state = STATE_OPERATOR;
                else if (isdigit(c))
                    state = STATE_LITERAL_NUMBER;

                break;

            case STATE_OPERATOR:

                if (isdigit(c)) {
                    state = STATE_LITERAL_NUMBER;
                } else if (isspace(c) || c == '\0') {
                    buffer[buffer_len++] = '\0';

                    token.type = OPERATOR;

                    switch (buffer[0]) {
                        case '+':
                            token.value.operator = ADD;
                            break;
                        case '-':
                            token.value.operator = SUBTRACT;
                            break;
                        case 'x':
                            token.value.operator = MULTIPLY;
                            break;
                        case '/':
                            token.value.operator = DIVIDE;
                            break;
                    }

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

