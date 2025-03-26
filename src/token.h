#pragma once

typedef struct {
    enum {
        OPERATOR,
        MACRO,
        LITERAL_NUMBER
    } type;

    struct {
        int operator;
        int macro;
        double literal_number;
    } value;
} token_t;

