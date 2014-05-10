#ifndef UTILS_LOGS_LOG_HPP
#define UTILS_LOGS_LOG_HPP

#include <ostream>

namespace utils
{
/**
 * \brief regroup function for log in a console
 * This functions are output-only I/O manipulator, it may be called with an expression such as out<<bold<<"text"<<reset;
 */
namespace log
{

    /**
     * \brief print a message
     */
    void info(const std::string& msg);

    /**
     * \brief print a message
     */
    void info(const std::string& type,const std::string& msg);

    /**
     * \brief print a message
     */
    void warnning(const std::string& msg);

    /**
     * \brief print a message
     */
    void warnning(const std::string& type,const std::string& msg);

    /**
     * \brief print a message
     */
    void error(const std::string& msg);

    /**
     * \brief print a message
     */
    void error(const std::string& type,const std::string& msg);

    /**
     * \brief print a message
     * if the code value is not 0, exit with that code
     */
    void critical(const std::string& msg,int code=0);

    /**
     * \brief print a message
     * if the code value is not 0, exit with that code
     */
    void critical(const std::string& type,const std::string& msg,int code=0);

    enum LOG_LVL{
        INFO = 1,
        WARNNING,
        ERROR,
        CRITICAL
    };

    template <typename ... Args>
    void log(LOG_LVL lvl,Args&& ... args);

    /**
     * \brief change the text format
     */
    namespace format
    {
        std::ostream& bold(std::ostream& output);

        std::ostream& dim(std::ostream& output);

        std::ostream& underline(std::ostream& output);

        std::ostream& blink(std::ostream& output);

        std::ostream& reverse(std::ostream& output);

        std::ostream& hidden(std::ostream& output);

        std::ostream& strikeout(std::ostream& output);



        std::ostream& reset_bold(std::ostream& output);

        std::ostream& reset_dim(std::ostream& output);

        std::ostream& reset_underline(std::ostream& output);

        std::ostream& reset_blink(std::ostream& output);

        std::ostream& reset_reverse(std::ostream& output);

        std::ostream& reset_hidden(std::ostream& output);

        std::ostream& reset_strikeout(std::ostream& output);

        /**
         * \brief reset the format
         * \return output
         */
        std::ostream& reset(std::ostream& output);
    }

    /**
     * \brief change the text color
     */ 
    namespace colors
    {
        std::ostream& black(std::ostream& output);

        std::ostream& red(std::ostream& output);

        std::ostream& green(std::ostream& output);

        std::ostream& yellow(std::ostream& output);

        std::ostream& blue(std::ostream& output);

        std::ostream& magenta(std::ostream& output);

        std::ostream& cyan(std::ostream& output);

        std::ostream& light_gray(std::ostream& output);

        std::ostream& dark_gray(std::ostream& output);

        std::ostream& light_red(std::ostream& output);

        std::ostream& light_green(std::ostream& output);

        std::ostream& light_yellow(std::ostream& output);

        std::ostream& light_blue(std::ostream& output);

        std::ostream& light_magenta(std::ostream& output);

        std::ostream& light_cyan(std::ostream& output);

        std::ostream& white(std::ostream& output);

        std::ostream& reset(std::ostream& output);

    }

    /**
     * \brief change the background color
     */ 
    namespace bg
    {
        std::ostream& black(std::ostream& output);

        std::ostream& red(std::ostream& output);

        std::ostream& green(std::ostream& output);

        std::ostream& yellow(std::ostream& output);

        std::ostream& blue(std::ostream& output);

        std::ostream& magenta(std::ostream& output);

        std::ostream& cyan(std::ostream& output);

        std::ostream& light_gray(std::ostream& output);

        std::ostream& dark_gray(std::ostream& output);

        std::ostream& light_red(std::ostream& output);

        std::ostream& light_green(std::ostream& output);

        std::ostream& light_yellow(std::ostream& output);

        std::ostream& light_blue(std::ostream& output);

        std::ostream& light_magenta(std::ostream& output);

        std::ostream& light_cyan(std::ostream& output);

        std::ostream& white(std::ostream& output);

        std::ostream& reset(std::ostream& output);

    }
}
}
#include <utils/log.tpl>
#endif
