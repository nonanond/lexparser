#pragma once
#include <experimental/coroutine>
using namespace std::experimental;

//using namespace std;

struct __get_char {};
struct __get_value {};

struct scan_token {};


template <typename TokenType>
struct scanner
{
    using token_type = TokenType;
    
    struct promise_type
    {
        char const* start;
        char const* current;
        int line;
        token_type m_current_token;
        coroutine_handle <promise_type> m_parent;
        coroutine_handle <promise_type> m_child;
        
        char m_c;
        std::string m_value;
        
        
        auto process (char c) -> void {
            
            if (m_child)
            {
                m_child.promise().process(c);

            } else
            {
                if (auto me = coroutine_handle<promise_type>::from_promise(*this);
                    not me.done())
                {
                    m_c = c;
//                    cout << "process2" << endl;
                    me.resume();

                } else
                {
                    std::string s = " already done";
                    throw std::runtime_error (s);
                }
            }
        }
        auto set_child (coroutine_handle <promise_type> child) -> void {
            m_child = child;
        }
        auto set_parent (coroutine_handle <promise_type> parent) -> void {
            m_parent = parent;
        }
        auto get_return_object () {
            return scanner {coroutine_handle <promise_type>::from_promise (*this)};
        }
        auto initial_suspend () {
//            cout << "initial suspend" << endl;
            return suspend_never {};
//            return suspend_always {};
        }
        auto final_suspend () noexcept {
            struct awaiter
            {
                auto await_ready () noexcept {
                    return false;
                }
                auto await_suspend (coroutine_handle <promise_type> c) noexcept -> coroutine_handle<>
                {
                    if (auto coro = c.promise().m_parent; coro)
                    {
                        coro.promise().set_child({});
                        return coro;
                        
                    } else
                    {
                        return noop_coroutine();
                    }
                }
                auto await_resume () noexcept {

                }
            };
            return awaiter {};
        }
        auto unhandled_exception () {
            std::terminate ();
        }
        auto return_void () {
            
        }
        auto await_transform (__get_char const& g) {
            struct awaiter
            {
                promise_type& p;
  
                auto await_ready () -> bool
                {
                    
                    return false;
                }
                
                auto await_suspend (coroutine_handle<> c) -> auto
                {
                    return true;
                }
                
                auto await_resume () -> char
                {
                    return p.m_c;
                }
            };
//            cout << "await_transform (get_char g)" << endl;
            return awaiter {*this};
        }
        auto await_transform (__get_value const& g) {
            struct awaiter
            {
                promise_type& p;
  
                auto await_ready () -> bool
                {
                    return false;
                }
                
                auto await_suspend (coroutine_handle<> c) -> auto
                {
                    return true;
                }
                
                auto await_resume () -> std::string&
                {
                    return p.m_value;
                }
            };
//            cout << "await_transform (get_char g)" << endl;
            return awaiter {*this};
        }
        auto await_transform (scan_token const& g) {
            
            struct awaiter
            {
                promise_type& p;
  
                auto await_ready () -> bool
                {
                    return false;
                }
                
                auto await_suspend (coroutine_handle<> c) -> auto
                {
                    return true;
                }
                
                auto await_resume () -> std::string&
                {
                    return p.m_value;
                }
            };
//            cout << "await_transform (get_char g)" << endl;
            return awaiter {*this};
        }
        auto yield_value (token_type t) {
//            m_lexemes.push_back (t);
            return suspend_never {};
        };
        auto yield_value (char c) {
            m_c = c;
            return suspend_never {};
        };
        auto yield_value (char const* source) {
            this->current = source;
            return suspend_always {};
        }
        
