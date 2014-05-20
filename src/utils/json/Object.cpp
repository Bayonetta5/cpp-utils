#include <utils/json/Object.hpp>
//#include <utils/json/Value.hpp>

namespace utils
{
    namespace json
    {
        
        Object::Object()
        {
        }

        std::ostream& operator<<(std::ostream& stream, const Object& self)
        {
            stream<<"{";
            if(self.values.size()>0)
            {
                auto begin = self.values.begin();
                auto end = self.values.end();
                stream<<"\""<<begin->first<<"\":"<<begin->second;
                ++begin;
                while(begin!=end)
                {
                    stream<<",\""<<begin->first<<"\":"<<begin->second;
                    ++begin;
                }
            }
            stream<<"}";
            return stream;
        }

        Value& Object::operator[] (const std::string& key)
        {
            return values[key];
        }

        const Value& Object::operator[] (const std::string& key) const
        {
            return values.at(key);
        }

        /*std::pair<std::unordered_map<std::string, Value>::iterator, bool> Object::insert(const std::pair<std::string, Value>& v)
        {
            return values.insert(v);
        }*/

        std::unordered_map<std::string, Value>::const_iterator Object::begin() const
        {
            return values.begin();
        }

        std::unordered_map<std::string, Value>::const_iterator Object::end() const
        {
            return values.end();
        }

        std::unordered_map<std::string, Value>::iterator Object::begin()
        {
            return values.begin();
        }

        std::unordered_map<std::string, Value>::iterator Object::end()
        {
            return values.end();
        }

        size_t Object::size() const
        {
            return values.size();
        }

    }
}
