#ifndef UTILS_JSON_OBJECT_HPP
#define UTILS_JSON_OBJECT_HPP

#include <utils/json/Value>
#include <unordered_map>
namespace utils
{
    namespace json
    {
        class Object
        {
            public:
                Object();
                Object(const Object&) = delete;
                Object& operator=(const Object&) = delete;

            private:

                std::unordered_map<std::string,Value> values;
        };
    }
}
#endif
