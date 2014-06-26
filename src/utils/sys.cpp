#include <utils/sys.hpp>
#include <utils/string.hpp>

#if __unix || __unix__
#include <unistd.h>
#include <ftw.h>
#endif

#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <errno.h>
#include <cstring>
#include <cstdlib>

namespace utils
{
namespace sys
{
    std::string whereis(const std::string& name)
    {
        //compute path dirs vector
        std::vector<std::string> paths = utils::string::split(std::string(::getenv("PATH")),
        #ifdef _WIN32 //_WIN64
        ";"
        #else
        ":"
        #endif
        );

        for(std::string& bpath : paths)
        {
            std::string fpath = bpath;
            if(bpath.size() > 1)
            {
                #ifdef _WIN32 //_WIN64
                if(bpath[bpath.size()-1] != '\\')
                    fpath += '\\';
                #else
                if(bpath[bpath.size()-1] != '/')
                    fpath += '/';
                #endif
            }
            fpath += name;
            if(utils::sys::file::exists(fpath))
                return fpath;
        }
        return {};
    }

    //NoCompilerException
    NoCompilerException::NoCompilerException(const std::string& name) : msg("no compiler \""+ name + "\" find")
    {
    };

    const char* NoCompilerException::what() const throw()
    {
        return msg.c_str();
    }

    //CompilationException
    CompilationException::CompilationException(const std::string& name) : msg(name)
    {
    };

    const char* CompilationException::what() const throw()
    {
        return msg.c_str();
    }

    //Library
    Library::Library(const std::string& name) : _name(name),lib(nullptr)
    {
    }

    bool Library::load()
    {
        #ifdef _WIN32 //_WIN64
        lib = ::LoadLibrary(_name.c_str());
        if (lib == nullptr)
        {
            utils::log::error("utils:sys::Library::load","Unable to load ",_name);
            return false;
        }
        #elif __linux //|| __unix //or __APPLE__
        lib = ::dlopen(_name.c_str(), RTLD_LAZY);
        char* err = ::dlerror();
        if (lib == nullptr or err)
        {
            utils::log::error("utils:sys::Library::load","Unable to load ",_name,err);
            return false;
        }
        #endif
        return true;
    }

    void Library::close()
    {

        //clear all linked functions
        for(auto& c : funcs)
            delete c.second;
        funcs.clear();

        //delete the lib
        #ifdef _WIN32 //_WIN64
        ::FreeLibrary(lib);
        #elif __linux
        ::dlclose(lib);
        ::dlerror();
        #endif

    }

    utils::func::VFunc* Library::operator[](const std::string& name)
    {
        auto value = funcs.find(name);
        if(value != funcs.end())
            return value->second;
        return nullptr;
    }

    //Compiler
    Compiler Compiler::getCompiler()
    {
        try
        {
            #ifdef _WIN32 //_WIN64
            return getCompiler("mingw32-g++.exe");
            #else
            return getCompiler("g++");
            #endif
        }
        catch(NoCompilerException& e)
        {
            try
            {
                #ifdef _WIN32 //_WIN64
                return getCompiler("clang.exe");
                #else
                return getCompiler("clang");
                #endif
            }
            catch(NoCompilerException& e)
            {
                #ifdef _WIN32 //_WIN64
                throw NoCompilerException("mingw-g++.exe or clang.exe");
                #else
                throw NoCompilerException("g++ or clang");
                #endif
            }
        }
    }

    Compiler Compiler::getCompiler(const std::string& name)
    {
        std::string path = sys::whereis(name);
        if(name.empty())
            throw NoCompilerException(name);
        return Compiler(path);
    }

    Compiler& Compiler::output(const std::string& out)
    {
        _output = out;

        return *this;
    }


