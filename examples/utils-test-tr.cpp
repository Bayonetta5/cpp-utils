#include <iostream>

#include <utils/tr.hpp>
#include <cmath>

int main(int argc,char* argv[])
{
    using namespace utils::tr;

    std::cout<<ceil(2)<<std::endl;
    Gnuplot g;

    g.plot("sin(x)");
    g.plot("log(x)");
    g.cmd("plot cos(x)");

    std::cin.get();
    g.clear();

    {
        auto x = {1,2,3,4};
        auto y = {1,4,2,5};

        g.plot("test",x,y,Gnuplot::Style::lines);
    }

    {
        auto x = {1,2,3,4};
        auto y = {3,4,8,2};

        g.plot(x,y,Gnuplot::Style::lines);
    }

    std::cin.get();
    g.close();

    return 0;
}
