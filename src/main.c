#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "args.h"
#include "lexer.h"
#include "interpreter.h"
#include "macro.h"

void macro_sqrt(void);
void macro_avg(void);

int main() {
    macro_t macros[1024];

    macros[0].name = "sqrt";
    macros[0].handler = &macro_sqrt;

    macros[1].name = "avg";
    macros[1].handler = &macro_avg;

    char *name = "sqrt";
    for (int i = 0; i < 2; i++) {
        if (strcmp(name, macros[i].name) == 0) {
            (*macros[i].handler)();
        }
    }

    return 0;
}

void macro_sqrt(void) {
    printf("sqrt macro handler invoked!\n");
}

void macro_avg(void) {
    printf("avg macro handler invoked!\n");
}

