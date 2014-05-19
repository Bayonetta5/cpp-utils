 /* use newer C++ skeleton file */
%skeleton "lalr1.cc"
/* Require bison version or later */
%require "2.5"
/* verbose error messages */
%error-verbose
/* namespace to enclose parser in */
%define api.namespace {utils::json}
/* set the parser's class identifier */
%define parser_class_name {Parser}

%lex-param { utils::json::Scanner& scanner }
%parse-param { utils::json::Scanner& scanner }

/*%lex-param { utils::json::Driver& driver }*/
%parse-param { utils::json::Driver& driver }

%code requires {

    extern int json_line_no; 

    namespace utils {
        namespace json {
            class Scanner;
            class Driver;
        }
    }
}

%code{
    #include <utils/json/Driver.hpp>
    #include <utils/json/Value.hpp>
    #include <utils/json/Array.hpp>
    #include <utils/json/Object.hpp>
    #include <string>
	/*Prototype for the yylex function*/
	static int yylex(utils::json::Parser::semantic_type* yylval, utils::json::Scanner& scanner);

    #define DEL(x) delete x; x=nullptr;
}



%union
{
    // "Pure" types
    long long int   v_int;
    long double     v_float;
    bool            v_bool;
    std::string*    v_string;
    // Pointers to more complex classes
    utils::json::Object* v_object;
    utils::json::Array* v_array;
    utils::json::Value* v_value;
} 

    
/** Declare tokens */
%token      T_EQUALS                  "equals token"
%token      T_SQUARE_BRACKET_L        "square bracket left"
%token      T_SQUARE_BRACKET_R        "square bracket right"
%token      T_CURLY_BRACKET_L         "curry bracket left"
%token      T_CURLY_BRACKET_R         "curry bracket right"
%token      T_COMMA                   "coma"
%token      T_COLON                   "colon"

%token      T_NUMBER_I                "integer"
%token      T_NUMBER_F                "float"
%token      T_BOOLEAN                 "boolean"
%token      T_NULL                    "null"
%token      T_DOUBLE_QUOTED_STRING    "double quoted string"


%start start
/** Define types for union values */
%type<v_int>    T_NUMBER_I
%type<v_float>  T_NUMBER_F
%type<v_bool>   T_BOOLEAN
%type<v_string> T_DOUBLE_QUOTED_STRING
%type<v_value>  value
%type<v_array>  array
%type<v_object> Object


%%

// Entry point (every JSON file represents a value)
start: value {driver.value = $1;};

object: T_CURLY_BRACKET_L assignment_list T_CURLY_BRACKET_R /*{$$ = $2;}*/
      ;

array : T_SQUARE_BRACKET_L list T_SQUARE_BRACKET_R {}
      ;

value : T_DOUBLE_QUOTED_STRING
      | T_NUMBER_I
      | T_NUMBER_F
      | object
      | array
      | T_BOOLEAN
      | T_NULL
      ;

list : value
     | list T_COMMA value
     ;

assignment_list : T_DOUBLE_QUOTED_STRING T_COLON value
               | assignment_list T_COMMA T_STRING T_COLON value

//
//// Object rule
//object: CURLY_BRACKET_L assignment_list CURLY_BRACKET_R { $$ = $2; } ;
//
//// Array rule
//array : SQUARE_BRACKET_L list SQUARE_BRACKET_R { $$ = $2; } ;
//
//// Values rule
//value : NUMBER_I { $$ = new JSON::Value($1); }
//    | NUMBER_F { $$ = new JSON::Value($1); }
//    | BOOLEAN { $$ = new JSON::Value($1); }
//    | NULL_T { $$ = new JSON::Value(); }
//    | string { $$ = new JSON::Value(std::move(std::string($1))); delete $1; }
//    | object { $$ = new JSON::Value(std::move(*$1)); delete $1; }
//    | array { $$ = new JSON::Value(std::move(*$1)); delete $1; }
//    ;
//
//// String rule
//string : DOUBLE_QUOTED_STRING {
//        // Trim string
//        std::string s($1);
//        s = s.substr(1, s.length()-2);
//        char* t = new char[s.length()+1];
//        strcpy(t, s.c_str());
//        $$ = t;
//    } 
//    | SINGLE_QUOTED_STRING {
//        // Trim string
//        std::string s($1);
//        s = s.substr(1, s.length()-2);
//        char* t = new char[s.length()+1];
//        strcpy(t, s.c_str());
//        $$ = t;
//    };
//
//// Assignments rule
//assignment_list: /* empty */ { $$ = new JSON::Object(); } 
//    | string COLON value {
//        $$ = new JSON::Object();
//        $$->insert(std::make_pair(std::string($1), std::move(*$3)));
//        delete $1;
//        delete $3;
//    } 
//    | assignment_list COMMA string COLON value { 
//        $$->insert(std::make_pair(std::string($3), std::move(*$5)));
//        delete $3;
//        delete $5;
//    }
//    ;
//    
//// List rule
//list: /* empty */ { $$ = new JSON::Array(); }
//    | value {
//        $$ = new JSON::Array();
//        $$->push_back(std::move(*$1));
//        delete $1;
//    }
//    | list COMMA value { 
//        $$->push_back(std::move(*$3)); 
//        delete $3;
//    }
//    ;
//    

%%

void utils::json::Parser::error(const std::string &message)
{
   std::cerr<<"Error line "<<json_line_no<<" : "<<message<<std::endl;; 
}
 
/*Now that we have the Parser declared, we can declare the Scanner and implement the yylex function*/
#include <utils/json/Scanner.hpp>
#include <utils/json/Driver.hpp>
static int yylex(utils::json::Parser::semantic_type *yylval,utils::json::Scanner& scanner)
{
    return scanner.yylex(yylval);
}
