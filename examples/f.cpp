#include <iostream>

extern "C"
{
    int print(int value)
    {
        std::cout<<__FILE__<<":"<<__LINE__<<" print("<<value<<")"<<std::endl;
        return value +1;
    }
}
