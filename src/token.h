#pragma once

typedef struct {
    enum {
        OPERATOR,
        MACRO,
        LITERAL_NUMBER
    } type;

    struct {
        int operator;
        char *macro;
        double literal_number;
    } value;
} token_t;

void print_token(token_t token);

