#include <utils/json/Driver.hpp>

int main(int argc,char* argv[])
{
    utils::json::Value* v = utils::json::Driver::parse_file(argv[1]);

    utils::json::Object& test = *v;
    std::cout<<test<<std::endl;

    utils::json::Value test_int;
    test_int= 42;
    std::cout<<test_int<<std::endl;
    return 0;
}
