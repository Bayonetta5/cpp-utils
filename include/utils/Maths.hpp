#ifndef UTILS_MATHS_HPP
#define UTILS_MATHS_HPP

namespace utils
{
namespace maths
{
    template <typename T>
    int sign(T val);

    template <typename T>
    inline const T& min(const T& a,const T& b);

    template <typename T, typename ... Args>
    inline const T& min(const T& a,const T& b, const Args& ... args);

    template <typename T>
    inline const T& max(const T& a,const T& b);

    template <typename T, typename ... Args>
    inline const T& max(const T& a,const T& b, const Args& ... args);
}
}
#include <utils/Maths.tpl>
#endif
