#include <stdio.h>
#include <assert.h>
#include "interpreter.h"
#include "stack.h"
#include "operator/interpreter.h"

void interprete_operator(Stack* stack, token_t token);
void interprete_literal_number(Stack* stack, token_t token);

void interprete(token_t tokens[], int len) {
    Stack stack;

    stack_init(&stack, 1024);

    int res = 0;
    for (int i = 0; i < len; i++) {
        token_t token = tokens[i];

        switch(token.type) {
            case OPERATOR:
                res = operator_interprete(&stack, token);
                break;
            case LITERAL_NUMBER:
                interprete_literal_number(&stack, token);
                res = 0;
                break;
        }

        if (res)
            break;
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

    int err;

    StackItem rhs;
    if ((err = stack_pop_type(stack, NUMBER, &rhs))) {
        if (err == E_STACK_TYPE) {
            printf("Operand error: operand type is invalid!\n");
        } else if (err == E_STACK_EMPTY) {
            printf("Operand error: not enough operands on stack!\n");
        }

        return;
    }

    StackItem lhs;
    if ((err = stack_pop_type(stack, NUMBER, &lhs))) {
        if (err == E_STACK_TYPE) {
            printf("Operand error: operand type is invalid!\n");
        } else if (err == E_STACK_EMPTY) {
            printf("Operand error: not enough operands on stack!\n");
        }

        return;
    }

    StackItem res;
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

