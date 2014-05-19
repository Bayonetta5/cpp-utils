%{
    /* Implementation of yyFlexScanner */
    #include <utils/json/Scanner.hpp>
    #include <utils/log.hpp>

    /* typedef to make the returns for the tokens shorter */
    typedef utils::json::Parser::token token;
    int json_line_no = 1;

    /* define yyterminate as this instead of NULL */
    #define yyterminate() return token::T_END;

    /* msvc2010 requires that we exclude this header file. */
    #define YY_NO_UNISTD_H
%}

%option c++
%option yyclass="Scanner"
%option nodefault
%option noyywrap

%%

\n {
    ++json_line_no;
    //return token::T_EOL;
}

"=" {
    return T_EQUALS;
}

"[" {
    return T_SQUARE_BRACKET_L;
}

"]" {
    return T_SQUARE_BRACKET_R;
}

"{" {
    return T_CURLY_BRACKET_L;
}

"}" {
    return T_CURLY_BRACKET_R;
}

"," {
    return T_COMMA;
}

":" {
    return T_COLON;
}

[ \t]  {
}

[-+]?[0-9]+  {
    yylval.v_int = ::atoi(yytext);
    return T_NUMBER_I;
}

[-+]?[0-9]*\.?[0-9]*([eE][-+]?[0-9]+)?  {
    yylval.v_float = atof(yytext);
    return T_NUMBER_F;
}

true {
    yylval.v_bool = true;
    return T_BOOLEAN;
}
false {
    yylval.v_bool = false;
    return T_BOOLEAN;
}

null {
    return T_NULL;
}

\"[^\"]*\" { 
    yylval.v_string = yytext;
    return T_DOUBLE_QUOTED_STRING;
}

. {
    utils::log::error("JSON Parser","line",json_line_no,": what is that <",yytext,"> ?");
}

