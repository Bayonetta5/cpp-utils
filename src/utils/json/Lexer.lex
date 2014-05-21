%{
    /* Implementation of yyFlexScanner */
    #include <utils/json/Scanner.hpp>
    #include <utils/log.hpp>

    /* typedef to make the returns for the tokens shorter */
    typedef utils::json::Parser::token token;
    int json_line_no = 1;

    /* define yyterminate as this instead of NULL */
    //#define yyterminate() return token::T_END;

    /* msvc2010 requires that we exclude this header file. */
    #define YY_NO_UNISTD_H
%}

%option c++
%option yyclass="Scanner"
%option nodefault
%option noyywrap
%option prefix="UtilsJson"

%%

\n {
    ++json_line_no;
    //return token::T_EOL;
}

"[" {
    utils::log::info("T_SQUARE_BRACKET_L");
    return token::T_SQUARE_BRACKET_L;
}

"]" {
    utils::log::info("T_SQUARE_BRACKET_R");
    return token::T_SQUARE_BRACKET_R;
}

"{" {
    utils::log::info("T_CURLY_BRACKET_L");
    return token::T_CURLY_BRACKET_L;
}

"}" {
    utils::log::info("T_CURLY_BRACKET_R");
    return token::T_CURLY_BRACKET_R;
}

"," {
    utils::log::info("T_COMMA");
    return token::T_COMMA;
}

":" {
    utils::log::info("T_COLON");
    return token::T_COLON;
}

[ \t]  {
}

[-+]?[0-9]+  {
    utils::log::info("T_NUMBER_I");
    yylval->v_int = ::atoi(yytext);
    return token::T_NUMBER_I;
}

[-+]?[0-9]*\.?[0-9]*([eE][-+]?[0-9]+)?  {
    utils::log::info("T_NUMBER_F");
    yylval->v_float = atof(yytext);
    return token::T_NUMBER_F;
}

true {
    utils::log::info("T_BOOLEAN");
    yylval->v_bool = true;
    return token::T_BOOLEAN;
}
false {
    utils::log::info("T_BOOLEAN");
    yylval->v_bool = false;
    return token::T_BOOLEAN;
}

null {
    utils::log::info("T_NULL");
    return token::T_NULL;
}

\"[^\"]*\" { 
    utils::log::info("T_DOUBLE_QUOTED_STRING");
    yylval->v_string = new std::string(yytext);
    return token::T_DOUBLE_QUOTED_STRING;
}

. {
    utils::log::error("JSON Parser","line",json_line_no,": what is that <",yytext,"> ?");
}

