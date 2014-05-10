namespace utils
{
namespace maths
{
    template <typename T>
    int sign(T val)
    {
        return (T(0) < val) - (val < T(0));
    }

    template <typename T>
    inline const T& min(const T& a,const T& b)
    {
        return (a<b)?a:b;
    }

    template <typename T, typename ... Args>
    inline const T& min(const T& a,const T& b,const T& c, const Args& ... args)
    {
        return min(min(a,b),c,args ...);
    }

    template <typename T>
    inline const T& max(const T& a,const T& b)
    {
        return (a>b)?a:b;
    }

    template <typename T, typename ... Args>
    inline const T& max(const T& a,const T& b, const Args& ... args)
    {
        return max(max(a,b),args ...);
    }

    template <typename T>
    inline T abs(const T& a)
    {
        return (a<T(0))?-a:a;
    }
}
}
