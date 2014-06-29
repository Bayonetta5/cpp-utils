namespace utils
{
    /**
     * \brief try namespace (for tests)
     */
    namespace func
    {
        template<int N>
        struct __apply_helper
        {
            template<typename Ret,typename ... FArgs,typename ... Args>
            static constexpr Ret apply(Ret(*f)(FArgs...),const std::tuple<FArgs...>& t,Args ... args)
            {
                return __apply_helper<N-1>::apply(f,t,std::get<N-1>(t),std::forward<Args>(args)...);
            }
        };

        template<>
        struct __apply_helper<0>
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
            return __apply_helper<sizeof...(Args)>::apply(f,t);
        }
        
        /*
         //C++14 version
        template <typename F, typename Tuple, size_t... I>
        decltype(auto) __apply_helper(F&& f, Tuple&& t, std::index_sequence<I...>)
        {
            return std::forward<F>(f)(std::get<I>(std::forward<Tuple>(t))...);
        }

        template <typename F, typename Tuple>
        decltype(auto) apply(F&& f, Tuple&& t)
        {
            using Indices = std::make_index_sequence<std::tuple_size<decay_t<Tuple>>::value>;
            return __apply_helper(std::forward<F>(f),std::forward<Tuple>(t),Indices{});
        }
        */

        template<typename Ret>
        struct __vcall_healper
        {
            template<typename ... Args>
            inline Ret operator()(const VFunc& f,Args&& ... args)const{
                auto t = std::make_tuple(std::forward<Args>(args)...);
                Ret res;
                f._call(&res,&t);
                return res;
            }
        };

        template<>
        struct __vcall_healper<void>
        {
            template<typename ... Args>
            inline void operator()(const VFunc& f,Args&& ... args)const{
                auto t = std::make_tuple(std::forward<Args>(args)...);
                f._call(nullptr,&t);
            }
        };

        /*** VFunc ***/
        template<typename Ret,typename ... Args>
        Ret VFunc::call(Args&& ... args)const
        {
            return __vcall_healper<Ret>()(*this,std::forward<Args>(args)...);
        }

        /*** Func ***/
        template<typename Ret,typename ... Args>
        Func<Ret,Args...>::Func(ftype f) : func(f){}

        template<typename Ret,typename ... Args>
        Ret Func<Ret,Args...>::operator()(Args&& ... args)const
        {
            return call<Ret>(std::forward<Args>(args)...);
        }

        template<typename Ret,typename ... Args>
        Func<Ret,Args...>::operator ftype()const
        {
            return func;
        }

        template<typename Ret>
        struct __call_healper
        {
            template<typename Func,typename Tuple>
            inline void operator()(void* ret,Func func,Tuple&& tuple)const{
                *reinterpret_cast<Ret*>(ret)=apply(func,tuple);
            };
        };

        template<>
        struct __call_healper<void>
        {
            template<typename Func,typename Tuple>
            inline void operator()(void* ret,Func func,Tuple&& tuple)const{
                apply(func,tuple);
            };
        };

        template<typename Ret,typename ... Args>
        void Func<Ret,Args...>::_call(void* ret,void* tuple)const
        {
            __call_healper<Ret>()(ret,func,*reinterpret_cast<std::tuple<Args...>*>(tuple));
        }

        template<typename Ret,typename ... Args>
        constexpr Func<Ret,Args...> make_func(Ret (*f)(Args...))
        {
            return {f};
        }
    }
}
