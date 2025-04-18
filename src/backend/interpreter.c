#include <stdio.h>
#include <assert.h>
#include "interpreter.h"
#include "stack.h"
#include "operator/interpreter.h"
#include "literal/interpreter.h"

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
                res = literal_interprete(&stack, token);
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

