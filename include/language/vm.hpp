#pragma once

#include "common.hpp"
#include "array.hpp"
#include "opcode.hpp"

struct vm
{
    enum result
    {
        OK,
        COMPILE_ERROR,
        RUNTIME_ERROR
    };
    
    cexp size_t stack_max = 256;
    
    int stack [stack_max];
    int* stack_top;
    int* ip;  /// points to the instruction about to be executed.
    array <int>& code;
    array <int>& consts;
    
    vm (array <int>& code, array <int>& consts) : stack {}, stack_top {stack}, ip {code.begin()}, code {code}, consts {consts} {}
    auto run () -> result
    {
        
        /// Each turn through that loop, we read and execute a single bytecode instruction.
        while (ip < code.end())
        {
            switch (*ip)
            {
                    
                case opcode::OP_RETURN:
                {
                    return result::OK;
                }
                    
                case opcode::OP_CONSTANT:
                {
                    int index = * (++ip);
                    int constant = consts [index];
                    push (constant);
                    ++ip;
                    break;
                }
                    
                case opcode::OP_NEGATE:
                {
                    push (-pop ());
                    ++ip;
                    break;
                }
                    
                case opcode::OP_ADD:
                {
                    push (pop () + pop ());
                    ++ip;
                    break;
                }
                    
                case opcode::OP_SUBTRACT:
                {
                    push (pop () - pop ());
                    ++ip;
                    break;
                }
                    
                case opcode::OP_MULTIPLY:
                {
                    push (pop () * pop ());
                    ++ip;
                    break;
                }
                    
                case opcode::OP_DIVIDE:
                {
                    push (pop () / pop ());
                    ++ip;
                    break;
                }
                    
                default:
                {
                    throw;
                }
                    
            }
        }
    }
    
private:
    auto push (int value) -> void
    {
        *stack_top = value;
        ++stack_top;
    }
    auto pop () -> int
    {
        return * (--stack_top);
    }
};
