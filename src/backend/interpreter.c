#include <stdio.h>
#include <assert.h>
#include "interpreter.h"
#include "stack.h"
#include "operator/interpreter.h"

int interprete_literal_number(Stack* stack, Token token);

void interprete(Token tokens[], int len) {
    Stack stack;

    stack_init(&stack, 1024);

    int res = 0;
    for (int i = 0; i < len; i++) {
        Token token = tokens[i];

        switch(token.type) {

            case OPERATOR:
                res = operator_interprete(&stack, token);
                break;

            case LITERAL_NUMBER:
                res = interprete_literal_number(&stack, token);
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

int interprete_literal_number(Stack* stack, Token token) {
    assert(token.type == LITERAL_NUMBER);

    StackItem item;
    item.type = NUMBER;
    item.data.number = token.value.literal_number;

    if (stack_push(stack, item)) {
        printf("Stack error!\n");
    }

    return 0;
}

