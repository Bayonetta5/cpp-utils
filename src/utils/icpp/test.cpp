#include <utils/icpp/test.hpp>
#include <utils/sys.cpp>
#include <vector>
#include <regex>
#include <algorithm> // for copy

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

        /*
        if(libf.load_f<int,int>("print"))
            libf["print"]->call<int>(21);

        if(libf.load_f<void,const Value&>("show"))
            libf["show"]->call<void>(vec[2]);
        libf.close();
        */

        std::string f_signature; //int name(int);
        //std::cin.ignore();
        std::cout<<"function signature?\n>"<<std::flush;
        std::getline(std::cin,f_signature);
        std::cout<<"signature: "<<f_signature<<std::endl;

        utils::string::replace(f_signature,","," ");
        utils::string::replace(f_signature,"("," ");
        utils::string::replace(f_signature,")"," ");

        auto sp = utils::string::split(f_signature," ");
        std::string ret = sp[0];
        std::string name = sp[1];

        std::cout<<"return : "<<ret
            <<" name : "<<name
            <<" params: [";
        std::copy(sp.begin()+2,sp.end(),std::ostream_iterator<std::string>(std::cout, " "));
        std::cout<<"]"<<std::endl;
    }



    return 0;
}
