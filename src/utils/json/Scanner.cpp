#include <utils/json/Scanner.hpp>

namespace utils
{
    namespace json
    {
        Scanner::Scanner(std::istream& in) : yyFlexLexer(&in), yylval(nullptr)
        {
        }

        int Scanner::yylex(utils::json::Parser::semantic_type *lval)
        {
            yylval = lval;
            return this->yylex();
        }
    }
}
