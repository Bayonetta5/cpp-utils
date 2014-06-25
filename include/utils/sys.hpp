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
     * \brief search a file in $PATH
     * \return the path where the file was find. if no file find, the value is empty
     */
    std::string whereis(const std::string& filename);
    
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


        /**
         * \brief remove a directory.
         * \param  recusive if true, delete all files on directory inside
         * \return true on success
         */
        bool rm(const std::string& path,bool recusive=false);


        /**
         * \brief remove the directory is empty
         * \brief recusive if true, delete all sub directory that are empty
         * \return true on success
         */
        bool rm_if_empty(const std::string& path,bool recusive=false);

        /**
         * \return the current dir path
         */
        std::string pwd();

        /**
         * \return the real path of
         */
        std::string abs_path(const std::string& relative_path);
    }

    namespace file
    {
        /**
         * \brief remove a file
         * \return true on success
         */
        bool rm(const std::string& path);

        /**
         * \return true if the file file_path exists
         */
        bool exists(const std::string& file_path);

        /**
         * \brief creat a empty file (creat the dir tree)
         * \return true on success
         */
        bool touch(const std::string& file_path);


    }
}
}
#endif
