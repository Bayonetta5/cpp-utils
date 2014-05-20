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
                Value(long double v);
                Value(utils::json::Array* v);
                Value(utils::json::Object* v);
                Value(bool v);
                explicit Value();//<NULL constructor

                Value(const Value&) = delete;
                Value& operator=(const Value&) = delete;

                Value(Value&&) = default;
                Value& operator=(Value&&) = default;

                /** Cast operator for float */
                explicit operator long double() const;
            
                /** Cast operator for int */
                explicit operator long long int() const;
            
                /** Cast operator for bool */
                explicit operator bool() const;
            
                /** Cast operator for string */
                explicit operator const std::string&() const;
            
                /** Cast operator for Object */
                explicit operator const Object&() const;
            
                /** Cast operator for Object */
                explicit operator const Array&() const;

                enum Type {
                    STRING,
                    INT,
                    FLOAT,
                    ARRAY,
                    OBJECT,
                    BOOL,
                    NIL
                };
                    
                Type getType()const;

                friend std::ostream& operator<<(std::ostream& stream, const Value& self);

                long double& as_float();
                long long int& as_int();
                bool& as_bool();
                std::string& as_string();
                Object& as_object();
                Array& as_array();


            private:
                union {
                    std::string*    v_string;
                    long long int   v_int;
                    long double     v_float;
                    Array*          v_array;
                    Object*         v_object;
                    bool            v_bool;
                };

                Type type;
        };
    }
}
#endif
