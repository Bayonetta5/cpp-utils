#ifndef UTILS_STRING_HPP
#define UTILS_STRING_HPP

#include <string>
#include <vector>

namespace utils
{
namespace string
{
        /**
     * \brief split a string in multiple sub string
     * \param string base to split
     * \param del the delemiteur
     * \return a vector that contain the sub string
     */
    std::vector<std::string> split(const std::string& string,const std::string& del);

    /**
     * \brief find and replace
     */
    void replace(string& source, string const& find, string const& replace);

    /**
     * \brief like the python join
     */
    template<typename T>
    std::string join(const std::string& del,const std::vector<T>& datas,bool reverse=false);
}
}
#include <utils/String.tpl>
#endif
