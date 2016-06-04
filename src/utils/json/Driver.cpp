#include <utils/json/Driver.hpp>

#include <fstream>
#include <sstream>
#include <utils/log.hpp>
extern int json_line_no;

namespace utils
{
    namespace json
    {
        Driver::Driver(std::istream& in) : _scanner(in), _parser(_scanner,*this), _validity(true)
        {
        }

        
        std::shared_ptr<Value> Driver::parse()
        {
            json_line_no = 1;
            _validity=true;
            if(_parser.parse() != 0)
            {
                utils::log::error("utils::json","Parse failed");
                _validity=false;
            }
            return _value;
        }

        std::shared_ptr<Value> Driver::parse(std::istream& in)
        {
            Driver driver(in);
            return driver.parse();
        }

        std::shared_ptr<Value> Driver::parse(const std::string& in)
        {
            std::istringstream ss(in);
            Driver driver(ss);
            return driver.parse();
        }

        std::shared_ptr<Value> Driver::parse_file(const std::string& filename)
        {
            std::ifstream file(filename, std::ifstream::in);
            std::shared_ptr<Value> res;
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
