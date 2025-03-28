#include "macro.h"
#include "../token.h"
#include <assert.h>
#include <stdio.h>
#include <string.h>
#include "stack.h"
#include <math.h>

void handler_sqrt();
void handler_pow();
void handler_pop();
void handler_sin();
void handler_cos();
void handler_tan();
void handler_cot();

void interprete_macro(token_t token) {
    assert(token.type == MACRO);

    struct macro macros[1024];

    macros[0].name = "@sqrt";
    macros[0].handler = &handler_sqrt;

    macros[1].name = "@pow";
    macros[1].handler = &handler_pow;

    macros[2].name = "@pop";
    macros[2].handler = &handler_pop;

    macros[3].name = "@sin";
    macros[3].handler = &handler_sin;

    macros[4].name = "@cos";
    macros[4].handler = &handler_cos;

    macros[5].name = "@tan";
    macros[5].handler = &handler_tan;

    macros[6].name = "@cot";
    macros[6].handler = &handler_cot;

    int found = 0;
    for (int i = 0; i < 7; i++) {
        if (strcmp(macros[i].name, token.value.macro) == 0) {
            (*macros[i].handler)();
            found = 1;
            break;
        }
    }

    if (found == 0) {
        printf("Macro \"%s\" is undefined\n", token.value.macro);
    }
}

void handler_sqrt() {
    item_t item;

    stack_pop(&item);

    assert(item.type == NUMBER);

    item.value.number = sqrt(item.value.number);

    stack_push(item);
}

void handler_pow() {
    item_t rhs, lhs;

    stack_pop(&rhs);
    stack_pop(&lhs);

    assert(rhs.type == NUMBER);
    assert(lhs.type == NUMBER);

    lhs.value.number = pow(lhs.value.number, rhs.value.number);

    stack_push(lhs);
}

void handler_pop() {
    item_t item;

    stack_pop(&item);

    printf("{number, %.4f}\n", item.value.number);
}

void handler_sin() {
    item_t item;

    stack_pop(&item);

    item.value.number = sin(item.value.number);

    stack_push(item);
}

void handler_cos() {
    item_t item;

    stack_pop(&item);

    item.value.number = cos(item.value.number);

    stack_push(item);
}

void handler_tan() {
    item_t item;

    stack_pop(&item);

    item.value.number = tan(item.value.number);

    stack_push(item);
}

void handler_cot() {
    item_t item;

    stack_pop(&item);

    item.value.number = 1.0 / tan(item.value.number);

    stack_push(item);
}

