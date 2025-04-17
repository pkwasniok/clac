#include <stdio.h>
#include <math.h>
#include <assert.h>
#include "interpreter.h"
#include "stack.h"

void interprete_operator(Stack* stack, token_t token);
void interprete_literal_number(Stack* stack, token_t token);

void interprete(token_t tokens[], int len) {
    Stack stack;

    stack_init(&stack, 1024);

    for (int i = 0; i < len; i++) {
        token_t token = tokens[i];

        switch(token.type) {
            case OPERATOR:
                interprete_operator(&stack, token);
                break;
            case LITERAL_NUMBER:
                interprete_literal_number(&stack, token);
                break;
        }
    }

    // Unwind and print stack
    StackItem item;
    while (!stack_pop(&stack, &item)) {
        printf("%f\n", item.data.number);
    }

    stack_deinit(&stack);
}

void interprete_operator(Stack* stack, token_t token) {
    assert(token.type == OPERATOR);

    StackItem lhs, rhs, res;
    if (stack_pop(stack, &rhs) || stack_pop(stack, &lhs)) {
        printf("Operator error!\n");
        return;
    }

    assert(rhs.type == NUMBER);
    assert(lhs.type == NUMBER);

    res.type = NUMBER;

    switch (token.value.operator) {
        case OPERATOR_ADD:
            res.data.number = lhs.data.number + rhs.data.number;
            break;
        case OPERATOR_SUBTRACT:
            res.data.number = lhs.data.number - rhs.data.number;
            break;
        case OPERATOR_MULTIPLY:
            res.data.number = lhs.data.number * rhs.data.number;
            break;
        case OPERATOR_DIVIDE:
            if (rhs.data.number == 0) {
                printf("Operator error!\n");
                return;
            }
            res.data.number = lhs.data.number / rhs.data.number;
            break;
        case OPERATOR_POWER:
            res.data.number = pow(lhs.data.number, rhs.data.number);
            break;
        default:
            printf("Operator error!\n");
            return;
            break;
    }

    stack_push(stack, res);
}

void interprete_literal_number(Stack* stack, token_t token) {
    assert(token.type == LITERAL_NUMBER);

    StackItem item;
    item.type = NUMBER;
    item.data.number = token.value.literal_number;

    if (stack_push(stack, item)) {
        printf("Stack error!\n");
    }
}

