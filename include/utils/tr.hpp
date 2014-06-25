#ifndef UTILS_TR_HPP
#define UTILS_TR_HPP

#include <string>
#include <list>
#include <exception>

namespace utils
{
    /**
     * \brief try namespace (for tests)
     */
    namespace tr
    {
        //library blah = Compiler::getCompiler(or "compname").input("files",...).output((lib)"blah".so/.dll).flags(...).link((lib)"names").get();
        namespace compiler
        {
            class NoCompilerException : std::exception {
                public:
                    NoCompilerException(const std::string& name) : msg("no compiler \""+ name + "\" find") {};

                    virtual const char* what() const throw()
                    {
                        return nsg.cstr()
                    }
                private:
                    std::string msg;
            };

            class Library
            {
                private:
            }

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
                         
                    }

                    template<typename  ...  Args>
                    Compiler& input(const std::string&,...);

                    Compiler& output(const std::string& out);

                    template<typename ... Args>
                    Compiler& flags(const std::string&,...);

                    template<typename ... Args>
                    Compiler& link(const std::string&,...);

                    Library get() const;

                private:
                    std::string name;
                    std::list<std::string> inputs;
                    std::string output;
                    std::list<std::string> flags;
                    std::list<std::link> links;


                    Compiler(const std::string& name) : name(name), output("out")
                    {
                    }

            }
        }
    }
}

#endif
