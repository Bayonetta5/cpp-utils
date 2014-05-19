#ifndef UTILS_JSON_VALUE_HPP
#define UTILS_JSON_VALUE_HPP

#include <string>

namespace utils
{
    namespace json
    {
        class Array;
        class Object;

        class Value
        {
            public:
                Value();
                Value(const Value&) = delete;
                Value& operator=(const Value&) = delete;

            protected:

            private:
                union {
                    std::string*    v_string;
                    long long int   v_int;
                    long double     v_float;
                    Array*          v_array;
                    Object*         v_object;
                    bool            v_bool;
                    bool            v_null;
                };

                enum Type {
                    STRING,
                    INT,
                    FLOAT,
                    ARRAY,
                    OBJECT,
                    BOOL,
                    NIL
                }type;
        };
    }
}
#endif
