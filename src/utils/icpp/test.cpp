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
    sys::Library libf = comp.input("f2.cpp")
        .output("f2")
        .flags("-o3","-Wall","-I../include","-std=c++0x")
        .get();

    if(libf.load())
    {
        if(libf.load_f<int,int>("print"))
            libf["print"]->call<int>(21);

        if(libf.load_f<void,const Value&>("show"))
            libf["show"]->call<void>(vec[2]);
        //cast test
        libf.close();
    }


    return 0;
}
