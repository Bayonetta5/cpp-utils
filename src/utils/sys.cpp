#include <utils/sys.hpp>
#include <utils/string.hpp>

//#if __unix || __unix__

#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <errno.h>

//#endif


namespace utils
{
namespace sys
{
    namespace dir
    {
        int create(const std::string& dirpath,const int permissions)
        {
            int res = 1; //0 => error, 1 => created, 2 => already exist
            auto sp = string::split(dirpath,"/");


            std::string current;
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

            return res;
        }
    }
}
}
