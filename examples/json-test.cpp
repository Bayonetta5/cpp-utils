#include <utils/json/Driver.hpp>

int main(int argc,char* argv[])
{
    utils::json::Value* v = utils::json::Driver::parse_file(argv[1]);

    std::cout<<*v<<std::endl;

    utils::json::Value test_int = 42;
    int i = test_int;
    std::cout<<i<<std::endl;
    return 0;
}
