#ifndef UTILS_JSON_VALUE_HPP
#define UTILS_JSON_VALUE_HPP

#include <string>
#include <iostream>

namespace utils
{
    namespace json
    {
        class Array;
        class Object;

        class Value
        {
            public:
                Value(std::string* v);
                Value(long long int v);
                Value(long int v);
                Value(int v);
                Value(long double v);
                Value(double);
                Value(float);
                Value(utils::json::Array* v);
                Value(utils::json::Object* v);
                Value(bool v);
                explicit Value();//<NULL constructor

                Value(const Value&) = delete;
                Value& operator=(const Value&) = delete;

                Value(Value&&);
                Value& operator=(Value&&);

                ~Value();

                /** Cast operator for float */
                operator long double() const;
                /** Cast operator for int */
                operator long long int() const;
                /** Cast operator for bool */
                operator bool() const;
                /** Cast operator for string */
                operator const std::string&() const;
                /** Cast operator for Object */
                operator const Object&() const;
                /** Cast operator for Object */
                operator const Array&() const;
                
                /** Cast operator for float */
                operator long double&();
                /** Cast operator for int */
                operator long long int&();
                /** Cast operator for bool */
                operator bool&();
                /** Cast operator for string */
                operator std::string&();
                /** Cast operator for Object */
                operator Object&();
                /** Cast operator for Object */
                operator Array&();

                enum Type {
                    STRING,
                    INT,
                    FLOAT,
                    ARRAY,
                    OBJECT,
                    BOOL,
                    NIL,
                    UNDEFINE
                };
                    
                Type getType()const;
                
                bool isString()const;
                bool isInt()const;
                bool isFloat()const;
                bool isArray()const;
                bool isObject()const;
                bool isBool()const;
                bool isNull()const;

                friend std::ostream& operator<<(std::ostream& stream, const Value& self);

                long double& as_float();
                long long int& as_int();
                bool& as_bool();
                std::string& as_string();
                Object& as_object();
                Array& as_array();


            private:
                friend class Object;
                
                union {
                    std::string*    v_string;
                    long long int   v_int;
                    long double     v_float;
                    Array*          v_array;
                    Object*         v_object;
                    bool            v_bool;
                };

                Type type;
                
                void print_ident(std::ostream& out,int i)const;
        };
    }
}
#endif
