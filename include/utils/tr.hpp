#ifndef UTILS_TR_HPP
#define UTILS_TR_HPP

#include <utility>
#include <tuple>

namespace utils
{
    /**
     * \brief try namespace (for tests)
     */
    namespace tr
    {
        template<int N>
        struct apply_helper
        {
            template<typename Ret,typename ... FArgs,typename ... Args>
            static constexpr Ret apply(Ret(*f)(FArgs...),const std::tuple<FArgs...>& t,Args ... args)
            {
                return apply_helper<N-1>::apply(f,t,std::get<N-1>(t),std::forward<Args>(args)...);
            }
        };

        template<>
        struct apply_helper<0>
        {
            template<typename Ret,typename ... FArgs,typename ... Args>
            static constexpr Ret apply(Ret(*f)(FArgs...),const std::tuple<FArgs...>& t,Args ... args)
            {
                return f(std::forward<Args>(args)...);
            }
        };
        
        
        template<typename Ret,typename ... Args>
        constexpr Ret apply(Ret(*f)(Args...),const std::tuple<Args...>& t)
        {
            return apply_helper<sizeof...(Args)>::apply(f,t);
        }
        /*template <typename F, typename Tuple, size_t... I>
        decltype(auto) apply_impl(F&& f, Tuple&& t, std::index_sequence<I...>)
        {
            return std::forward<F>(f)(std::get<I>(std::forward<Tuple>(t))...);
        }

        template <typename F, typename Tuple>
        decltype(auto) apply(F&& f, Tuple&& t)
        {
            using Indices = std::make_index_sequence<std::tuple_size<decay_t<Tuple>>::value>;
            return apply_impl(std::forward<F>(f),std::forward<Tuple>(t),Indices{});
        }*/

        class VFunc
        {
            public:
                template<typename Ret,typename ... Args>
                Ret call(Args&& ... args)const
                {
                    auto t = std::make_tuple(std::forward<Args>(args)...);
                    Ret res;
                    _call(&res,&t);
                    return res;
                }

            protected:
                virtual void _call(void* ret,void* tuple)const = 0;
        };


        template<typename Ret,typename ... Args>
        class Func: public VFunc
        {
            public:
                typedef Ret(*ftype)(Args...);

                Func(ftype f) : func(f){}

                Ret operator()(Args&& ... args)const
                {
                    return call<Ret>(std::forward<Args>(args)...);
                }

            protected:

                virtual void _call(void* ret,void* tuple)const
                {
                    *reinterpret_cast<Ret*>(ret)=apply(func,*reinterpret_cast<std::tuple<Args...>*>(tuple));
                }

                ftype func;

        };

        template<typename Ret,typename ... Args>
        constexpr Func<Ret,Args...> make_func(Ret (*f)(Args...))
        {
            return {f};
        }
    }
}

#endif
