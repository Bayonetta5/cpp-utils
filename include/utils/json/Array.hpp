#ifndef UTILS_JSON_ARRAY_HPP
#define UTILS_JSON_ARRAY_HPP

#include <utils/json/Value>
#include <list>

namespace utils
{
    namespace json
    {
        class Array
        {
            public:
                Array();
                Array(const Array&) = delete;
                Array& operator=(const Array&) = delete;

            private:

                std::list<Value> list;
        };
    }
}
#endif
