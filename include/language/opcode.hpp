#pragma once

#define OPCODES \
    X (OP_RETURN) \
    X (OP_CONSTANT) \
    X (OP_NEGATE) \
    X (OP_ADD) \
    X (OP_SUBTRACT) \
    X (OP_MULTIPLY) \
    X (OP_DIVIDE)


enum opcode : int
{
#define X(x, ...) \
    x,
    OPCODES
#undef X
};
