#include <utils/json/Driver.hpp>

#include <fstream>
#include <utils/log.hpp>

namespace utils
{
    namespace json
    {
        Driver::Driver(std::istream& in) : scanner(in), parser(scanner,*this), validity(true), value(nullptr)
        {
        }

        Driver::~Driver()
        {
            delete value;
        }

        
        Value* Driver::parse()
        {
            validity=true;
            if(parser.parse() != 0)
            {
                utils::log::error("utils::json","Parse failed");
                validity=false;
            }
            auto tmp = value;
            value = nullptr;
            return tmp;
        }

        Value* Driver::parse(std::istream& in)
        {
            Driver driver(in);
            return driver.parse();
        }

        Value* Driver::parse_file(const std::string& filename)
        {
            std::ifstream file(filename, std::ifstream::in);
            Value* res =nullptr;
            if (file.good())
            {
                Driver driver(file);
                res= driver.parse();
                file.close();
            }
            return res;
        }
    }
}
