#ifndef UTILS_JSON_ARRAY_HPP
#define UTILS_JSON_ARRAY_HPP

#include <utils/json/Value.hpp>
#include <list>
#include <iostream>

namespace utils
{
    namespace json
    {
        class Array
        {
            public:
                explicit Array();

                Array(const Array&) = delete;
                Array& operator=(const Array&) = delete;

                Array(Array&&) = default;
                Array& operator=(Array&&) = default;
                
                friend std::ostream& operator<<(std::ostream& stream, const Array& self);

                std::list<Value> values;

            private:
                friend class Value;

                void print_ident(std::ostream& out,int i)const;

        };
    }
}
#endif
