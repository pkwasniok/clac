#include "interpreter.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

void print_stack(float stack[], int len);
void print_token(token_t token);

int interprete_operator(float *stack, int *stack_ptr, int operator);
int interprete_literal_number(float *stack, int *stack_ptr, float literal_number);

float interprete(token_t tokens[], int len) {
    float stack[1024];
    int stack_ptr = 0;

    for (int i = 0; i < len; i++) {
        token_t token = tokens[i];

        switch (token.type) {
            case OPERATOR:
                interprete_operator(stack, &stack_ptr, token.data.operator);
                break;
            case LITERAL_NUMBER:
                interprete_literal_number(stack, &stack_ptr, token.data.literal_number);
                break;
        }
    }

    if (stack_ptr > 0)
        stack_ptr -= 1;

    return stack[stack_ptr];
}

int interprete_operator(float *stack, int *stack_ptr, int operator) {
    float result, rhs, lhs;

    rhs = stack[--(*stack_ptr)];
    lhs = stack[--(*stack_ptr)];

    switch (operator) {
        case OPERATOR_ADD:
            result = lhs + rhs;
            break;
        case OPERATOR_SUBTRACT:
            result = lhs - rhs;
            break;
        case OPERATOR_MULTIPLY:
            result = lhs * rhs;
            break;
        case OPERATOR_DIVIDE:
            result = lhs / rhs;
            break;
        case OPERATOR_POWER:
            result = pow(lhs, rhs);
            break;
    }

    stack[(*stack_ptr)++] = result;

    return 0;
}

int interprete_literal_number(float *stack, int *stack_ptr, float literal_number) {
    stack[(*stack_ptr)++] = literal_number;

    return 0;
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

