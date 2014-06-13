#include <utils/tr.hpp>
#include <iostream>

using namespace utils::tr;

double f(int a,int b)
{
    std::cout<<"f("<<a<<" "<<b<<")"<<std::endl;
    return 41.5;
}

int main(int argc,char* argv[])
{
    std::cout<<apply(f,std::make_tuple(1,5))<<std::endl;

    auto func=make_func(f);
    std::cout<<func(3,5)<<std::endl; //know complet type

    VFunc& vfunc=func;
    vfunc.call<double>(1,5); //must specify the return type

    return 0;
}
