#include "macro.h"
#include "../token.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "stack.h"

void handler_pop();
void handler_flush();
void handler_avg();
void handler_sort();
void handler_factorial();

void interprete_macro(token_t token) {
    assert(token.type == MACRO);

    struct macro macros[1024];

    macros[0].name = "@pop";
    macros[0].handler = &handler_pop;

    macros[1].name = "@flush";
    macros[1].handler = &handler_flush;

    macros[2].name = "@avg";
    macros[2].handler = &handler_avg;

    macros[3].name = "@sort";
    macros[3].handler = &handler_sort;

    macros[4].name = "@factorial";
    macros[4].handler = &handler_factorial;

    int found = 0;
    for (int i = 0; i < 5; i++) {
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

void handler_pop() {
    int res;
    item_t item;

    res = stack_pop(&item);

    if (res == E_EMPTY) {
        printf("Error: stack is empty!\n");
        return;
    }

    printf("%.4f\n", item.value.number);
}

void handler_flush() {
    item_t item;

    while (!stack_pop(&item)) {
        printf("%f ", item.value.number);
    }

    printf("\n");
}

void handler_avg() {
    double sum = 0;
    int c = 0;
    item_t item;
    while (!stack_pop(&item)) {
        sum += item.value.number; 
        c += 1;
    }

    if (c == 0) {
        printf("Error: stack is empty!\n");
        return;
    }

    item.value.number = sum / c;

    stack_push(item);
}

int cmp(const void *a, const void *b) {
    double l, r;

    l = *(double*) a;
    r = *(double*) b;

    if (l > r) {
        return -1;
    } else {
        return 1;
    }
}

void handler_sort() {
    double *buffer = malloc(sizeof(double) * stack_len());
    int buffer_len = 0;
    item_t item;

    while (!stack_pop(&item)) {
        buffer[buffer_len++] = item.value.number;
    }

    qsort(buffer, buffer_len, sizeof(double), cmp);

    for (int i = 0; i < buffer_len; i++) {
        item.type = NUMBER;
        item.value.number = buffer[i];
        stack_push(item);
    }

    free(buffer);
}

void handler_factorial() {
    double res = 1;

    item_t item;
    stack_pop(&item);

    assert(item.type == NUMBER);

    for (int i = 1; i <= (int) item.value.number; i++) {
        res *= i; 
    }

    item.value.number = res;

    stack_push(item);
}

