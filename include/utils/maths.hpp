#ifndef UTILS_MATHS_HPP
#define UTILS_MATHS_HPP

namespace utils
{

    /**
     * \brief regroup some math utility
     */
    namespace maths
    {
        /**
         * \return -1 if < T(0), 1 if > T(0) else 0
         */
        template <typename T>
        int sign(T val);

        /**
         * \return a if a<, else b
         */
        template <typename T>
        inline const T& min(const T& a,const T& b);

        /**
         * \brief call min(a,b) recusivly
         */
        template <typename T, typename ... Args>
        inline const T& min(const T& a,const T& b,const T& c,const Args& ... args);

        /**
         * \return a if a>b else b
         */
        template <typename T>
        inline const T& max(const T& a,const T& b);

        /**
         * \brief call max(a,b) recusivly
         */
        template <typename T, typename ... Args>
        inline const T& max(const T& a,const T& b, const Args& ... args);

        /**
         * \return the abolute value of a
         */
        template <typename T>
        inline T abs(const T& a);
    }
}
#include <utils/maths.tpl>
#endif
