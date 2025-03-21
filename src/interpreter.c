#include "interpreter.h"
#include <stdlib.h>
#include <stdio.h>

void print_stack(float stack[], int len);
void print_token(token_t token);

void interprete(token_t tokens[], int len) {
    float stack[1024];
    int stack_ptr = 0;

    for (int i = 0; i < len; i++) {
        token_t token = tokens[i];

        if (token.type == OPERATOR) {
            if (stack_ptr < 2) {
                break;
            }

            float rhs = stack[--stack_ptr];
            float lhs = stack[--stack_ptr];
            float res = 0;

            switch (token.data.operator) {
                case OPERATOR_ADD:
                    res = lhs + rhs;
                    break;
                case OPERATOR_SUBTRACT:
                    res = lhs - rhs;
                    break;
                case OPERATOR_MULTIPLY:
                    res = lhs * rhs;
                    break;
                case OPERATOR_DIVIDE:
                    res = lhs / rhs;
                    break;
            }

            stack[stack_ptr++] = res;
        } else if (token.type == LITERAL_NUMBER) {
            stack[stack_ptr++] = token.data.literal_number;
        }

        print_token(token);
        printf("\n");
        print_stack(stack, stack_ptr);
        printf("\n\n");
    }
}

void print_stack(float stack[], int len) {
    printf("[ ");
    for (int i = 0; i < len; i++)
        printf("%.4f ", stack[i]);
    printf("]\n");
}

void print_token(token_t token) {
    if (token.type == OPERATOR) {
        printf("{%c}", token.data.operator);
    } else if (token.type == LITERAL_NUMBER) {
        printf("{%.4f}", token.data.literal_number);
    }
}

