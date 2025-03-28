#pragma once
#include "../token.h"

typedef struct macro {
    char *name;
    void (*handler)(void);
} macro_t;

void interprete_macro(token_t token);