    Library Compiler::get() const
    {
        for(const std::string& u : make_cmds())
        {
            utils::log::info("utils:sys::Compiler::get","system(\""+u+"\")");
            int res = ::system(u.c_str());
            if(res == -1)
            {
                utils::log::error("utils:sys::Compiler::get","failed to make sytem call");
                throw CompilationException("fork failed");
            }
            else if(res != 0)
            {
                utils::log::error("utils:sys::Compiler::get","the command return the error code:",res);
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

    std::ostream& operator<<(std::ostream& output,const Compiler& self)
    {
        for(const std::string& u : self.make_cmds())
            output<<u<<std::endl;
        return output;
    }


    Compiler::Compiler(const std::string& name) : _name(name), _output("out")
    {
    }

    std::vector<std::string> Compiler::make_cmds() const
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

    namespace dir
    {
        int create(const std::string& dirpath,const int permissions)
        {
            int res = 1; //0 => error, 1 => created, 2 => already exist
            auto sp = string::split(dirpath,"/");


            std::string current;
            if(dirpath.size() > 0 and dirpath[0] == '/')
                current = "/";
            const unsigned int _size = sp.size();
            for(unsigned int i=0; i<_size and res != 0;++i)
            {

                current += sp[i] + "/";

                #if __WIN32
                res = ::mkdir(current.c_str());
                #else
                res = ::mkdir(current.c_str(), permissions);
                #endif

                if(res == 0)
                    res = 1;
                else if(errno == EEXIST)
                    res = 2;
                else
                    res = 0;
            }
            return res;
        }

        std::list<std::string> list_files(const std::string& dirpath)
        {
            DIR *curDir;
            std::list<std::string> res;

            if ((curDir = opendir(dirpath.c_str())) == NULL)
                return res;

            dirent *curEntry =readdir(curDir);
            while (curEntry != NULL)
            {
                if(curEntry->d_type == DT_REG)
                    res.push_back(curEntry->d_name);
                curEntry =readdir(curDir);
            }
            ::closedir(curDir);
            return res;
        }

        std::list<std::string> list_dirs(const std::string& dirpath)
        {
            DIR *curDir;
            std::list<std::string> res;

            if ((curDir = opendir(dirpath.c_str())) == NULL)
                return res;

            dirent *curEntry =readdir(curDir);
            while (curEntry != NULL)
            {
                if(curEntry->d_type == DT_DIR
                   and std::string(curEntry->d_name) != ".."
                   and std::string(curEntry->d_name) != ".")
                    res.push_back(curEntry->d_name);
                curEntry =readdir(curDir);
            }
            ::closedir(curDir);
            return res;
        }


        bool rm(const std::string& path,bool recusive)
        {
            bool res;
            if(not recusive)
            {
                #if __unix__
                res = ::rmdir(path.c_str()) == 0;
                #endif
            }
            else
            {
                auto f = [](const char *fpath, const struct stat *sb, int typeflag, struct FTW *ftwbuf) -> int
                {
                    int rv;
                    switch(typeflag)
                    {
                        case FTW_F:
                            rv = ::unlink(fpath);break;
                        case FTW_D:
                        case FTW_DP:
                            rv = ::rmdir(fpath);break;
                        default:
                            rv = ::remove(fpath);break;
                    }

                    if (rv)
                        ::perror(fpath);
                    return rv;
                };

                res = ::nftw(path.c_str(),f, 64, FTW_DEPTH | FTW_PHYS) == 0;
            }
            return res;
        }

        bool rm_if_empty(const std::string& path,bool recusive)
        {
            bool res;
            if(not recusive)
            {
                res = ::rmdir(path.c_str()) == 0;
            }
            else
            {
                auto f = [](const char *fpath, const struct stat *sb, int typeflag, struct FTW *ftwbuf) -> int
                {
                    int rv;
                    switch(typeflag)
                    {
                        case FTW_D:
                        case FTW_DP:
                            rv = ::rmdir(fpath);break;
                        default:
                            return 1;
                    }

                    if (rv)
                        ::perror(fpath);
                    return rv;
                };
                res = ::nftw(path.c_str(),f, 64, FTW_DEPTH | FTW_PHYS) == 0;
            }
            return res;
        }

        std::string pwd()
        {
            char* path = ::get_current_dir_name();
            std::string res(path);
            ::free(path);
            return res;
        }

        std::string abs_path(const std::string& relative_path)
        {
            char my_path[relative_path.size() + 1];
            ::strcpy(my_path,relative_path.c_str());
            char *resolved_path = ::realpath(my_path,nullptr);
            std::string res =  resolved_path;
            ::free(resolved_path);
            return res;
        }

    }

    namespace file
    {
        bool rm(const std::string& path)
        {
            #if __unix__
            return ::unlink(path.c_str()) == 0;
            #endif
        }

        bool exists(const std::string& name)
        {
            if (FILE *file = fopen(name.c_str(), "rb"))
            {
                fclose(file);
                return true;
            }
            return false;
        }

        bool touch(const std::string& file_path)
        {
            //build dir tree
            #ifdef _WIN32 //_WIN64
            file_path = utils::replace(file_path,"\\","/");
            #endif
            std::vector<std::string> dirs = utils::string::split(file_path,"/");
            if(dirs.size()>1)
                dirs.pop_back();
            std::string dir_path = "/"+utils::string::join("/",dirs);
            if(not dir::create(dir_path))
                return false;

            //create file
            if (FILE *file = fopen(file_path.c_str(), "ab"))
            {
                fclose(file);
                return true;
            }
            return false;

        }

        
    }
}
}
