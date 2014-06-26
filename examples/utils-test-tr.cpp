#include <utils/tr.hpp>

int main(int argc,char* argv[])
{
    using namespace utils::tr;
    Compiler comp = Compiler::getCompiler();

    Library libf = comp.input("f.cpp")
        .output("f")
        .flags("-o3","-Wall")
        .get();

    if(libf.load())
    {
        if(libf.load_f<int,int>("print"))
            libf["print"]->call<int>(21);

        libf.close();
    }
    return 0;
}
