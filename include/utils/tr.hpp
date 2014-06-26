#ifndef UTILS_TR_HPP
#define UTILS_TR_HPP

#include <string>
#include <vector>
#include <exception>
#include <unordered_map>

#include <utils/sys.hpp>
#include <utils/log.hpp>
#include <utils/functional.hpp>

#include <iostream>
#include <cstdlib>

#ifdef _WIN32 //_WIN64
    #include <windows.h>
#elif __linux //|| __unix //or __APPLE__ 
    #include <dlfcn.h>
#else
    #error not defined for this platform
#endif

namespace utils
{
    /**
     * \brief try namespace (for tests)
     */
    namespace tr
    {
        class NoCompilerException : std::exception
        {
            public:
                NoCompilerException(const std::string& name) : msg("no compiler \""+ name + "\" find") {};

                virtual const char* what() const throw()
                {
                    return msg.c_str();
                }
            private:
                std::string msg;
        };

        class CompilationException : std::exception
        {
            public:
                CompilationException(const std::string& name) : msg(name) {};

                virtual const char* what() const throw()
                {
                    return msg.c_str();
                }
            private:
                std::string msg;
        };

        class Library
        {
            public:
                Library(const std::string& name) : _name(name)
                {
                }

                bool load()
                {
                    return false;
                }

                bool close()
                {
                    return false;
                }

                template<typename Ret,typename ... Args>
                bool load_f(const std::string& name)
                {
                    void* f = 
                }

                utils::func::VFunc* operator[](const std::string& name)
                {
                    auto value = funcs.find(name);
                    if(value != funcs.end())
                        return value->second;
                    return nullptr;
                }

            private:
                std::string _name;
                std::unordered_map<std::string,utils::func::VFunc*> funcs;

                #ifdef _WIN32 //_WIN64
                HMODULE lib; ///< lib manager
                #elif __linux
                void* lib; ///< lig manager
                #endif
        };

        class Compiler
        {
            public:
                Compiler(const Compiler&) = default;
                Compiler& operator=(const Compiler&) = default;

                Compiler(Compiler&&) = default;
                Compiler& operator=(Compiler&&) = default;


                static Compiler getCompiler()
                {
                    try{
                        #ifdef _WIN32 //_WIN64
                        return getCompiler("mingw-g++.exe");
                        #else
                        return getCompiler("g++");
                        #endif
                    }catch(NoCompilerException& e){
                        try{
                            #ifdef _WIN32 //_WIN64
                            return getCompiler("clang.exe");
                            #else
                            return getCompiler("clang");
                            #endif
                        }
                        catch(NoCompilerException& e){
                            #ifdef _WIN32 //_WIN64
                            throw NoCompilerException("mingw-g++.exe or clang.exe");
                            #else
                            throw NoCompilerException("g++ or clang");
                            #endif
                        }
                    }
                }

                static Compiler getCompiler(const std::string& name)
                {
                    std::string path = sys::whereis(name);
                    if(name.empty())
                        throw NoCompilerException(name);
                    return Compiler(path);
                }

                template<typename ... Args>
                Compiler& input(Args&& ... args)
                {
                    char tmp[] = {(_inputs.push_back(args),'0')...};
                    ((void)(tmp));

                    return *this;
                }

                Compiler& output(const std::string& out)
                {
                    _output = out;

                    return *this;
                }

                template<typename ... Args>
                Compiler& flags(Args&& ... args)
                {
                    char tmp[] = {(_flags.push_back(args),'0')...};
                    ((void)(tmp));

                    return *this;
                }

                template<typename ... Args>
                Compiler& link(Args&& ... args)
                {
                    char tmp[] = {(_links.push_back(args),'0')...};
                    ((void)(tmp));

                    return *this;
                }

                Library get() const
                {
                    for(const std::string& u : make_cmds())
                    {
                        utils::log::info("utils:tr::Compiler::get","system(\"",u,"\")");
                        int res = ::system(u.c_str());
                        if(res == -1)
                        {
                            utils::log::error("utils:tr::Compiler::get","failed to make sytem call");
                            throw CompilationException("fork failed");
                        }
                        else if(res != 0)
                        {
                            utils::log::error("utils:tr::Compiler::get","the command return the error code:",res);
                            throw CompilationException("Error");
                        }

                    }
                    return {_output+
                    #ifdef _WIN32
                    ".dll"
                    #else
                    ".so"
                    #endif
                    };
                }

                friend std::ostream& operator<<(std::ostream& output,const Compiler& self)
                {
                    for(const std::string& u : self.make_cmds())
                        output<<u<<std::endl;
                    return output;
                }


            private:
                std::string _name;
                std::vector<std::string> _inputs;
                std::string _output;
                std::vector<std::string> _flags;
                std::vector<std::string> _links;


                Compiler(const std::string& name) : _name(name), _output("out")
                {
                }

                std::vector<std::string> make_cmds() const
                {
                    std::vector<std::string> res;

                    //compile as .o
                    unsigned int _size = _inputs.size();
                    for(unsigned int i=0;i<_size;++i)
                    {
                        std::string tmp = _name + " -fpic";

                        unsigned int _s = _flags.size();
                        for(unsigned int i=0;i<_s;++i)
                            tmp+=" "+_flags[i];

                        tmp +=" -c \"" +_inputs[i]+"\" -o \""+_inputs[i]+"\".o";

                        res.push_back(std::move(tmp));
                    }
                    
                    //compile .o as .so/.dll
                    {
                        std::string tmp = _name + " -shared -o "+_output+
                        #ifdef _WIN32
                        ".dll";
                        #else
                        ".so";
                        #endif

                        unsigned int _s = _links.size();
                        if(_s>0)
                        {
                            for(unsigned int i=0;i<_s;++i)
                                tmp += " -l"+_links[i];
                        }

                        for(unsigned int i=0;i<_size;++i)
                            tmp+= " \""+_inputs[i]+".o\"";

                        res.push_back(std::move(tmp));
                    }
                    
                    return res;
                }

        };
    }
}

#endif
