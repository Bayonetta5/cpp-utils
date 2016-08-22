%{
    /* Implementation of yyFlexScanner */
    #include <utils/json/Scanner.hpp>
    #include <utils/log.hpp>
    #undef YY_DECL
    #define YY_DECL int utils::json::Scanner::yylex2()

    /* typedef to make the returns for the tokens shorter */
    typedef utils::json::Parser::token token;
    int json_line_no = 1;
    std::string json_buffer;

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
%option debug
%x STRING_BEGIN

%%

\n {
    utils::log::info("\\n");
    ++json_line_no;
    //return token::T_EOL;
}

"[" {
    utils::log::info("[");
    return token::T_SQUARE_BRACKET_L;
}

"]" {
    utils::log::info("]");
    return token::T_SQUARE_BRACKET_R;
}

"{" {
    utils::log::info("{");
    return token::T_CURLY_BRACKET_L;
}

"}" {
    utils::log::info("}");
    return token::T_CURLY_BRACKET_R;
}

"," {
    utils::log::info(",");
    return token::T_COMMA;
}

":" {
    utils::log::info(":");
    return token::T_COLON;
}

[ \t]  {
    utils::log::info("\\t");
}

[-+]?[0-9]+  {
    utils::log::info("number");
    yylval->v_int = ::atoi(yytext);
    return token::T_NUMBER_I;
}

[-+]?[0-9]*\.?[0-9]*([eE][-+]?[0-9]+)?  {
    utils::log::info("float");
    yylval->v_float = atof(yytext);
    return token::T_NUMBER_F;
}

true {
    utils::log::info("true");
    yylval->v_bool = true;
    return token::T_BOOLEAN;
}
false {
    utils::log::info("false");
    yylval->v_bool = false;
    return token::T_BOOLEAN;
}

null {
    utils::log::info("null");
    return token::T_NULL;
}

\" {
    utils::log::info("\\");
	json_buffer.clear();
	BEGIN STRING_BEGIN;
}

<STRING_BEGIN>\" {
    utils::log::info("string begin");
	yylval->v_string = new std::string(json_buffer);
	BEGIN 0;
	return token::T_DOUBLE_QUOTED_STRING;
}

<STRING_BEGIN>\\\" {
    utils::log::info("string \"");
	json_buffer.push_back('"');
}

<STRING_BEGIN>\\\\ {
    utils::log::info("string \\");
	json_buffer.push_back('\\');
}

<STRING_BEGIN>\\\/ {
    utils::log::info("string /");
	json_buffer.push_back('/');
}

<STRING_BEGIN>\\b {
    utils::log::info("\\b");
	json_buffer.push_back('\b');
}

<STRING_BEGIN>\\f {
    utils::log::info("string \\f");
	json_buffer.push_back('\f');
}

<STRING_BEGIN>\\n {
    utils::log::info("string \\n");
	json_buffer.push_back('\n');
}

<STRING_BEGIN>\\r {
    utils::log::info("string \\r");
	json_buffer.push_back('\r');
}

<STRING_BEGIN>\\t {
    utils::log::info("string \\t");
	json_buffer.push_back('\t');
}

<STRING_BEGIN>\\u[a-fA-F0-9][a-fA-F0-9][a-fA-F0-9][a-fA-F0-9] {
    utils::log::info("string utf8");
	//TODO NOT SUPPORTED
}

<STRING_BEGIN>[^\"] { 
    utils::log::info("string text");
	json_buffer.push_back(yytext[0]);
}

. {
    utils::log::error("JSON Parser","line",json_line_no,": what is that <",yytext,"> ?");
}

