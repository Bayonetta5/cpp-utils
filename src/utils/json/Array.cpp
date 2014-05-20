#include <utils/json/Array.hpp>

namespace utils
{
    namespace json
    {
        Array::Array()
        {
        }

        std::ostream& operator<<(std::ostream& stream, const Array& self)
        {
            stream<<"[";
            if(self.values.size()>0)
            {
                auto begin = self.values.begin();
                auto end = self.values.end();
                stream<<*begin;
                ++begin;
                while(begin!=end)
                {
                    stream<<","<<*begin;
                    ++begin;
                }
            }
            stream<<"]";
            return stream;
        }
    }
}