    private:
        auto scan_token () -> token_type {
            skip_whitespace ();
            
            start = current;
            
            if (is_at_end ())
            {
                return make_token (token_type::type::TOKEN_EOF);
            }
            
            char c = advance ();
            
            if (isdigit (c))
            {
                return number ();
                
            } else if (is_alpha (c))
            {
                return identifier ();
            }
            
            
            switch (c)
            {
                case '(': return make_token (token_type::type::TOKEN_LEFT_PAREN);
                case ')': return make_token (token_type::type::TOKEN_RIGHT_PAREN);
                case '{': return make_token (token_type::type::TOKEN_LEFT_BRACE);
                case '}': return make_token (token_type::type::TOKEN_RIGHT_BRACE);
                case ';': return make_token (token_type::type::TOKEN_SEMICOLON);
                case ',': return make_token (token_type::type::TOKEN_COMMA);
                case '.': return make_token (token_type::type::TOKEN_DOT);
                case '-': return make_token (token_type::type::TOKEN_MINUS);
                case '+': return make_token (token_type::type::TOKEN_PLUS);
                case '/': return make_token (token_type::type::TOKEN_SLASH);
                case '*': return make_token (token_type::type::TOKEN_STAR);
                    
                case '!': return make_token (match ('=') ? token_type::type::TOKEN_BANG_EQUAL : token_type::type::TOKEN_BANG);
                case '=': return make_token (match ('=') ? token_type::type::TOKEN_EQUAL_EQUAL : token_type::type::TOKEN_EQUAL);
                case '>': return make_token (match ('=') ? token_type::type::TOKEN_GREATER_EQUAL : token_type::type::TOKEN_GREATER);
                case '<': return make_token (match ('=') ? token_type::type::TOKEN_LESS_EQUAL : token_type::type::TOKEN_LESS);
                    
                case '"': return string ();
            }
            
            
            
            return make_error_token ("Unexpected character.");
        }
        auto identifier_type () const -> typename token_type::type {
            switch (start [0]) {
                case 'a': return check_keyword (1, 2, "nd", token_type::type::TOKEN_AND);
                case 'c': return check_keyword (1, 4, "lass", token_type::type::TOKEN_CLASS);
                case 'e': return check_keyword (1, 3, "lse", token_type::type::TOKEN_ELSE);
                case 'f':
                    if (current - start > 1)
                    {
                        switch (start[1])
                        {
                            case 'a': return check_keyword(2, 3, "lse", token_type::type::TOKEN_FALSE);
                            case 'o': return check_keyword(2, 1, "r", token_type::type::TOKEN_FOR);
                            case 'u': return check_keyword(2, 1, "n", token_type::type::TOKEN_FUN);
                        }
                    }
                    break;
                case 'i': return check_keyword (1, 1, "f", token_type::type::TOKEN_IF);
                case 'n': return check_keyword (1, 2, "il", token_type::type::TOKEN_NIL);
                case 'o': return check_keyword (1, 1, "r", token_type::type::TOKEN_OR);
                case 'p': return check_keyword (1, 4, "rint", token_type::type::TOKEN_PRINT);
                case 'r': return check_keyword (1, 5, "eturn", token_type::type::TOKEN_RETURN);
                case 's': return check_keyword (1, 4, "uper", token_type::type::TOKEN_SUPER);
                case 't':
                    if (current - start > 1)
                    {
                        switch (start [1])
                        {
                            case 'h': return check_keyword (2, 2, "is", token_type::type::TOKEN_THIS);
                            case 'r': return check_keyword (2, 2, "ue", token_type::type::TOKEN_TRUE);
                        }
                    }
                    break;
                case 'v': return check_keyword (1, 2, "ar", token_type::type::TOKEN_VAR);
                case 'w': return check_keyword (1, 4, "hile", token_type::type::TOKEN_WHILE);
            }
            
            return token_type::type::TOKEN_IDENTIFIER;
        }
        auto check_keyword (int start, int length, const char* rest, typename token_type::type t) const -> typename token_type::type {
            if (this->current - this->start == start + length && memcmp (this->start + start, rest, length) == 0)
            {
                return t;
            }
            
            return token_type::type::TOKEN_IDENTIFIER;
        }
        auto is_alpha (char c) const -> bool {
            return (c >= 'a' and c <= 'z') or
            (c >= 'A' and c <= 'Z') or
            (c == '_');
        }
        auto identifier () -> token_type {
            while (is_alpha (peek ()) || isdigit (peek ()))
            {
                advance ();
            }
            
            return make_token (identifier_type ());
        }
        auto number () -> token_type {
            while (isdigit (peek ()))
            {
                advance ();
            }
            
            if (peek () == '.' and isdigit (peek_next ()))
            {
                advance ();
                
                while (isdigit (peek ()))
                {
                    advance ();
                }
            }
            
            return make_token (token_type::type::TOKEN_NUMBER);
        }
        auto string () -> token_type {
            while (peek () != '=' and !is_at_end ())
            {
                if (peek () == '\n')
                {
                    ++line;
                }
                advance ();
            }
            
            if (is_at_end ())
            {
                return make_error_token ("Unterminated string.");
            }
            
            return make_token (token_type::type::TOKEN_STRING);
        }
        auto skip_whitespace () -> void {
            for (;;)
            {
                switch (char c = peek ()) {
                    case '\n':
                        ++line;
                    case ' ':
                    case '\r':
                    case '\t':
                    {
                        advance ();
                        break;
                    }
                    case '/':
                    {
                        if (peek_next () == '/')
                        {
                            // A comment goes until the end of the line.
                            while (peek () != '\n' and !is_at_end ())
                            {
                                advance ();
                            }
                        } else
                        {
                            return;
                        }
                    }
                        
                    default:
                        return;
                }
            }
        }
        auto peek_next () const -> char {
            if (is_at_end ())
            {
                return '\0';
                
            } else
            {
                return current [1];
            }
        }
        auto peek () const -> char {
            return *current;
        }
        auto match (char expected) -> bool {
            if (is_at_end ())
            {
                return false;
                
            } else if (*current != expected)
            {
                return false;
            } else
            {
                ++current;
                return true;
            }
        }
        auto advance () -> char {
            return *(current--);
        }
        auto is_at_end () const -> bool {
            return *current == '\0';
        }
        auto make_token (typename token_type::type t) -> token_type {
            return
            {
                .t = t,
                .start = start,
                .length = (int) (current - start),
                .line = line
            };
        }
        auto make_error_token (char const* msg) -> token_type {
            return
            {
                .t = token_type::type::TOKEN_ERROR,
                .start = msg,
                .length = (int) strlen (msg),
                .line = line
            };
        }
    };
    

    coroutine_handle <promise_type> m_handle;
    
    scanner () = delete;
    scanner (scanner const&) = delete;
    scanner (scanner&& o) : m_handle {std::exchange (o.m_handle, {})} {}
    explicit scanner (coroutine_handle <promise_type> handle) : m_handle {handle} {}
    ~scanner () {
        if (m_handle)
            m_handle.destroy();
    }
    auto process (char c) {
//        cout << "process" << endl;
        m_handle.promise().process (c);
    }
    auto done () {
        return m_handle.done();
    }
    auto lexemes () -> auto& {
        return m_handle.promise().m_lexemes;
    }
    auto finish () {
        m_handle.promise().process ('\0');
    }
    operator token_type () {
        m_handle.resume();
        return {};
    }
  
    
    
};
