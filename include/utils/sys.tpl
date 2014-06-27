namespace utils
{
    /**
     * \brief try namespace (for tests)
     */
    namespace sys
    {
        template<typename Ret,typename ... Args>
        bool Library::load_f(const std::string& name)
        {
            if (lib == nullptr)
                return false;

            auto value = funcs.find(name);
            if(value != funcs.end())
            {
                utils::log::error("utils:sys::Library::load_f","function of name",name,"already exists");
                return false;
            }

            void* f = nullptr;
            #ifdef _WIN32 //_WIN64
            f = (void*)::GetProcAddress(lib,name.c_str());
            if(f == nullptr)
            {
                utils::log::error("utils:sys::Library::load_f","Unable to load function",name);
                return false;
            }
            #elif __linux //|| __unix //or __APPLE__
            f = ::dlsym(lib,name.c_str());
            char* err = ::dlerror();
            if(f == nullptr or err)
            {
                utils::log::error("utils:sys::Library::load_f","Unable to load function",name,err);
                return false;
            }
            #endif

            funcs.emplace(name,new utils::func::Func<Ret,Args...>(reinterpret_cast<Ret(*)(Args...)>(f)));
            return true;
        }

        template<typename ... Args>
        Compiler& Compiler::input(Args&& ... args)
        {
            char tmp[] = {(_inputs.push_back(args),'0')...};
            ((void)(tmp));

            return *this;
        }

        template<typename ... Args>
        Compiler& Compiler::flags(Args&& ... args)
        {
            char tmp[] = {(_flags.push_back(args),'0')...};
            ((void)(tmp));

            return *this;
        }

        template<typename ... Args>
        Compiler& Compiler::link(Args&& ... args)
        {
            char tmp[] = {(_links.push_back(args),'0')...};
            ((void)(tmp));

            return *this;
        }
    }
}
