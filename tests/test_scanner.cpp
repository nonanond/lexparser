#include <catch2/catch.hpp>
//#include <language/language.hpp>
//#include <language/task.hpp>
//#include <language/promise.hpp>
//#include <language/lexer.hpp>
//#include <language/uni.hpp>
//#include <language/token.hpp>
//#include <experimental/coroutine>
//#include <language/generator.hpp>
#include <language/scanner.hpp>
#include <language/array.hpp>
#include <language/opcode.hpp>
#include <language/token.hpp>

//using namespace std;
//using namespace std::experimental;

auto disassemble = [] (array <int>& code, array <int>& consts) {
    
    auto dis_const = [&] (int*& i) {
        int index = * (i + 1);
        int c = consts [index];
        std::cout << "OP_CONSTANT " << c << std::endl;
        ++i;
    };
    
    for (auto i = code.begin(); i < code.end(); ++i)
    {
        switch (*i)
        {
            case opcode::OP_CONSTANT:
                dis_const (i);
                break;
                
            case opcode::OP_RETURN:
                std::cout << "OP_RETURN" << std::endl;
                break;
                
            case opcode::OP_NEGATE:
                std::cout << "OP_NEGATE" << std::endl;
                break;
                
            case opcode::OP_ADD:
                std::cout << "OP_ADD" << std::endl;
                break;
                
            case opcode::OP_SUBTRACT:
                std::cout << "OP_SUBTRACT" << std::endl;
                break;
                
            case opcode::OP_MULTIPLY:
                std::cout << "OP_MULTIPLY" << std::endl;
                break;
                
            case opcode::OP_DIVIDE:
                std::cout << "OP_DIVIDE" << std::endl;
                break;
                
            default:
                std::cout << "UNKNOWN" << std::endl;
                break;
        }
    }
};


TEST_CASE ("")
{
    return;
    auto code   = array <int> {};
    auto consts = array <int> {};
    
    [&]{
        code += opcode::OP_CONSTANT;
        consts += 10;
        code += consts.active() - 1;
        
        code += opcode::OP_CONSTANT;
        consts += 20;
        code += consts.active() - 1;
        code += opcode::OP_NEGATE;
        
        code += opcode::OP_CONSTANT;
        consts += 1;
        code += consts.active() - 1;
        
        code += opcode::OP_CONSTANT;
        consts += 2;
        code += consts.active() - 1;
        
        code += opcode::OP_ADD;
        
        code += opcode::OP_RETURN;
    }();
    
    
    disassemble (code, consts);
}





auto scan (char const* source) -> scanner <token>
{
    co_yield source;
    
    while (true)
    {
        co_await scan_token {};
    }
    
    
    std::cout << "yo" << std::endl;
    
    
    
    
}


TEST_CASE ("")
{
    char const* source = "3+2-(7*4)";
    
    auto sc = scan (source);
    auto tok = (token) sc;
    
    
}


