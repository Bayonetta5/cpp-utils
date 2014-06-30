#include <iostream>

#include <thread>
#include <cmath>

int main(int argc,char* argv[])
{
    unsigned int nb = std::thread::hardware_concurrency();
    float sq = sqrt(nb);
    std::cout<<"set multiplot layout "<<::round(sq)<<","<<::ceil(sq)<<"\n";
    return 0;
}
