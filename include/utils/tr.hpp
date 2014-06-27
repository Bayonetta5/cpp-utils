#ifndef UTILS_TR_HPP
#define UTILS_TR_HPP

#include <string>
#include <list>
#include <exception>

#include <utils/sys.hpp>

#include <iostream>

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


        class Library
        {
            private:
        };

        //library blah = Compiler::getCompiler(or "compname").input("files",...).output((lib)"blah".so/.dll).flags(...).link((lib)"names").get();
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

                template<typename  ...  Args>
                Compiler& input(const std::string&,...);

                Compiler& output(const std::string& out);

                template<typename ... Args>
                Compiler& flags(const std::string&,...);

                template<typename ... Args>
                Compiler& link(const std::string&,...);

                Library get() const;


                friend std::ostream& operator<<(std::ostream& output,const Compiler& self)
                {
                    output<<self.make_cmd();
                    return output;
                }

            private:
                std::string _name;
                std::list<std::string> _inputs;
                std::string _output;
                std::list<std::string> _flags;
                std::list<std::string> _links;

                std::string make_cmd()const
                {
                    return {};
                }


                Compiler(const std::string& name) : _name(name), _output("out")
                {
                }

        };
    }
}

#endif
