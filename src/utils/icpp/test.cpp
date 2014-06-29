#include <utils/icpp/test.hpp>
#include <utils/sys.cpp>
#include <vector>

//#include <tuple>
//std::tuple_cat(tuple,std::make_tuple());

using namespace utils;

int main(int argc,char* argv[])
{
    std::vector<Value> vec = {{2},{2.4},{"test"}};
    for(const Value& v : vec)
        v.show(std::cout)<<std::endl;

    sys::Compiler comp = sys::Compiler::getCompiler();
    sys::Library libf = comp.input("f.cpp")
        .output("f")
        .flags("-o3","-Wall")
        .get();

    if(libf.load())
    {
        if(libf.load_f<int,int>("print"))
            libf["print"]->call<int>(21);
        //cast test
        libf.close();
    }


    return 0;
}
