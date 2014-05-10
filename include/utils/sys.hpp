#ifndef UTILS_SYS_HPP
#define UTILS_SYS_HPP

#include <string>
#include <list>

namespace utils
{
/**
 * \brief a namspace that regroup function for the system
 */
namespace sys
{
    /**
     * \brief regroup functions on dir and manipulation
     */
    namespace dir
    {
        /**
         * \brief create a directory.
         * \param dirpath the dir path name
         * \param permissions  (ignored in windows)
         * \return 1 if created, 2 if it was allready exist, 0 if errored
         */
        int create(const std::string& dirpath,const int permissions = 0777);

        /**
         * \brief get file list of a directory
         * \param dirpath the root dir
         * \return the list
         */
        std::list<std::string> list_files(const std::string& path);

        /**
         * \brief get the dir list in a folder
         * \param dirpath the root dir
         * \return the dir list (without . and ..)
         */
        std::list<std::string> list_dirs(const std::string& path);


    }
}
}
#endif
