#pragma once

typedef struct macro {
    char *name;
    void (*handler)(void);
} macro_t;

