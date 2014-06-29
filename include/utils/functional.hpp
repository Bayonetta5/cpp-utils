#ifndef UTILS_FUNCTIONAL_HPP
#define UTILS_FUNCTIONAL_HPP

#include <utility>
#include <tuple>

namespace utils
{
    /**
     * \brief try namespace (for tests)
     */
    namespace func
    {
        
        template<typename Ret,typename ... Args>
        constexpr Ret apply(Ret(*f)(Args...),const std::tuple<Args...>& t);


        class VFunc
        {
            public:
                template<typename Ret,typename ... Args>
                Ret call(Args&& ... args)const;

                virtual ~VFunc(){};

            protected:
                template<typename T> friend class __vcall_healper;
                void* func;

                VFunc(void* f);
        };


        template<typename Ret,typename ... Args>
        class Func: public VFunc
        {
            public:
                typedef Ret(*ftype)(Args...);

                Func(ftype f);
                Ret operator()(Args&& ... args)const;

                operator ftype()const;

                virtual ~Func(){};

            private:

        };

        template<typename Ret,typename ... Args>
        constexpr Func<Ret,Args...> make_func(Ret (*f)(Args...));
    }
}
#include <utils/functional.tpl>
#endif
