#include <stdio.h>
#include <math.h>
#include <assert.h>
#include "interpreter.h"
#include "stack.h"
#include "macro.h"

void interprete_operator(token_t token);
void interprete_literal_number(token_t token);

void interprete(token_t tokens[], int len) {
    stack_init(1024);

    stack_load("stack");

    for (int i = 0; i < len; i++) {
        token_t token = tokens[i];

        switch(token.type) {
            case OPERATOR:
                interprete_operator(token);
                break;
            case MACRO:
                interprete_macro(token);
                break;
            case LITERAL_NUMBER:
                interprete_literal_number(token);
                break;
        }
    }

    stack_dump("stack");

    stack_unwind();
}

void interprete_operator(token_t token) {
    assert(token.type == OPERATOR);

    item_t lhs, rhs, res;
    if (stack_pop(&rhs) || stack_pop(&lhs)) {
        printf("Operator error!\n");
        return;
    }

    assert(rhs.type == NUMBER);
    assert(lhs.type == NUMBER);

    res.type = NUMBER;

    switch (token.value.operator) {
        case OPERATOR_ADD:
            res.value.number = lhs.value.number + rhs.value.number;
            break;
        case OPERATOR_SUBTRACT:
            res.value.number = lhs.value.number - rhs.value.number;
            break;
        case OPERATOR_MULTIPLY:
            res.value.number = lhs.value.number * rhs.value.number;
            break;
        case OPERATOR_DIVIDE:
            if (rhs.value.number == 0) {
                printf("Operator error!\n");
                return;
            }
            res.value.number = lhs.value.number / rhs.value.number;
            break;
        case OPERATOR_POWER:
            res.value.number = pow(lhs.value.number, rhs.value.number);
            break;
        default:
            printf("Operator error!\n");
            return;
            break;
    }

    stack_push(res);
}

void interprete_literal_number(token_t token) {
    assert(token.type == LITERAL_NUMBER);

    item_t item;
    item.type = NUMBER;
    item.value.number = token.value.literal_number;

    if (stack_push(item)) {
        printf("Stack error!\n");
    }
}

