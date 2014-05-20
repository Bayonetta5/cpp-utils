#ifndef UTILS_JSON_OBJECT_HPP
#define UTILS_JSON_OBJECT_HPP

#include <utils/json/Value.hpp>
#include <unordered_map>
#include <iostream>

namespace utils
{
    namespace json
    {
        class Object
        {
            public:
                explicit Object();

                Object(const Object&) = delete;
                Object& operator=(const Object&) = delete;

                Object(Object&&) = default;
                Object& operator=(Object&&) = default;

                friend std::ostream& operator<<(std::ostream& stream, const Object& self);

                Value& operator[] (const std::string& key);

                const Value& operator[] (const std::string& key) const;

                std::unordered_map<std::string, Value>::const_iterator begin() const;

                std::unordered_map<std::string, Value>::const_iterator end() const;

                std::unordered_map<std::string, Value>::iterator begin();

                std::unordered_map<std::string, Value>::iterator end();

                //std::pair<std::unordered_map<std::string, Value>::iterator, bool> insert(const std::pair<std::string, Value>& v);
                
                size_t size() const;


            private:
                friend class Parser;
                friend class Value;

                std::unordered_map<std::string,Value> values;

                static void ident(std::ostream& out,int);

                void print_ident(std::ostream& out,int i)const;

        };
    }
}
#endif
