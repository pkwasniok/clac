#pragma once

typedef struct {
    enum {
        OPERATOR,
        LITERAL_NUMBER
    } type;

    struct {
        int operator;
        double literal_number;
    } value;
} token_t;

void print_token(token_t token);

