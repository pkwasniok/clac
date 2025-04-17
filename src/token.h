#pragma once

typedef enum {
    ADD,
    SUBTRACT,
    MULTIPLY,
    DIVIDE,
} TokenOperator;

typedef struct {
    enum {
        OPERATOR,
        LITERAL_NUMBER
    } type;

    struct {
        TokenOperator operator;
        double literal_number;
    } value;
} Token;

